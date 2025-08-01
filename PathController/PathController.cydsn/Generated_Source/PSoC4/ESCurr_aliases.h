/*******************************************************************************
* File Name: ESCurr.h  
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

#if !defined(CY_PINS_ESCurr_ALIASES_H) /* Pins ESCurr_ALIASES_H */
#define CY_PINS_ESCurr_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ESCurr_0			(ESCurr__0__PC)
#define ESCurr_0_PS		(ESCurr__0__PS)
#define ESCurr_0_PC		(ESCurr__0__PC)
#define ESCurr_0_DR		(ESCurr__0__DR)
#define ESCurr_0_SHIFT	(ESCurr__0__SHIFT)
#define ESCurr_0_INTR	((uint16)((uint16)0x0003u << (ESCurr__0__SHIFT*2u)))

#define ESCurr_INTR_ALL	 ((uint16)(ESCurr_0_INTR))


#endif /* End Pins ESCurr_ALIASES_H */


/* [] END OF FILE */
