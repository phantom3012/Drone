/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_I2C_LiDAR_H)
#define CY_SCB_PVT_I2C_LiDAR_H

#include "I2C_LiDAR.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define I2C_LiDAR_SetI2CExtClkInterruptMode(interruptMask) I2C_LiDAR_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define I2C_LiDAR_ClearI2CExtClkInterruptSource(interruptMask) I2C_LiDAR_CLEAR_INTR_I2C_EC(interruptMask)
#define I2C_LiDAR_GetI2CExtClkInterruptSource()                (I2C_LiDAR_INTR_I2C_EC_REG)
#define I2C_LiDAR_GetI2CExtClkInterruptMode()                  (I2C_LiDAR_INTR_I2C_EC_MASK_REG)
#define I2C_LiDAR_GetI2CExtClkInterruptSourceMasked()          (I2C_LiDAR_INTR_I2C_EC_MASKED_REG)

#if (!I2C_LiDAR_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define I2C_LiDAR_SetSpiExtClkInterruptMode(interruptMask) \
                                                                I2C_LiDAR_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define I2C_LiDAR_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                I2C_LiDAR_CLEAR_INTR_SPI_EC(interruptMask)
    #define I2C_LiDAR_GetExtSpiClkInterruptSource()                 (I2C_LiDAR_INTR_SPI_EC_REG)
    #define I2C_LiDAR_GetExtSpiClkInterruptMode()                   (I2C_LiDAR_INTR_SPI_EC_MASK_REG)
    #define I2C_LiDAR_GetExtSpiClkInterruptSourceMasked()           (I2C_LiDAR_INTR_SPI_EC_MASKED_REG)
#endif /* (!I2C_LiDAR_CY_SCBIP_V1) */

#if(I2C_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void I2C_LiDAR_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (I2C_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (I2C_LiDAR_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_I2C_LiDAR_CUSTOM_INTR_HANDLER)
    extern cyisraddress I2C_LiDAR_customIntrHandler;
#endif /* !defined (CY_REMOVE_I2C_LiDAR_CUSTOM_INTR_HANDLER) */
#endif /* (I2C_LiDAR_SCB_IRQ_INTERNAL) */

extern I2C_LiDAR_BACKUP_STRUCT I2C_LiDAR_backup;

#if(I2C_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 I2C_LiDAR_scbMode;
    extern uint8 I2C_LiDAR_scbEnableWake;
    extern uint8 I2C_LiDAR_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 I2C_LiDAR_mode;
    extern uint8 I2C_LiDAR_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * I2C_LiDAR_rxBuffer;
    extern uint8   I2C_LiDAR_rxDataBits;
    extern uint32  I2C_LiDAR_rxBufferSize;

    extern volatile uint8 * I2C_LiDAR_txBuffer;
    extern uint8   I2C_LiDAR_txDataBits;
    extern uint32  I2C_LiDAR_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 I2C_LiDAR_numberOfAddr;
    extern uint8 I2C_LiDAR_subAddrSize;
#endif /* (I2C_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (I2C_LiDAR_SCB_MODE_I2C_CONST_CFG || \
        I2C_LiDAR_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 I2C_LiDAR_IntrTxMask;
#endif /* (! (I2C_LiDAR_SCB_MODE_I2C_CONST_CFG || \
              I2C_LiDAR_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(I2C_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define I2C_LiDAR_SCB_MODE_I2C_RUNTM_CFG     (I2C_LiDAR_SCB_MODE_I2C      == I2C_LiDAR_scbMode)
    #define I2C_LiDAR_SCB_MODE_SPI_RUNTM_CFG     (I2C_LiDAR_SCB_MODE_SPI      == I2C_LiDAR_scbMode)
    #define I2C_LiDAR_SCB_MODE_UART_RUNTM_CFG    (I2C_LiDAR_SCB_MODE_UART     == I2C_LiDAR_scbMode)
    #define I2C_LiDAR_SCB_MODE_EZI2C_RUNTM_CFG   (I2C_LiDAR_SCB_MODE_EZI2C    == I2C_LiDAR_scbMode)
    #define I2C_LiDAR_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (I2C_LiDAR_SCB_MODE_UNCONFIG == I2C_LiDAR_scbMode)

    /* Defines wakeup enable */
    #define I2C_LiDAR_SCB_WAKE_ENABLE_CHECK       (0u != I2C_LiDAR_scbEnableWake)
#endif /* (I2C_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!I2C_LiDAR_CY_SCBIP_V1)
    #define I2C_LiDAR_SCB_PINS_NUMBER    (7u)
#else
    #define I2C_LiDAR_SCB_PINS_NUMBER    (2u)
#endif /* (!I2C_LiDAR_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_I2C_LiDAR_H) */


/* [] END OF FILE */
