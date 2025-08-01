/*******************************************************************************
* File Name: BckLftCnt.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "BckLftCnt.h"

uint8 BckLftCnt_initVar = 0u;


/*******************************************************************************
* Function Name: BckLftCnt_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void BckLftCnt_Init(void) 
{
        #if (!BckLftCnt_UsingFixedFunction && !BckLftCnt_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!BckLftCnt_UsingFixedFunction && !BckLftCnt_ControlRegRemoved) */
        
        #if(!BckLftCnt_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 BckLftCnt_interruptState;
        #endif /* (!BckLftCnt_UsingFixedFunction) */
        
        #if (BckLftCnt_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            BckLftCnt_CONTROL &= BckLftCnt_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                BckLftCnt_CONTROL2 &= ((uint8)(~BckLftCnt_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                BckLftCnt_CONTROL3 &= ((uint8)(~BckLftCnt_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (BckLftCnt_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                BckLftCnt_CONTROL |= BckLftCnt_ONESHOT;
            #endif /* (BckLftCnt_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            BckLftCnt_CONTROL2 |= BckLftCnt_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            BckLftCnt_RT1 &= ((uint8)(~BckLftCnt_RT1_MASK));
            BckLftCnt_RT1 |= BckLftCnt_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            BckLftCnt_RT1 &= ((uint8)(~BckLftCnt_SYNCDSI_MASK));
            BckLftCnt_RT1 |= BckLftCnt_SYNCDSI_EN;

        #else
            #if(!BckLftCnt_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = BckLftCnt_CONTROL & ((uint8)(~BckLftCnt_CTRL_CMPMODE_MASK));
            BckLftCnt_CONTROL = ctrl | BckLftCnt_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = BckLftCnt_CONTROL & ((uint8)(~BckLftCnt_CTRL_CAPMODE_MASK));
            
            #if( 0 != BckLftCnt_CAPTURE_MODE_CONF)
                BckLftCnt_CONTROL = ctrl | BckLftCnt_DEFAULT_CAPTURE_MODE;
            #else
                BckLftCnt_CONTROL = ctrl;
            #endif /* 0 != BckLftCnt_CAPTURE_MODE */ 
            
            #endif /* (!BckLftCnt_ControlRegRemoved) */
        #endif /* (BckLftCnt_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!BckLftCnt_UsingFixedFunction)
            BckLftCnt_ClearFIFO();
        #endif /* (!BckLftCnt_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        BckLftCnt_WritePeriod(BckLftCnt_INIT_PERIOD_VALUE);
        #if (!(BckLftCnt_UsingFixedFunction && (CY_PSOC5A)))
            BckLftCnt_WriteCounter(BckLftCnt_INIT_COUNTER_VALUE);
        #endif /* (!(BckLftCnt_UsingFixedFunction && (CY_PSOC5A))) */
        BckLftCnt_SetInterruptMode(BckLftCnt_INIT_INTERRUPTS_MASK);
        
        #if (!BckLftCnt_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)BckLftCnt_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            BckLftCnt_WriteCompare(BckLftCnt_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            BckLftCnt_interruptState = CyEnterCriticalSection();
            
            BckLftCnt_STATUS_AUX_CTRL |= BckLftCnt_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(BckLftCnt_interruptState);
            
        #endif /* (!BckLftCnt_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BckLftCnt_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void BckLftCnt_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (BckLftCnt_UsingFixedFunction)
        BckLftCnt_GLOBAL_ENABLE |= BckLftCnt_BLOCK_EN_MASK;
        BckLftCnt_GLOBAL_STBY_ENABLE |= BckLftCnt_BLOCK_STBY_EN_MASK;
    #endif /* (BckLftCnt_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!BckLftCnt_ControlRegRemoved || BckLftCnt_UsingFixedFunction)
        BckLftCnt_CONTROL |= BckLftCnt_CTRL_ENABLE;                
    #endif /* (!BckLftCnt_ControlRegRemoved || BckLftCnt_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: BckLftCnt_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  BckLftCnt_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void BckLftCnt_Start(void) 
{
    if(BckLftCnt_initVar == 0u)
    {
        BckLftCnt_Init();
        
        BckLftCnt_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    BckLftCnt_Enable();        
}


/*******************************************************************************
* Function Name: BckLftCnt_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void BckLftCnt_Stop(void) 
{
    /* Disable Counter */
    #if(!BckLftCnt_ControlRegRemoved || BckLftCnt_UsingFixedFunction)
        BckLftCnt_CONTROL &= ((uint8)(~BckLftCnt_CTRL_ENABLE));        
    #endif /* (!BckLftCnt_ControlRegRemoved || BckLftCnt_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (BckLftCnt_UsingFixedFunction)
        BckLftCnt_GLOBAL_ENABLE &= ((uint8)(~BckLftCnt_BLOCK_EN_MASK));
        BckLftCnt_GLOBAL_STBY_ENABLE &= ((uint8)(~BckLftCnt_BLOCK_STBY_EN_MASK));
    #endif /* (BckLftCnt_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BckLftCnt_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void BckLftCnt_SetInterruptMode(uint8 interruptsMask) 
{
    BckLftCnt_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: BckLftCnt_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   BckLftCnt_ReadStatusRegister(void) 
{
    return BckLftCnt_STATUS;
}


#if(!BckLftCnt_ControlRegRemoved)
/*******************************************************************************
* Function Name: BckLftCnt_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   BckLftCnt_ReadControlRegister(void) 
{
    return BckLftCnt_CONTROL;
}


/*******************************************************************************
* Function Name: BckLftCnt_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    BckLftCnt_WriteControlRegister(uint8 control) 
{
    BckLftCnt_CONTROL = control;
}

#endif  /* (!BckLftCnt_ControlRegRemoved) */


#if (!(BckLftCnt_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: BckLftCnt_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void BckLftCnt_WriteCounter(uint8 counter) \
                                   
{
    #if(BckLftCnt_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (BckLftCnt_GLOBAL_ENABLE & BckLftCnt_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        BckLftCnt_GLOBAL_ENABLE |= BckLftCnt_BLOCK_EN_MASK;
        CY_SET_REG16(BckLftCnt_COUNTER_LSB_PTR, (uint16)counter);
        BckLftCnt_GLOBAL_ENABLE &= ((uint8)(~BckLftCnt_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(BckLftCnt_COUNTER_LSB_PTR, counter);
    #endif /* (BckLftCnt_UsingFixedFunction) */
}
#endif /* (!(BckLftCnt_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: BckLftCnt_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 BckLftCnt_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(BckLftCnt_UsingFixedFunction)
		(void)CY_GET_REG16(BckLftCnt_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(BckLftCnt_COUNTER_LSB_PTR_8BIT);
	#endif/* (BckLftCnt_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(BckLftCnt_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(BckLftCnt_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(BckLftCnt_STATICCOUNT_LSB_PTR));
    #endif /* (BckLftCnt_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BckLftCnt_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 BckLftCnt_ReadCapture(void) 
{
    #if(BckLftCnt_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(BckLftCnt_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(BckLftCnt_STATICCOUNT_LSB_PTR));
    #endif /* (BckLftCnt_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BckLftCnt_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void BckLftCnt_WritePeriod(uint8 period) 
{
    #if(BckLftCnt_UsingFixedFunction)
        CY_SET_REG16(BckLftCnt_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(BckLftCnt_PERIOD_LSB_PTR, period);
    #endif /* (BckLftCnt_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BckLftCnt_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 BckLftCnt_ReadPeriod(void) 
{
    #if(BckLftCnt_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(BckLftCnt_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(BckLftCnt_PERIOD_LSB_PTR));
    #endif /* (BckLftCnt_UsingFixedFunction) */
}


#if (!BckLftCnt_UsingFixedFunction)
/*******************************************************************************
* Function Name: BckLftCnt_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void BckLftCnt_WriteCompare(uint8 compare) \
                                   
{
    #if(BckLftCnt_UsingFixedFunction)
        CY_SET_REG16(BckLftCnt_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(BckLftCnt_COMPARE_LSB_PTR, compare);
    #endif /* (BckLftCnt_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BckLftCnt_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 BckLftCnt_ReadCompare(void) 
{
    return (CY_GET_REG8(BckLftCnt_COMPARE_LSB_PTR));
}


#if (BckLftCnt_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: BckLftCnt_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void BckLftCnt_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    BckLftCnt_CONTROL &= ((uint8)(~BckLftCnt_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    BckLftCnt_CONTROL |= compareMode;
}
#endif  /* (BckLftCnt_COMPARE_MODE_SOFTWARE) */


#if (BckLftCnt_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: BckLftCnt_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void BckLftCnt_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    BckLftCnt_CONTROL &= ((uint8)(~BckLftCnt_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    BckLftCnt_CONTROL |= ((uint8)((uint8)captureMode << BckLftCnt_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (BckLftCnt_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: BckLftCnt_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void BckLftCnt_ClearFIFO(void) 
{

    while(0u != (BckLftCnt_ReadStatusRegister() & BckLftCnt_STATUS_FIFONEMP))
    {
        (void)BckLftCnt_ReadCapture();
    }

}
#endif  /* (!BckLftCnt_UsingFixedFunction) */


/* [] END OF FILE */

