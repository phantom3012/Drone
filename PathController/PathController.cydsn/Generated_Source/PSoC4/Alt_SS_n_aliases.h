/*******************************************************************************
* File Name: Alt_SS_n.h  
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

#if !defined(CY_PINS_Alt_SS_n_ALIASES_H) /* Pins Alt_SS_n_ALIASES_H */
#define CY_PINS_Alt_SS_n_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Alt_SS_n_0			(Alt_SS_n__0__PC)
#define Alt_SS_n_0_PS		(Alt_SS_n__0__PS)
#define Alt_SS_n_0_PC		(Alt_SS_n__0__PC)
#define Alt_SS_n_0_DR		(Alt_SS_n__0__DR)
#define Alt_SS_n_0_SHIFT	(Alt_SS_n__0__SHIFT)
#define Alt_SS_n_0_INTR	((uint16)((uint16)0x0003u << (Alt_SS_n__0__SHIFT*2u)))

#define Alt_SS_n_INTR_ALL	 ((uint16)(Alt_SS_n_0_INTR))


#endif /* End Pins Alt_SS_n_ALIASES_H */


/* [] END OF FILE */
