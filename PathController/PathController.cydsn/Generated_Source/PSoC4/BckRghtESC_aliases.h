/*******************************************************************************
* File Name: BckRghtESC.h  
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

#if !defined(CY_PINS_BckRghtESC_ALIASES_H) /* Pins BckRghtESC_ALIASES_H */
#define CY_PINS_BckRghtESC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BckRghtESC_0			(BckRghtESC__0__PC)
#define BckRghtESC_0_PS		(BckRghtESC__0__PS)
#define BckRghtESC_0_PC		(BckRghtESC__0__PC)
#define BckRghtESC_0_DR		(BckRghtESC__0__DR)
#define BckRghtESC_0_SHIFT	(BckRghtESC__0__SHIFT)
#define BckRghtESC_0_INTR	((uint16)((uint16)0x0003u << (BckRghtESC__0__SHIFT*2u)))

#define BckRghtESC_INTR_ALL	 ((uint16)(BckRghtESC_0_INTR))


#endif /* End Pins BckRghtESC_ALIASES_H */


/* [] END OF FILE */
