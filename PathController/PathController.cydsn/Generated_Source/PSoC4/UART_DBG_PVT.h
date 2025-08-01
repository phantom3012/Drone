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

#if !defined(CY_SCB_PVT_UART_DBG_H)
#define CY_SCB_PVT_UART_DBG_H

#include "UART_DBG.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_DBG_SetI2CExtClkInterruptMode(interruptMask) UART_DBG_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_DBG_ClearI2CExtClkInterruptSource(interruptMask) UART_DBG_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_DBG_GetI2CExtClkInterruptSource()                (UART_DBG_INTR_I2C_EC_REG)
#define UART_DBG_GetI2CExtClkInterruptMode()                  (UART_DBG_INTR_I2C_EC_MASK_REG)
#define UART_DBG_GetI2CExtClkInterruptSourceMasked()          (UART_DBG_INTR_I2C_EC_MASKED_REG)

#if (!UART_DBG_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_DBG_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_DBG_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_DBG_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_DBG_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_DBG_GetExtSpiClkInterruptSource()                 (UART_DBG_INTR_SPI_EC_REG)
    #define UART_DBG_GetExtSpiClkInterruptMode()                   (UART_DBG_INTR_SPI_EC_MASK_REG)
    #define UART_DBG_GetExtSpiClkInterruptSourceMasked()           (UART_DBG_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_DBG_CY_SCBIP_V1) */

#if(UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_DBG_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_DBG_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_DBG_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_DBG_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_DBG_CUSTOM_INTR_HANDLER) */
#endif /* (UART_DBG_SCB_IRQ_INTERNAL) */

extern UART_DBG_BACKUP_STRUCT UART_DBG_backup;

#if(UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_DBG_scbMode;
    extern uint8 UART_DBG_scbEnableWake;
    extern uint8 UART_DBG_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_DBG_mode;
    extern uint8 UART_DBG_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_DBG_rxBuffer;
    extern uint8   UART_DBG_rxDataBits;
    extern uint32  UART_DBG_rxBufferSize;

    extern volatile uint8 * UART_DBG_txBuffer;
    extern uint8   UART_DBG_txDataBits;
    extern uint32  UART_DBG_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_DBG_numberOfAddr;
    extern uint8 UART_DBG_subAddrSize;
#endif /* (UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_DBG_SCB_MODE_I2C_CONST_CFG || \
        UART_DBG_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_DBG_IntrTxMask;
#endif /* (! (UART_DBG_SCB_MODE_I2C_CONST_CFG || \
              UART_DBG_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_DBG_SCB_MODE_I2C_RUNTM_CFG     (UART_DBG_SCB_MODE_I2C      == UART_DBG_scbMode)
    #define UART_DBG_SCB_MODE_SPI_RUNTM_CFG     (UART_DBG_SCB_MODE_SPI      == UART_DBG_scbMode)
    #define UART_DBG_SCB_MODE_UART_RUNTM_CFG    (UART_DBG_SCB_MODE_UART     == UART_DBG_scbMode)
    #define UART_DBG_SCB_MODE_EZI2C_RUNTM_CFG   (UART_DBG_SCB_MODE_EZI2C    == UART_DBG_scbMode)
    #define UART_DBG_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_DBG_SCB_MODE_UNCONFIG == UART_DBG_scbMode)

    /* Defines wakeup enable */
    #define UART_DBG_SCB_WAKE_ENABLE_CHECK       (0u != UART_DBG_scbEnableWake)
#endif /* (UART_DBG_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_DBG_CY_SCBIP_V1)
    #define UART_DBG_SCB_PINS_NUMBER    (7u)
#else
    #define UART_DBG_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_DBG_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_DBG_H) */


/* [] END OF FILE */
