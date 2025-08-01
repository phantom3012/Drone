/*******************************************************************************
* File Name: Ana.h  
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

#if !defined(CY_PINS_Ana_ALIASES_H) /* Pins Ana_ALIASES_H */
#define CY_PINS_Ana_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Ana_0			(Ana__0__PC)
#define Ana_0_PS		(Ana__0__PS)
#define Ana_0_PC		(Ana__0__PC)
#define Ana_0_DR		(Ana__0__DR)
#define Ana_0_SHIFT	(Ana__0__SHIFT)
#define Ana_0_INTR	((uint16)((uint16)0x0003u << (Ana__0__SHIFT*2u)))

#define Ana_INTR_ALL	 ((uint16)(Ana_0_INTR))


#endif /* End Pins Ana_ALIASES_H */


/* [] END OF FILE */
