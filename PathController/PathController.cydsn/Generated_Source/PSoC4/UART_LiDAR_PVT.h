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

#if !defined(CY_SCB_PVT_UART_LiDAR_H)
#define CY_SCB_PVT_UART_LiDAR_H

#include "UART_LiDAR.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_LiDAR_SetI2CExtClkInterruptMode(interruptMask) UART_LiDAR_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_LiDAR_ClearI2CExtClkInterruptSource(interruptMask) UART_LiDAR_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_LiDAR_GetI2CExtClkInterruptSource()                (UART_LiDAR_INTR_I2C_EC_REG)
#define UART_LiDAR_GetI2CExtClkInterruptMode()                  (UART_LiDAR_INTR_I2C_EC_MASK_REG)
#define UART_LiDAR_GetI2CExtClkInterruptSourceMasked()          (UART_LiDAR_INTR_I2C_EC_MASKED_REG)

#if (!UART_LiDAR_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_LiDAR_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_LiDAR_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_LiDAR_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_LiDAR_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_LiDAR_GetExtSpiClkInterruptSource()                 (UART_LiDAR_INTR_SPI_EC_REG)
    #define UART_LiDAR_GetExtSpiClkInterruptMode()                   (UART_LiDAR_INTR_SPI_EC_MASK_REG)
    #define UART_LiDAR_GetExtSpiClkInterruptSourceMasked()           (UART_LiDAR_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_LiDAR_CY_SCBIP_V1) */

#if(UART_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_LiDAR_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_LiDAR_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_LiDAR_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_LiDAR_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_LiDAR_CUSTOM_INTR_HANDLER) */
#endif /* (UART_LiDAR_SCB_IRQ_INTERNAL) */

extern UART_LiDAR_BACKUP_STRUCT UART_LiDAR_backup;

#if(UART_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_LiDAR_scbMode;
    extern uint8 UART_LiDAR_scbEnableWake;
    extern uint8 UART_LiDAR_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_LiDAR_mode;
    extern uint8 UART_LiDAR_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_LiDAR_rxBuffer;
    extern uint8   UART_LiDAR_rxDataBits;
    extern uint32  UART_LiDAR_rxBufferSize;

    extern volatile uint8 * UART_LiDAR_txBuffer;
    extern uint8   UART_LiDAR_txDataBits;
    extern uint32  UART_LiDAR_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_LiDAR_numberOfAddr;
    extern uint8 UART_LiDAR_subAddrSize;
#endif /* (UART_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_LiDAR_SCB_MODE_I2C_CONST_CFG || \
        UART_LiDAR_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_LiDAR_IntrTxMask;
#endif /* (! (UART_LiDAR_SCB_MODE_I2C_CONST_CFG || \
              UART_LiDAR_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_LiDAR_SCB_MODE_I2C_RUNTM_CFG     (UART_LiDAR_SCB_MODE_I2C      == UART_LiDAR_scbMode)
    #define UART_LiDAR_SCB_MODE_SPI_RUNTM_CFG     (UART_LiDAR_SCB_MODE_SPI      == UART_LiDAR_scbMode)
    #define UART_LiDAR_SCB_MODE_UART_RUNTM_CFG    (UART_LiDAR_SCB_MODE_UART     == UART_LiDAR_scbMode)
    #define UART_LiDAR_SCB_MODE_EZI2C_RUNTM_CFG   (UART_LiDAR_SCB_MODE_EZI2C    == UART_LiDAR_scbMode)
    #define UART_LiDAR_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_LiDAR_SCB_MODE_UNCONFIG == UART_LiDAR_scbMode)

    /* Defines wakeup enable */
    #define UART_LiDAR_SCB_WAKE_ENABLE_CHECK       (0u != UART_LiDAR_scbEnableWake)
#endif /* (UART_LiDAR_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_LiDAR_CY_SCBIP_V1)
    #define UART_LiDAR_SCB_PINS_NUMBER    (7u)
#else
    #define UART_LiDAR_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_LiDAR_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_LiDAR_H) */


/* [] END OF FILE */
