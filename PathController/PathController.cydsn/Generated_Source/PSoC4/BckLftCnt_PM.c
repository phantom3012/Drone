/*******************************************************************************
* File Name: BckLftCnt_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
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

static BckLftCnt_backupStruct BckLftCnt_backup;


/*******************************************************************************
* Function Name: BckLftCnt_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  BckLftCnt_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void BckLftCnt_SaveConfig(void) 
{
    #if (!BckLftCnt_UsingFixedFunction)

        BckLftCnt_backup.CounterUdb = BckLftCnt_ReadCounter();

        #if(!BckLftCnt_ControlRegRemoved)
            BckLftCnt_backup.CounterControlRegister = BckLftCnt_ReadControlRegister();
        #endif /* (!BckLftCnt_ControlRegRemoved) */

    #endif /* (!BckLftCnt_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BckLftCnt_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  BckLftCnt_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BckLftCnt_RestoreConfig(void) 
{      
    #if (!BckLftCnt_UsingFixedFunction)

       BckLftCnt_WriteCounter(BckLftCnt_backup.CounterUdb);

        #if(!BckLftCnt_ControlRegRemoved)
            BckLftCnt_WriteControlRegister(BckLftCnt_backup.CounterControlRegister);
        #endif /* (!BckLftCnt_ControlRegRemoved) */

    #endif /* (!BckLftCnt_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BckLftCnt_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  BckLftCnt_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void BckLftCnt_Sleep(void) 
{
    #if(!BckLftCnt_ControlRegRemoved)
        /* Save Counter's enable state */
        if(BckLftCnt_CTRL_ENABLE == (BckLftCnt_CONTROL & BckLftCnt_CTRL_ENABLE))
        {
            /* Counter is enabled */
            BckLftCnt_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            BckLftCnt_backup.CounterEnableState = 0u;
        }
    #else
        BckLftCnt_backup.CounterEnableState = 1u;
        if(BckLftCnt_backup.CounterEnableState != 0u)
        {
            BckLftCnt_backup.CounterEnableState = 0u;
        }
    #endif /* (!BckLftCnt_ControlRegRemoved) */
    
    BckLftCnt_Stop();
    BckLftCnt_SaveConfig();
}


/*******************************************************************************
* Function Name: BckLftCnt_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  BckLftCnt_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BckLftCnt_Wakeup(void) 
{
    BckLftCnt_RestoreConfig();
    #if(!BckLftCnt_ControlRegRemoved)
        if(BckLftCnt_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            BckLftCnt_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!BckLftCnt_ControlRegRemoved) */
    
}


/* [] END OF FILE */
