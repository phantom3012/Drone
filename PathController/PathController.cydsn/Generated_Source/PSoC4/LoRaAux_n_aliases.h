/*******************************************************************************
* File Name: LoRaAux_n.h  
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

#if !defined(CY_PINS_LoRaAux_n_ALIASES_H) /* Pins LoRaAux_n_ALIASES_H */
#define CY_PINS_LoRaAux_n_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LoRaAux_n_0			(LoRaAux_n__0__PC)
#define LoRaAux_n_0_PS		(LoRaAux_n__0__PS)
#define LoRaAux_n_0_PC		(LoRaAux_n__0__PC)
#define LoRaAux_n_0_DR		(LoRaAux_n__0__DR)
#define LoRaAux_n_0_SHIFT	(LoRaAux_n__0__SHIFT)
#define LoRaAux_n_0_INTR	((uint16)((uint16)0x0003u << (LoRaAux_n__0__SHIFT*2u)))

#define LoRaAux_n_INTR_ALL	 ((uint16)(LoRaAux_n_0_INTR))


#endif /* End Pins LoRaAux_n_ALIASES_H */


/* [] END OF FILE */
