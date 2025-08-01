/*******************************************************************************
* File Name: A2D_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "A2D.h"


/***************************************
* Local data allocation
***************************************/

static A2D_BACKUP_STRUCT  A2D_backup =
{
    A2D_DISABLED,
    0u    
};


/*******************************************************************************
* Function Name: A2D_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void A2D_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: A2D_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void A2D_RestoreConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: A2D_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  A2D_backup - modified.
*
*******************************************************************************/
void A2D_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    A2D_backup.dftRegVal = A2D_SAR_DFT_CTRL_REG & (uint32)~A2D_ADFT_OVERRIDE;
    A2D_SAR_DFT_CTRL_REG |= A2D_ADFT_OVERRIDE;
    if((A2D_SAR_CTRL_REG  & A2D_ENABLE) != 0u)
    {
        if((A2D_SAR_SAMPLE_CTRL_REG & A2D_CONTINUOUS_EN) != 0u)
        {
            A2D_backup.enableState = A2D_ENABLED | A2D_STARTED;
        }
        else
        {
            A2D_backup.enableState = A2D_ENABLED;
        }
        A2D_StopConvert();
        A2D_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((A2D_SAR_CTRL_REG & A2D_BOOSTPUMP_EN) != 0u)
        {
            A2D_SAR_CTRL_REG &= (uint32)~A2D_BOOSTPUMP_EN;
            A2D_backup.enableState |= A2D_BOOSTPUMP_ENABLED;
        }
    }
    else
    {
        A2D_backup.enableState = A2D_DISABLED;
    }
}


/*******************************************************************************
* Function Name: A2D_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  A2D_backup - used.
*
*******************************************************************************/
void A2D_Wakeup(void)
{
    A2D_SAR_DFT_CTRL_REG = A2D_backup.dftRegVal;
    if(A2D_backup.enableState != A2D_DISABLED)
    {
        /* Enable the SAR internal pump  */
        if((A2D_backup.enableState & A2D_BOOSTPUMP_ENABLED) != 0u)
        {
            A2D_SAR_CTRL_REG |= A2D_BOOSTPUMP_EN;
        }
        A2D_Enable();
        if((A2D_backup.enableState & A2D_STARTED) != 0u)
        {
            A2D_StartConvert();
        }
    }
}
/* [] END OF FILE */
