/*******************************************************************************
* File Name: BCKRGHT_ESC_PM.c
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

#include "BCKRGHT_ESC.h"

static BCKRGHT_ESC_BACKUP_STRUCT BCKRGHT_ESC_backup;


/*******************************************************************************
* Function Name: BCKRGHT_ESC_SaveConfig
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
void BCKRGHT_ESC_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: BCKRGHT_ESC_Sleep
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
void BCKRGHT_ESC_Sleep(void)
{
    if(0u != (BCKRGHT_ESC_BLOCK_CONTROL_REG & BCKRGHT_ESC_MASK))
    {
        BCKRGHT_ESC_backup.enableState = 1u;
    }
    else
    {
        BCKRGHT_ESC_backup.enableState = 0u;
    }

    BCKRGHT_ESC_Stop();
    BCKRGHT_ESC_SaveConfig();
}


/*******************************************************************************
* Function Name: BCKRGHT_ESC_RestoreConfig
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
void BCKRGHT_ESC_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: BCKRGHT_ESC_Wakeup
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
void BCKRGHT_ESC_Wakeup(void)
{
    BCKRGHT_ESC_RestoreConfig();

    if(0u != BCKRGHT_ESC_backup.enableState)
    {
        BCKRGHT_ESC_Enable();
    }
}


/* [] END OF FILE */
