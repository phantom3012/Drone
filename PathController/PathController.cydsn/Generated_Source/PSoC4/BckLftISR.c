/*******************************************************************************
* File Name: BckLftISR.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <BckLftISR.h>
#include "cyapicallbacks.h"

#if !defined(BckLftISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START BckLftISR_intc` */
 #include "main.h"
/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: BckLftISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void BckLftISR_Start(void)
{
    /* For all we know the interrupt is active. */
    BckLftISR_Disable();

    /* Set the ISR to point to the BckLftISR Interrupt. */
    BckLftISR_SetVector(&BckLftISR_Interrupt);

    /* Set the priority. */
    BckLftISR_SetPriority((uint8)BckLftISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    BckLftISR_Enable();
}


/*******************************************************************************
* Function Name: BckLftISR_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void BckLftISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    BckLftISR_Disable();

    /* Set the ISR to point to the BckLftISR Interrupt. */
    BckLftISR_SetVector(address);

    /* Set the priority. */
    BckLftISR_SetPriority((uint8)BckLftISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    BckLftISR_Enable();
}


/*******************************************************************************
* Function Name: BckLftISR_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void BckLftISR_Stop(void)
{
    /* Disable this interrupt. */
    BckLftISR_Disable();

    /* Set the ISR to point to the passive one. */
    BckLftISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: BckLftISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for BckLftISR.
*
*   Add custom code between the START and END comments to keep the next version
*   of this file from over-writing your code.
*
*   Note You may use either the default ISR by using this API, or you may define
*   your own separate ISR through ISR_StartEx().
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(BckLftISR_Interrupt)
{
    #ifdef BckLftISR_INTERRUPT_INTERRUPT_CALLBACK
        BckLftISR_Interrupt_InterruptCallback();
    #endif /* BckLftISR_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START BckLftISR_Interrupt` */
    motor_toggles++;
    BckLftISR_ClearPending();
    /* `#END` */
}


/*******************************************************************************
* Function Name: BckLftISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling BckLftISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use BckLftISR_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void BckLftISR_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + BckLftISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: BckLftISR_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress BckLftISR_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + BckLftISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: BckLftISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling BckLftISR_Start or BckLftISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after BckLftISR_Start or BckLftISR_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void BckLftISR_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((BckLftISR__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *BckLftISR_INTC_PRIOR = (*BckLftISR_INTC_PRIOR & (uint32)(~BckLftISR__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: BckLftISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 BckLftISR_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((BckLftISR__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*BckLftISR_INTC_PRIOR & BckLftISR__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: BckLftISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void BckLftISR_Enable(void)
{
    /* Enable the general interrupt. */
    *BckLftISR_INTC_SET_EN = BckLftISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: BckLftISR_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 BckLftISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*BckLftISR_INTC_SET_EN & (uint32)BckLftISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: BckLftISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void BckLftISR_Disable(void)
{
    /* Disable the general interrupt. */
    *BckLftISR_INTC_CLR_EN = BckLftISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: BckLftISR_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void BckLftISR_SetPending(void)
{
    *BckLftISR_INTC_SET_PD = BckLftISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: BckLftISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void BckLftISR_ClearPending(void)
{
    *BckLftISR_INTC_CLR_PD = BckLftISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
