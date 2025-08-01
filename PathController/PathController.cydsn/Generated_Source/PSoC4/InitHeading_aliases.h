/*******************************************************************************
* File Name: InitHeading.h  
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

#if !defined(CY_PINS_InitHeading_ALIASES_H) /* Pins InitHeading_ALIASES_H */
#define CY_PINS_InitHeading_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define InitHeading_0			(InitHeading__0__PC)
#define InitHeading_0_PS		(InitHeading__0__PS)
#define InitHeading_0_PC		(InitHeading__0__PC)
#define InitHeading_0_DR		(InitHeading__0__DR)
#define InitHeading_0_SHIFT	(InitHeading__0__SHIFT)
#define InitHeading_0_INTR	((uint16)((uint16)0x0003u << (InitHeading__0__SHIFT*2u)))

#define InitHeading_INTR_ALL	 ((uint16)(InitHeading_0_INTR))


#endif /* End Pins InitHeading_ALIASES_H */


/* [] END OF FILE */
