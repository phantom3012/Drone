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

#if !defined(CY_SCB_PVT_UART_GPS_H)
#define CY_SCB_PVT_UART_GPS_H

#include "UART_GPS.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_GPS_SetI2CExtClkInterruptMode(interruptMask) UART_GPS_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_GPS_ClearI2CExtClkInterruptSource(interruptMask) UART_GPS_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_GPS_GetI2CExtClkInterruptSource()                (UART_GPS_INTR_I2C_EC_REG)
#define UART_GPS_GetI2CExtClkInterruptMode()                  (UART_GPS_INTR_I2C_EC_MASK_REG)
#define UART_GPS_GetI2CExtClkInterruptSourceMasked()          (UART_GPS_INTR_I2C_EC_MASKED_REG)

#if (!UART_GPS_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_GPS_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_GPS_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_GPS_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_GPS_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_GPS_GetExtSpiClkInterruptSource()                 (UART_GPS_INTR_SPI_EC_REG)
    #define UART_GPS_GetExtSpiClkInterruptMode()                   (UART_GPS_INTR_SPI_EC_MASK_REG)
    #define UART_GPS_GetExtSpiClkInterruptSourceMasked()           (UART_GPS_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_GPS_CY_SCBIP_V1) */

#if(UART_GPS_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_GPS_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_GPS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_GPS_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_GPS_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_GPS_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_GPS_CUSTOM_INTR_HANDLER) */
#endif /* (UART_GPS_SCB_IRQ_INTERNAL) */

extern UART_GPS_BACKUP_STRUCT UART_GPS_backup;

#if(UART_GPS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_GPS_scbMode;
    extern uint8 UART_GPS_scbEnableWake;
    extern uint8 UART_GPS_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_GPS_mode;
    extern uint8 UART_GPS_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_GPS_rxBuffer;
    extern uint8   UART_GPS_rxDataBits;
    extern uint32  UART_GPS_rxBufferSize;

    extern volatile uint8 * UART_GPS_txBuffer;
    extern uint8   UART_GPS_txDataBits;
    extern uint32  UART_GPS_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_GPS_numberOfAddr;
    extern uint8 UART_GPS_subAddrSize;
#endif /* (UART_GPS_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_GPS_SCB_MODE_I2C_CONST_CFG || \
        UART_GPS_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_GPS_IntrTxMask;
#endif /* (! (UART_GPS_SCB_MODE_I2C_CONST_CFG || \
              UART_GPS_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_GPS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_GPS_SCB_MODE_I2C_RUNTM_CFG     (UART_GPS_SCB_MODE_I2C      == UART_GPS_scbMode)
    #define UART_GPS_SCB_MODE_SPI_RUNTM_CFG     (UART_GPS_SCB_MODE_SPI      == UART_GPS_scbMode)
    #define UART_GPS_SCB_MODE_UART_RUNTM_CFG    (UART_GPS_SCB_MODE_UART     == UART_GPS_scbMode)
    #define UART_GPS_SCB_MODE_EZI2C_RUNTM_CFG   (UART_GPS_SCB_MODE_EZI2C    == UART_GPS_scbMode)
    #define UART_GPS_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_GPS_SCB_MODE_UNCONFIG == UART_GPS_scbMode)

    /* Defines wakeup enable */
    #define UART_GPS_SCB_WAKE_ENABLE_CHECK       (0u != UART_GPS_scbEnableWake)
#endif /* (UART_GPS_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_GPS_CY_SCBIP_V1)
    #define UART_GPS_SCB_PINS_NUMBER    (7u)
#else
    #define UART_GPS_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_GPS_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_GPS_H) */


/* [] END OF FILE */
