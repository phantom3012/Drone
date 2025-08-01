/*******************************************************************************
* File Name: TMR_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TMR.h"

static TMR_BACKUP_STRUCT TMR_backup;


/*******************************************************************************
* Function Name: TMR_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: TMR_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TMR_Sleep(void)
{
    if(0u != (TMR_BLOCK_CONTROL_REG & TMR_MASK))
    {
        TMR_backup.enableState = 1u;
    }
    else
    {
        TMR_backup.enableState = 0u;
    }

    TMR_Stop();
    TMR_SaveConfig();
}


/*******************************************************************************
* Function Name: TMR_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TMR_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: TMR_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TMR_Wakeup(void)
{
    TMR_RestoreConfig();

    if(0u != TMR_backup.enableState)
    {
        TMR_Enable();
    }
}


/* [] END OF FILE */
