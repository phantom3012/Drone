/*******************************************************************************
* File Name: UART_CAM_rx.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_UART_CAM_rx_ALIASES_H) /* Pins UART_CAM_rx_ALIASES_H */
#define CY_PINS_UART_CAM_rx_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define UART_CAM_rx_0			(UART_CAM_rx__0__PC)
#define UART_CAM_rx_0_PS		(UART_CAM_rx__0__PS)
#define UART_CAM_rx_0_PC		(UART_CAM_rx__0__PC)
#define UART_CAM_rx_0_DR		(UART_CAM_rx__0__DR)
#define UART_CAM_rx_0_SHIFT	(UART_CAM_rx__0__SHIFT)
#define UART_CAM_rx_0_INTR	((uint16)((uint16)0x0003u << (UART_CAM_rx__0__SHIFT*2u)))

#define UART_CAM_rx_INTR_ALL	 ((uint16)(UART_CAM_rx_0_INTR))


#endif /* End Pins UART_CAM_rx_ALIASES_H */


/* [] END OF FILE */
