/*******************************************************************************
* File Name: FrntRghtESC.h  
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

#if !defined(CY_PINS_FrntRghtESC_ALIASES_H) /* Pins FrntRghtESC_ALIASES_H */
#define CY_PINS_FrntRghtESC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define FrntRghtESC_0			(FrntRghtESC__0__PC)
#define FrntRghtESC_0_PS		(FrntRghtESC__0__PS)
#define FrntRghtESC_0_PC		(FrntRghtESC__0__PC)
#define FrntRghtESC_0_DR		(FrntRghtESC__0__DR)
#define FrntRghtESC_0_SHIFT	(FrntRghtESC__0__SHIFT)
#define FrntRghtESC_0_INTR	((uint16)((uint16)0x0003u << (FrntRghtESC__0__SHIFT*2u)))

#define FrntRghtESC_INTR_ALL	 ((uint16)(FrntRghtESC_0_INTR))


#endif /* End Pins FrntRghtESC_ALIASES_H */


/* [] END OF FILE */
