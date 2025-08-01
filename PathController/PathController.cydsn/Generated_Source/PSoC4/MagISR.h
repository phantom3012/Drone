/*******************************************************************************
* File Name: MagISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_MagISR_H)
#define CY_ISR_MagISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void MagISR_Start(void);
void MagISR_StartEx(cyisraddress address);
void MagISR_Stop(void);

CY_ISR_PROTO(MagISR_Interrupt);

void MagISR_SetVector(cyisraddress address);
cyisraddress MagISR_GetVector(void);

void MagISR_SetPriority(uint8 priority);
uint8 MagISR_GetPriority(void);

void MagISR_Enable(void);
uint8 MagISR_GetState(void);
void MagISR_Disable(void);

void MagISR_SetPending(void);
void MagISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the MagISR ISR. */
#define MagISR_INTC_VECTOR            ((reg32 *) MagISR__INTC_VECT)

/* Address of the MagISR ISR priority. */
#define MagISR_INTC_PRIOR             ((reg32 *) MagISR__INTC_PRIOR_REG)

/* Priority of the MagISR interrupt. */
#define MagISR_INTC_PRIOR_NUMBER      MagISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable MagISR interrupt. */
#define MagISR_INTC_SET_EN            ((reg32 *) MagISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the MagISR interrupt. */
#define MagISR_INTC_CLR_EN            ((reg32 *) MagISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the MagISR interrupt state to pending. */
#define MagISR_INTC_SET_PD            ((reg32 *) MagISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the MagISR interrupt. */
#define MagISR_INTC_CLR_PD            ((reg32 *) MagISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_MagISR_H */


/* [] END OF FILE */
