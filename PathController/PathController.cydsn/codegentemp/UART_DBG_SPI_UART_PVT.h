/***************************************************************************//**
* \file UART_DBG_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_UART_DBG_H)
#define CY_SCB_SPI_UART_PVT_UART_DBG_H

#include "UART_DBG_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART_DBG_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_DBG_rxBufferHead;
    extern volatile uint32  UART_DBG_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   UART_DBG_rxBufferOverflow;
    /** @} globals */
#endif /* (UART_DBG_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_DBG_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_DBG_txBufferHead;
    extern volatile uint32  UART_DBG_txBufferTail;
#endif /* (UART_DBG_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART_DBG_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_DBG_rxBufferInternal[UART_DBG_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART_DBG_INTERNAL_RX_SW_BUFFER) */

#if (UART_DBG_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_DBG_txBufferInternal[UART_DBG_TX_BUFFER_SIZE];
#endif /* (UART_DBG_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART_DBG_SpiPostEnable(void);
void UART_DBG_SpiStop(void);

#if (UART_DBG_SCB_MODE_SPI_CONST_CFG)
    void UART_DBG_SpiInit(void);
#endif /* (UART_DBG_SCB_MODE_SPI_CONST_CFG) */

#if (UART_DBG_SPI_WAKE_ENABLE_CONST)
    void UART_DBG_SpiSaveConfig(void);
    void UART_DBG_SpiRestoreConfig(void);
#endif /* (UART_DBG_SPI_WAKE_ENABLE_CONST) */

void UART_DBG_UartPostEnable(void);
void UART_DBG_UartStop(void);

#if (UART_DBG_SCB_MODE_UART_CONST_CFG)
    void UART_DBG_UartInit(void);
#endif /* (UART_DBG_SCB_MODE_UART_CONST_CFG) */

#if (UART_DBG_UART_WAKE_ENABLE_CONST)
    void UART_DBG_UartSaveConfig(void);
    void UART_DBG_UartRestoreConfig(void);
#endif /* (UART_DBG_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_DBG_SetPins() */
#define UART_DBG_UART_RX_PIN_ENABLE    (UART_DBG_UART_RX)
#define UART_DBG_UART_TX_PIN_ENABLE    (UART_DBG_UART_TX)

/* UART RTS and CTS position to be used in  UART_DBG_SetPins() */
#define UART_DBG_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_DBG_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART_DBG_SpiUartEnableIntRx(intSourceMask)  UART_DBG_SetRxInterruptMode(intSourceMask)
#define UART_DBG_SpiUartEnableIntTx(intSourceMask)  UART_DBG_SetTxInterruptMode(intSourceMask)
uint32  UART_DBG_SpiUartDisableIntRx(void);
uint32  UART_DBG_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART_DBG_H) */


/* [] END OF FILE */
