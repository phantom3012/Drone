/*******************************************************************************
* File Name: FrntLftESC.h  
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

#if !defined(CY_PINS_FrntLftESC_ALIASES_H) /* Pins FrntLftESC_ALIASES_H */
#define CY_PINS_FrntLftESC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define FrntLftESC_0			(FrntLftESC__0__PC)
#define FrntLftESC_0_PS		(FrntLftESC__0__PS)
#define FrntLftESC_0_PC		(FrntLftESC__0__PC)
#define FrntLftESC_0_DR		(FrntLftESC__0__DR)
#define FrntLftESC_0_SHIFT	(FrntLftESC__0__SHIFT)
#define FrntLftESC_0_INTR	((uint16)((uint16)0x0003u << (FrntLftESC__0__SHIFT*2u)))

#define FrntLftESC_INTR_ALL	 ((uint16)(FrntLftESC_0_INTR))


#endif /* End Pins FrntLftESC_ALIASES_H */


/* [] END OF FILE */
