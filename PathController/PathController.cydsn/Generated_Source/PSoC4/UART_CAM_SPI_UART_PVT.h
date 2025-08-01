/***************************************************************************//**
* \file UART_CAM_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_UART_CAM_H)
#define CY_SCB_SPI_UART_PVT_UART_CAM_H

#include "UART_CAM_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART_CAM_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART_CAM_rxBufferHead;
    extern volatile uint32  UART_CAM_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   UART_CAM_rxBufferOverflow;
    /** @} globals */
#endif /* (UART_CAM_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_CAM_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART_CAM_txBufferHead;
    extern volatile uint32  UART_CAM_txBufferTail;
#endif /* (UART_CAM_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART_CAM_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART_CAM_rxBufferInternal[UART_CAM_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART_CAM_INTERNAL_RX_SW_BUFFER) */

#if (UART_CAM_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART_CAM_txBufferInternal[UART_CAM_TX_BUFFER_SIZE];
#endif /* (UART_CAM_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART_CAM_SpiPostEnable(void);
void UART_CAM_SpiStop(void);

#if (UART_CAM_SCB_MODE_SPI_CONST_CFG)
    void UART_CAM_SpiInit(void);
#endif /* (UART_CAM_SCB_MODE_SPI_CONST_CFG) */

#if (UART_CAM_SPI_WAKE_ENABLE_CONST)
    void UART_CAM_SpiSaveConfig(void);
    void UART_CAM_SpiRestoreConfig(void);
#endif /* (UART_CAM_SPI_WAKE_ENABLE_CONST) */

void UART_CAM_UartPostEnable(void);
void UART_CAM_UartStop(void);

#if (UART_CAM_SCB_MODE_UART_CONST_CFG)
    void UART_CAM_UartInit(void);
#endif /* (UART_CAM_SCB_MODE_UART_CONST_CFG) */

#if (UART_CAM_UART_WAKE_ENABLE_CONST)
    void UART_CAM_UartSaveConfig(void);
    void UART_CAM_UartRestoreConfig(void);
#endif /* (UART_CAM_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART_CAM_SetPins() */
#define UART_CAM_UART_RX_PIN_ENABLE    (UART_CAM_UART_RX)
#define UART_CAM_UART_TX_PIN_ENABLE    (UART_CAM_UART_TX)

/* UART RTS and CTS position to be used in  UART_CAM_SetPins() */
#define UART_CAM_UART_RTS_PIN_ENABLE    (0x10u)
#define UART_CAM_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART_CAM_SpiUartEnableIntRx(intSourceMask)  UART_CAM_SetRxInterruptMode(intSourceMask)
#define UART_CAM_SpiUartEnableIntTx(intSourceMask)  UART_CAM_SetTxInterruptMode(intSourceMask)
uint32  UART_CAM_SpiUartDisableIntRx(void);
uint32  UART_CAM_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART_CAM_H) */


/* [] END OF FILE */
