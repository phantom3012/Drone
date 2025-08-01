/*******************************************************************************
* File Name: LftESC.h  
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

#if !defined(CY_PINS_LftESC_ALIASES_H) /* Pins LftESC_ALIASES_H */
#define CY_PINS_LftESC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LftESC_0			(LftESC__0__PC)
#define LftESC_0_PS		(LftESC__0__PS)
#define LftESC_0_PC		(LftESC__0__PC)
#define LftESC_0_DR		(LftESC__0__DR)
#define LftESC_0_SHIFT	(LftESC__0__SHIFT)
#define LftESC_0_INTR	((uint16)((uint16)0x0003u << (LftESC__0__SHIFT*2u)))

#define LftESC_INTR_ALL	 ((uint16)(LftESC_0_INTR))


#endif /* End Pins LftESC_ALIASES_H */


/* [] END OF FILE */
