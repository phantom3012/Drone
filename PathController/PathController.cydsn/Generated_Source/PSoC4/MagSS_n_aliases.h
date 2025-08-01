/*******************************************************************************
* File Name: MagSS_n.h  
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

#if !defined(CY_PINS_MagSS_n_ALIASES_H) /* Pins MagSS_n_ALIASES_H */
#define CY_PINS_MagSS_n_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MagSS_n_0			(MagSS_n__0__PC)
#define MagSS_n_0_PS		(MagSS_n__0__PS)
#define MagSS_n_0_PC		(MagSS_n__0__PC)
#define MagSS_n_0_DR		(MagSS_n__0__DR)
#define MagSS_n_0_SHIFT	(MagSS_n__0__SHIFT)
#define MagSS_n_0_INTR	((uint16)((uint16)0x0003u << (MagSS_n__0__SHIFT*2u)))

#define MagSS_n_INTR_ALL	 ((uint16)(MagSS_n_0_INTR))


#endif /* End Pins MagSS_n_ALIASES_H */


/* [] END OF FILE */
