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

#if !defined(CY_SCB_PVT_UART_FC_H)
#define CY_SCB_PVT_UART_FC_H

#include "UART_FC.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_FC_SetI2CExtClkInterruptMode(interruptMask) UART_FC_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_FC_ClearI2CExtClkInterruptSource(interruptMask) UART_FC_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_FC_GetI2CExtClkInterruptSource()                (UART_FC_INTR_I2C_EC_REG)
#define UART_FC_GetI2CExtClkInterruptMode()                  (UART_FC_INTR_I2C_EC_MASK_REG)
#define UART_FC_GetI2CExtClkInterruptSourceMasked()          (UART_FC_INTR_I2C_EC_MASKED_REG)

#if (!UART_FC_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_FC_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_FC_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_FC_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_FC_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_FC_GetExtSpiClkInterruptSource()                 (UART_FC_INTR_SPI_EC_REG)
    #define UART_FC_GetExtSpiClkInterruptMode()                   (UART_FC_INTR_SPI_EC_MASK_REG)
    #define UART_FC_GetExtSpiClkInterruptSourceMasked()           (UART_FC_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_FC_CY_SCBIP_V1) */

#if(UART_FC_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_FC_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_FC_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_FC_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_FC_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_FC_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_FC_CUSTOM_INTR_HANDLER) */
#endif /* (UART_FC_SCB_IRQ_INTERNAL) */

extern UART_FC_BACKUP_STRUCT UART_FC_backup;

#if(UART_FC_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_FC_scbMode;
    extern uint8 UART_FC_scbEnableWake;
    extern uint8 UART_FC_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_FC_mode;
    extern uint8 UART_FC_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_FC_rxBuffer;
    extern uint8   UART_FC_rxDataBits;
    extern uint32  UART_FC_rxBufferSize;

    extern volatile uint8 * UART_FC_txBuffer;
    extern uint8   UART_FC_txDataBits;
    extern uint32  UART_FC_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_FC_numberOfAddr;
    extern uint8 UART_FC_subAddrSize;
#endif /* (UART_FC_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_FC_SCB_MODE_I2C_CONST_CFG || \
        UART_FC_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_FC_IntrTxMask;
#endif /* (! (UART_FC_SCB_MODE_I2C_CONST_CFG || \
              UART_FC_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_FC_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_FC_SCB_MODE_I2C_RUNTM_CFG     (UART_FC_SCB_MODE_I2C      == UART_FC_scbMode)
    #define UART_FC_SCB_MODE_SPI_RUNTM_CFG     (UART_FC_SCB_MODE_SPI      == UART_FC_scbMode)
    #define UART_FC_SCB_MODE_UART_RUNTM_CFG    (UART_FC_SCB_MODE_UART     == UART_FC_scbMode)
    #define UART_FC_SCB_MODE_EZI2C_RUNTM_CFG   (UART_FC_SCB_MODE_EZI2C    == UART_FC_scbMode)
    #define UART_FC_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_FC_SCB_MODE_UNCONFIG == UART_FC_scbMode)

    /* Defines wakeup enable */
    #define UART_FC_SCB_WAKE_ENABLE_CHECK       (0u != UART_FC_scbEnableWake)
#endif /* (UART_FC_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_FC_CY_SCBIP_V1)
    #define UART_FC_SCB_PINS_NUMBER    (7u)
#else
    #define UART_FC_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_FC_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_FC_H) */


/* [] END OF FILE */
