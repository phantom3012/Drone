/*******************************************************************************
* File Name: FRNTLFT_ESC_PM.c
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

#include "FRNTLFT_ESC.h"

static FRNTLFT_ESC_BACKUP_STRUCT FRNTLFT_ESC_backup;


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SaveConfig
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
void FRNTLFT_ESC_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_Sleep
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
void FRNTLFT_ESC_Sleep(void)
{
    if(0u != (FRNTLFT_ESC_BLOCK_CONTROL_REG & FRNTLFT_ESC_MASK))
    {
        FRNTLFT_ESC_backup.enableState = 1u;
    }
    else
    {
        FRNTLFT_ESC_backup.enableState = 0u;
    }

    FRNTLFT_ESC_Stop();
    FRNTLFT_ESC_SaveConfig();
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_RestoreConfig
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
void FRNTLFT_ESC_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_Wakeup
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
void FRNTLFT_ESC_Wakeup(void)
{
    FRNTLFT_ESC_RestoreConfig();

    if(0u != FRNTLFT_ESC_backup.enableState)
    {
        FRNTLFT_ESC_Enable();
    }
}


/* [] END OF FILE */
