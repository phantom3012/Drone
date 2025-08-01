/*******************************************************************************
* File Name: BckLftESC.h  
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

#if !defined(CY_PINS_BckLftESC_ALIASES_H) /* Pins BckLftESC_ALIASES_H */
#define CY_PINS_BckLftESC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BckLftESC_0			(BckLftESC__0__PC)
#define BckLftESC_0_PS		(BckLftESC__0__PS)
#define BckLftESC_0_PC		(BckLftESC__0__PC)
#define BckLftESC_0_DR		(BckLftESC__0__DR)
#define BckLftESC_0_SHIFT	(BckLftESC__0__SHIFT)
#define BckLftESC_0_INTR	((uint16)((uint16)0x0003u << (BckLftESC__0__SHIFT*2u)))

#define BckLftESC_INTR_ALL	 ((uint16)(BckLftESC_0_INTR))


#endif /* End Pins BckLftESC_ALIASES_H */


/* [] END OF FILE */
