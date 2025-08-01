/*******************************************************************************
* File Name: InertINT.h  
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

#if !defined(CY_PINS_InertINT_ALIASES_H) /* Pins InertINT_ALIASES_H */
#define CY_PINS_InertINT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define InertINT_0			(InertINT__0__PC)
#define InertINT_0_PS		(InertINT__0__PS)
#define InertINT_0_PC		(InertINT__0__PC)
#define InertINT_0_DR		(InertINT__0__DR)
#define InertINT_0_SHIFT	(InertINT__0__SHIFT)
#define InertINT_0_INTR	((uint16)((uint16)0x0003u << (InertINT__0__SHIFT*2u)))

#define InertINT_INTR_ALL	 ((uint16)(InertINT_0_INTR))


#endif /* End Pins InertINT_ALIASES_H */


/* [] END OF FILE */
