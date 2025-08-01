/*******************************************************************************
* File Name: TMR_ISR.h
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
#if !defined(CY_ISR_TMR_ISR_H)
#define CY_ISR_TMR_ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TMR_ISR_Start(void);
void TMR_ISR_StartEx(cyisraddress address);
void TMR_ISR_Stop(void);

CY_ISR_PROTO(TMR_ISR_Interrupt);

void TMR_ISR_SetVector(cyisraddress address);
cyisraddress TMR_ISR_GetVector(void);

void TMR_ISR_SetPriority(uint8 priority);
uint8 TMR_ISR_GetPriority(void);

void TMR_ISR_Enable(void);
uint8 TMR_ISR_GetState(void);
void TMR_ISR_Disable(void);

void TMR_ISR_SetPending(void);
void TMR_ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TMR_ISR ISR. */
#define TMR_ISR_INTC_VECTOR            ((reg32 *) TMR_ISR__INTC_VECT)

/* Address of the TMR_ISR ISR priority. */
#define TMR_ISR_INTC_PRIOR             ((reg32 *) TMR_ISR__INTC_PRIOR_REG)

/* Priority of the TMR_ISR interrupt. */
#define TMR_ISR_INTC_PRIOR_NUMBER      TMR_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TMR_ISR interrupt. */
#define TMR_ISR_INTC_SET_EN            ((reg32 *) TMR_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TMR_ISR interrupt. */
#define TMR_ISR_INTC_CLR_EN            ((reg32 *) TMR_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TMR_ISR interrupt state to pending. */
#define TMR_ISR_INTC_SET_PD            ((reg32 *) TMR_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TMR_ISR interrupt. */
#define TMR_ISR_INTC_CLR_PD            ((reg32 *) TMR_ISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_TMR_ISR_H */


/* [] END OF FILE */
