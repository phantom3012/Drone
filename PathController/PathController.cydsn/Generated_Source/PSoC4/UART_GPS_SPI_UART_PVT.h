/***************************************************************************//**
* \file UART_GPS_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_UART_GPS_H)
#define CY_SCB_SPI_UART_PVT_UART_GPS_H

#include "UART_GPS_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART_GPS_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_GPS_rxBufferHead;
    extern volatile uint32  UART_GPS_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   UART_GPS_rxBufferOverflow;
    /** @} globals */
#endif /* (UART_GPS_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_GPS_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_GPS_txBufferHead;
    extern volatile uint32  UART_GPS_txBufferTail;
#endif /* (UART_GPS_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART_GPS_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_GPS_rxBufferInternal[UART_GPS_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART_GPS_INTERNAL_RX_SW_BUFFER) */

#if (UART_GPS_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_GPS_txBufferInternal[UART_GPS_TX_BUFFER_SIZE];
#endif /* (UART_GPS_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART_GPS_SpiPostEnable(void);
void UART_GPS_SpiStop(void);

#if (UART_GPS_SCB_MODE_SPI_CONST_CFG)
    void UART_GPS_SpiInit(void);
#endif /* (UART_GPS_SCB_MODE_SPI_CONST_CFG) */

#if (UART_GPS_SPI_WAKE_ENABLE_CONST)
    void UART_GPS_SpiSaveConfig(void);
    void UART_GPS_SpiRestoreConfig(void);
#endif /* (UART_GPS_SPI_WAKE_ENABLE_CONST) */

void UART_GPS_UartPostEnable(void);
void UART_GPS_UartStop(void);

#if (UART_GPS_SCB_MODE_UART_CONST_CFG)
    void UART_GPS_UartInit(void);
#endif /* (UART_GPS_SCB_MODE_UART_CONST_CFG) */

#if (UART_GPS_UART_WAKE_ENABLE_CONST)
    void UART_GPS_UartSaveConfig(void);
    void UART_GPS_UartRestoreConfig(void);
#endif /* (UART_GPS_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_GPS_SetPins() */
#define UART_GPS_UART_RX_PIN_ENABLE    (UART_GPS_UART_RX)
#define UART_GPS_UART_TX_PIN_ENABLE    (UART_GPS_UART_TX)

/* UART RTS and CTS position to be used in  UART_GPS_SetPins() */
#define UART_GPS_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_GPS_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART_GPS_SpiUartEnableIntRx(intSourceMask)  UART_GPS_SetRxInterruptMode(intSourceMask)
#define UART_GPS_SpiUartEnableIntTx(intSourceMask)  UART_GPS_SetTxInterruptMode(intSourceMask)
uint32  UART_GPS_SpiUartDisableIntRx(void);
uint32  UART_GPS_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART_GPS_H) */


/* [] END OF FILE */
