/*******************************************************************************
* File Name: magINT.h  
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

#if !defined(CY_PINS_magINT_ALIASES_H) /* Pins magINT_ALIASES_H */
#define CY_PINS_magINT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define magINT_0			(magINT__0__PC)
#define magINT_0_PS		(magINT__0__PS)
#define magINT_0_PC		(magINT__0__PC)
#define magINT_0_DR		(magINT__0__DR)
#define magINT_0_SHIFT	(magINT__0__SHIFT)
#define magINT_0_INTR	((uint16)((uint16)0x0003u << (magINT__0__SHIFT*2u)))

#define magINT_INTR_ALL	 ((uint16)(magINT_0_INTR))


#endif /* End Pins magINT_ALIASES_H */


/* [] END OF FILE */
