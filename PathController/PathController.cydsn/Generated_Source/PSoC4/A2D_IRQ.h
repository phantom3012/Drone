/*******************************************************************************
* File Name: A2D_IRQ.h
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
#if !defined(CY_ISR_A2D_IRQ_H)
#define CY_ISR_A2D_IRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void A2D_IRQ_Start(void);
void A2D_IRQ_StartEx(cyisraddress address);
void A2D_IRQ_Stop(void);

CY_ISR_PROTO(A2D_IRQ_Interrupt);

void A2D_IRQ_SetVector(cyisraddress address);
cyisraddress A2D_IRQ_GetVector(void);

void A2D_IRQ_SetPriority(uint8 priority);
uint8 A2D_IRQ_GetPriority(void);

void A2D_IRQ_Enable(void);
uint8 A2D_IRQ_GetState(void);
void A2D_IRQ_Disable(void);

void A2D_IRQ_SetPending(void);
void A2D_IRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the A2D_IRQ ISR. */
#define A2D_IRQ_INTC_VECTOR            ((reg32 *) A2D_IRQ__INTC_VECT)

/* Address of the A2D_IRQ ISR priority. */
#define A2D_IRQ_INTC_PRIOR             ((reg32 *) A2D_IRQ__INTC_PRIOR_REG)

/* Priority of the A2D_IRQ interrupt. */
#define A2D_IRQ_INTC_PRIOR_NUMBER      A2D_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable A2D_IRQ interrupt. */
#define A2D_IRQ_INTC_SET_EN            ((reg32 *) A2D_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the A2D_IRQ interrupt. */
#define A2D_IRQ_INTC_CLR_EN            ((reg32 *) A2D_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the A2D_IRQ interrupt state to pending. */
#define A2D_IRQ_INTC_SET_PD            ((reg32 *) A2D_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the A2D_IRQ interrupt. */
#define A2D_IRQ_INTC_CLR_PD            ((reg32 *) A2D_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_A2D_IRQ_H */


/* [] END OF FILE */
