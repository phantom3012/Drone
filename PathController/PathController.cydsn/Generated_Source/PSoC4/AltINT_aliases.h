/*******************************************************************************
* File Name: AltINT.h  
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

#if !defined(CY_PINS_AltINT_ALIASES_H) /* Pins AltINT_ALIASES_H */
#define CY_PINS_AltINT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AltINT_0			(AltINT__0__PC)
#define AltINT_0_PS		(AltINT__0__PS)
#define AltINT_0_PC		(AltINT__0__PC)
#define AltINT_0_DR		(AltINT__0__DR)
#define AltINT_0_SHIFT	(AltINT__0__SHIFT)
#define AltINT_0_INTR	((uint16)((uint16)0x0003u << (AltINT__0__SHIFT*2u)))

#define AltINT_INTR_ALL	 ((uint16)(AltINT_0_INTR))


#endif /* End Pins AltINT_ALIASES_H */


/* [] END OF FILE */
