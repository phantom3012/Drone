/*******************************************************************************
* File Name: RGHT_ESC_PM.c
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

#include "RGHT_ESC.h"

static RGHT_ESC_BACKUP_STRUCT RGHT_ESC_backup;


/*******************************************************************************
* Function Name: RGHT_ESC_SaveConfig
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
void RGHT_ESC_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: RGHT_ESC_Sleep
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
void RGHT_ESC_Sleep(void)
{
    if(0u != (RGHT_ESC_BLOCK_CONTROL_REG & RGHT_ESC_MASK))
    {
        RGHT_ESC_backup.enableState = 1u;
    }
    else
    {
        RGHT_ESC_backup.enableState = 0u;
    }

    RGHT_ESC_Stop();
    RGHT_ESC_SaveConfig();
}


/*******************************************************************************
* Function Name: RGHT_ESC_RestoreConfig
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
void RGHT_ESC_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: RGHT_ESC_Wakeup
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
void RGHT_ESC_Wakeup(void)
{
    RGHT_ESC_RestoreConfig();

    if(0u != RGHT_ESC_backup.enableState)
    {
        RGHT_ESC_Enable();
    }
}


/* [] END OF FILE */
