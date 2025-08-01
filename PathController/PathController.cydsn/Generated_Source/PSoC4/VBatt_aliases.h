/*******************************************************************************
* File Name: VBatt.h  
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

#if !defined(CY_PINS_VBatt_ALIASES_H) /* Pins VBatt_ALIASES_H */
#define CY_PINS_VBatt_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define VBatt_0			(VBatt__0__PC)
#define VBatt_0_PS		(VBatt__0__PS)
#define VBatt_0_PC		(VBatt__0__PC)
#define VBatt_0_DR		(VBatt__0__DR)
#define VBatt_0_SHIFT	(VBatt__0__SHIFT)
#define VBatt_0_INTR	((uint16)((uint16)0x0003u << (VBatt__0__SHIFT*2u)))

#define VBatt_INTR_ALL	 ((uint16)(VBatt_0_INTR))


#endif /* End Pins VBatt_ALIASES_H */


/* [] END OF FILE */
