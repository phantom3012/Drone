/***************************************************************************//**
* \file UART_CAM_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
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

#include "UART_CAM_PVT.h"
#include "UART_CAM_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (UART_CAM_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: UART_CAM_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(UART_CAM_SPI_UART_ISR)
{
#if (UART_CAM_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (UART_CAM_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART_CAM_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (UART_CAM_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef UART_CAM_SPI_UART_ISR_ENTRY_CALLBACK
    UART_CAM_SPI_UART_ISR_EntryCallback();
#endif /* UART_CAM_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != UART_CAM_customIntrHandler)
    {
        UART_CAM_customIntrHandler();
    }

    #if(UART_CAM_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        UART_CAM_ClearSpiExtClkInterruptSource(UART_CAM_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (UART_CAM_CHECK_RX_SW_BUFFER)
    {
        if (UART_CAM_CHECK_INTR_RX_MASKED(UART_CAM_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (UART_CAM_rxBufferHead + 1u);

                /* Adjust local head index */
                if (UART_CAM_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == UART_CAM_rxBufferTail)
                {
                    #if (UART_CAM_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        UART_CAM_INTR_RX_MASK_REG &= ~UART_CAM_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) UART_CAM_RX_FIFO_RD_REG;
                        UART_CAM_rxBufferOverflow = (uint8) UART_CAM_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    UART_CAM_PutWordInRxBuffer(locHead, UART_CAM_RX_FIFO_RD_REG);

                    /* Move head index */
                    UART_CAM_rxBufferHead = locHead;
                }
            }
            while(0u != UART_CAM_GET_RX_FIFO_ENTRIES);

            UART_CAM_ClearRxInterruptSource(UART_CAM_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (UART_CAM_CHECK_TX_SW_BUFFER)
    {
        if (UART_CAM_CHECK_INTR_TX_MASKED(UART_CAM_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (UART_CAM_txBufferHead != UART_CAM_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (UART_CAM_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (UART_CAM_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    UART_CAM_TX_FIFO_WR_REG = UART_CAM_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    UART_CAM_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    UART_CAM_DISABLE_INTR_TX(UART_CAM_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (UART_CAM_SPI_UART_FIFO_SIZE != UART_CAM_GET_TX_FIFO_ENTRIES);

            UART_CAM_ClearTxInterruptSource(UART_CAM_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef UART_CAM_SPI_UART_ISR_EXIT_CALLBACK
    UART_CAM_SPI_UART_ISR_ExitCallback();
#endif /* UART_CAM_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (UART_CAM_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
