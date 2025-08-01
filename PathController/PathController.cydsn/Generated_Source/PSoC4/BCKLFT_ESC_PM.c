/*******************************************************************************
* File Name: BCKLFT_ESC_PM.c
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

#include "BCKLFT_ESC.h"

static BCKLFT_ESC_BACKUP_STRUCT BCKLFT_ESC_backup;


/*******************************************************************************
* Function Name: BCKLFT_ESC_SaveConfig
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
void BCKLFT_ESC_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: BCKLFT_ESC_Sleep
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
void BCKLFT_ESC_Sleep(void)
{
    if(0u != (BCKLFT_ESC_BLOCK_CONTROL_REG & BCKLFT_ESC_MASK))
    {
        BCKLFT_ESC_backup.enableState = 1u;
    }
    else
    {
        BCKLFT_ESC_backup.enableState = 0u;
    }

    BCKLFT_ESC_Stop();
    BCKLFT_ESC_SaveConfig();
}


/*******************************************************************************
* Function Name: BCKLFT_ESC_RestoreConfig
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
void BCKLFT_ESC_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: BCKLFT_ESC_Wakeup
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
void BCKLFT_ESC_Wakeup(void)
{
    BCKLFT_ESC_RestoreConfig();

    if(0u != BCKLFT_ESC_backup.enableState)
    {
        BCKLFT_ESC_Enable();
    }
}


/* [] END OF FILE */
