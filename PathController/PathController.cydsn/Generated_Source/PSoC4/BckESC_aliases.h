/*******************************************************************************
* File Name: BckESC.h  
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

#if !defined(CY_PINS_BckESC_ALIASES_H) /* Pins BckESC_ALIASES_H */
#define CY_PINS_BckESC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BckESC_0			(BckESC__0__PC)
#define BckESC_0_PS		(BckESC__0__PS)
#define BckESC_0_PC		(BckESC__0__PC)
#define BckESC_0_DR		(BckESC__0__DR)
#define BckESC_0_SHIFT	(BckESC__0__SHIFT)
#define BckESC_0_INTR	((uint16)((uint16)0x0003u << (BckESC__0__SHIFT*2u)))

#define BckESC_INTR_ALL	 ((uint16)(BckESC_0_INTR))


#endif /* End Pins BckESC_ALIASES_H */


/* [] END OF FILE */
