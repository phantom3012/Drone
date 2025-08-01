/*******************************************************************************
* File Name: RghtESC.h  
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

#if !defined(CY_PINS_RghtESC_ALIASES_H) /* Pins RghtESC_ALIASES_H */
#define CY_PINS_RghtESC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define RghtESC_0			(RghtESC__0__PC)
#define RghtESC_0_PS		(RghtESC__0__PS)
#define RghtESC_0_PC		(RghtESC__0__PC)
#define RghtESC_0_DR		(RghtESC__0__DR)
#define RghtESC_0_SHIFT	(RghtESC__0__SHIFT)
#define RghtESC_0_INTR	((uint16)((uint16)0x0003u << (RghtESC__0__SHIFT*2u)))

#define RghtESC_INTR_ALL	 ((uint16)(RghtESC_0_INTR))


#endif /* End Pins RghtESC_ALIASES_H */


/* [] END OF FILE */
