/*******************************************************************************
* File Name: GyroSS_n.h  
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

#if !defined(CY_PINS_GyroSS_n_ALIASES_H) /* Pins GyroSS_n_ALIASES_H */
#define CY_PINS_GyroSS_n_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GyroSS_n_0			(GyroSS_n__0__PC)
#define GyroSS_n_0_PS		(GyroSS_n__0__PS)
#define GyroSS_n_0_PC		(GyroSS_n__0__PC)
#define GyroSS_n_0_DR		(GyroSS_n__0__DR)
#define GyroSS_n_0_SHIFT	(GyroSS_n__0__SHIFT)
#define GyroSS_n_0_INTR	((uint16)((uint16)0x0003u << (GyroSS_n__0__SHIFT*2u)))

#define GyroSS_n_INTR_ALL	 ((uint16)(GyroSS_n_0_INTR))


#endif /* End Pins GyroSS_n_ALIASES_H */


/* [] END OF FILE */
