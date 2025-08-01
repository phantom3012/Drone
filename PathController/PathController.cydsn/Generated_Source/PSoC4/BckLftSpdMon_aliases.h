/*******************************************************************************
* File Name: BckLftSpdMon.h  
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

#if !defined(CY_PINS_BckLftSpdMon_ALIASES_H) /* Pins BckLftSpdMon_ALIASES_H */
#define CY_PINS_BckLftSpdMon_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BckLftSpdMon_0			(BckLftSpdMon__0__PC)
#define BckLftSpdMon_0_PS		(BckLftSpdMon__0__PS)
#define BckLftSpdMon_0_PC		(BckLftSpdMon__0__PC)
#define BckLftSpdMon_0_DR		(BckLftSpdMon__0__DR)
#define BckLftSpdMon_0_SHIFT	(BckLftSpdMon__0__SHIFT)
#define BckLftSpdMon_0_INTR	((uint16)((uint16)0x0003u << (BckLftSpdMon__0__SHIFT*2u)))

#define BckLftSpdMon_INTR_ALL	 ((uint16)(BckLftSpdMon_0_INTR))


#endif /* End Pins BckLftSpdMon_ALIASES_H */


/* [] END OF FILE */
