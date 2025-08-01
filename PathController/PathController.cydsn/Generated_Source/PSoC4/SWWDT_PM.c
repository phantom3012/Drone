/*******************************************************************************
* File Name: SWWDT_PM.c
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

#include "SWWDT.h"

static SWWDT_BACKUP_STRUCT SWWDT_backup;


/*******************************************************************************
* Function Name: SWWDT_SaveConfig
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
void SWWDT_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: SWWDT_Sleep
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
void SWWDT_Sleep(void)
{
    if(0u != (SWWDT_BLOCK_CONTROL_REG & SWWDT_MASK))
    {
        SWWDT_backup.enableState = 1u;
    }
    else
    {
        SWWDT_backup.enableState = 0u;
    }

    SWWDT_Stop();
    SWWDT_SaveConfig();
}


/*******************************************************************************
* Function Name: SWWDT_RestoreConfig
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
void SWWDT_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: SWWDT_Wakeup
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
void SWWDT_Wakeup(void)
{
    SWWDT_RestoreConfig();

    if(0u != SWWDT_backup.enableState)
    {
        SWWDT_Enable();
    }
}


/* [] END OF FILE */
