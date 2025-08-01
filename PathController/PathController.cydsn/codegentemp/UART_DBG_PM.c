/***************************************************************************//**
* \file UART_DBG_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_DBG.h"
#include "UART_DBG_PVT.h"

#if(UART_DBG_SCB_MODE_I2C_INC)
    #include "UART_DBG_I2C_PVT.h"
#endif /* (UART_DBG_SCB_MODE_I2C_INC) */

#if(UART_DBG_SCB_MODE_EZI2C_INC)
    #include "UART_DBG_EZI2C_PVT.h"
#endif /* (UART_DBG_SCB_MODE_EZI2C_INC) */

#if(UART_DBG_SCB_MODE_SPI_INC || UART_DBG_SCB_MODE_UART_INC)
    #include "UART_DBG_SPI_UART_PVT.h"
#endif /* (UART_DBG_SCB_MODE_SPI_INC || UART_DBG_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_DBG_SCB_MODE_I2C_CONST_CFG   && (!UART_DBG_I2C_WAKE_ENABLE_CONST))   || \
   (UART_DBG_SCB_MODE_EZI2C_CONST_CFG && (!UART_DBG_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_DBG_SCB_MODE_SPI_CONST_CFG   && (!UART_DBG_SPI_WAKE_ENABLE_CONST))   || \
   (UART_DBG_SCB_MODE_UART_CONST_CFG  && (!UART_DBG_UART_WAKE_ENABLE_CONST)))

    UART_DBG_BACKUP_STRUCT UART_DBG_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_DBG_Sleep
****************************************************************************//**
*
*  Prepares the UART_DBG component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the UART_DBG_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void UART_DBG_Sleep(void)
{
#if(UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_DBG_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_DBG_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_DBG_I2CSaveConfig();
        }
        else if(UART_DBG_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_DBG_EzI2CSaveConfig();
        }
    #if(!UART_DBG_CY_SCBIP_V1)
        else if(UART_DBG_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_DBG_SpiSaveConfig();
        }
        else if(UART_DBG_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_DBG_UartSaveConfig();
        }
    #endif /* (!UART_DBG_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_DBG_backup.enableState = (uint8) UART_DBG_GET_CTRL_ENABLED;

        if(0u != UART_DBG_backup.enableState)
        {
            UART_DBG_Stop();
        }
    }

#else

    #if (UART_DBG_SCB_MODE_I2C_CONST_CFG && UART_DBG_I2C_WAKE_ENABLE_CONST)
        UART_DBG_I2CSaveConfig();

    #elif (UART_DBG_SCB_MODE_EZI2C_CONST_CFG && UART_DBG_EZI2C_WAKE_ENABLE_CONST)
        UART_DBG_EzI2CSaveConfig();

    #elif (UART_DBG_SCB_MODE_SPI_CONST_CFG && UART_DBG_SPI_WAKE_ENABLE_CONST)
        UART_DBG_SpiSaveConfig();

    #elif (UART_DBG_SCB_MODE_UART_CONST_CFG && UART_DBG_UART_WAKE_ENABLE_CONST)
        UART_DBG_UartSaveConfig();

    #else

        UART_DBG_backup.enableState = (uint8) UART_DBG_GET_CTRL_ENABLED;

        if(0u != UART_DBG_backup.enableState)
        {
            UART_DBG_Stop();
        }

    #endif /* defined (UART_DBG_SCB_MODE_I2C_CONST_CFG) && (UART_DBG_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_DBG_Wakeup
****************************************************************************//**
*
*  Prepares the UART_DBG component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the UART_DBG_Wakeup() function without first calling the 
*   UART_DBG_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void UART_DBG_Wakeup(void)
{
#if(UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_DBG_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_DBG_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_DBG_I2CRestoreConfig();
        }
        else if(UART_DBG_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_DBG_EzI2CRestoreConfig();
        }
    #if(!UART_DBG_CY_SCBIP_V1)
        else if(UART_DBG_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_DBG_SpiRestoreConfig();
        }
        else if(UART_DBG_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_DBG_UartRestoreConfig();
        }
    #endif /* (!UART_DBG_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_DBG_backup.enableState)
        {
            UART_DBG_Enable();
        }
    }

#else

    #if (UART_DBG_SCB_MODE_I2C_CONST_CFG  && UART_DBG_I2C_WAKE_ENABLE_CONST)
        UART_DBG_I2CRestoreConfig();

    #elif (UART_DBG_SCB_MODE_EZI2C_CONST_CFG && UART_DBG_EZI2C_WAKE_ENABLE_CONST)
        UART_DBG_EzI2CRestoreConfig();

    #elif (UART_DBG_SCB_MODE_SPI_CONST_CFG && UART_DBG_SPI_WAKE_ENABLE_CONST)
        UART_DBG_SpiRestoreConfig();

    #elif (UART_DBG_SCB_MODE_UART_CONST_CFG && UART_DBG_UART_WAKE_ENABLE_CONST)
        UART_DBG_UartRestoreConfig();

    #else

        if(0u != UART_DBG_backup.enableState)
        {
            UART_DBG_Enable();
        }

    #endif /* (UART_DBG_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
