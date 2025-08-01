/*******************************************************************************
* File Name: MaxLidar.h  
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

#if !defined(CY_PINS_MaxLidar_ALIASES_H) /* Pins MaxLidar_ALIASES_H */
#define CY_PINS_MaxLidar_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MaxLidar_0			(MaxLidar__0__PC)
#define MaxLidar_0_PS		(MaxLidar__0__PS)
#define MaxLidar_0_PC		(MaxLidar__0__PC)
#define MaxLidar_0_DR		(MaxLidar__0__DR)
#define MaxLidar_0_SHIFT	(MaxLidar__0__SHIFT)
#define MaxLidar_0_INTR	((uint16)((uint16)0x0003u << (MaxLidar__0__SHIFT*2u)))

#define MaxLidar_INTR_ALL	 ((uint16)(MaxLidar_0_INTR))


#endif /* End Pins MaxLidar_ALIASES_H */


/* [] END OF FILE */
