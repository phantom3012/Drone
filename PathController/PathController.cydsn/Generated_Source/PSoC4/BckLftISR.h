/*******************************************************************************
* File Name: BckLftISR.h
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
#if !defined(CY_ISR_BckLftISR_H)
#define CY_ISR_BckLftISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void BckLftISR_Start(void);
void BckLftISR_StartEx(cyisraddress address);
void BckLftISR_Stop(void);

CY_ISR_PROTO(BckLftISR_Interrupt);

void BckLftISR_SetVector(cyisraddress address);
cyisraddress BckLftISR_GetVector(void);

void BckLftISR_SetPriority(uint8 priority);
uint8 BckLftISR_GetPriority(void);

void BckLftISR_Enable(void);
uint8 BckLftISR_GetState(void);
void BckLftISR_Disable(void);

void BckLftISR_SetPending(void);
void BckLftISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the BckLftISR ISR. */
#define BckLftISR_INTC_VECTOR            ((reg32 *) BckLftISR__INTC_VECT)

/* Address of the BckLftISR ISR priority. */
#define BckLftISR_INTC_PRIOR             ((reg32 *) BckLftISR__INTC_PRIOR_REG)

/* Priority of the BckLftISR interrupt. */
#define BckLftISR_INTC_PRIOR_NUMBER      BckLftISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable BckLftISR interrupt. */
#define BckLftISR_INTC_SET_EN            ((reg32 *) BckLftISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the BckLftISR interrupt. */
#define BckLftISR_INTC_CLR_EN            ((reg32 *) BckLftISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the BckLftISR interrupt state to pending. */
#define BckLftISR_INTC_SET_PD            ((reg32 *) BckLftISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the BckLftISR interrupt. */
#define BckLftISR_INTC_CLR_PD            ((reg32 *) BckLftISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_BckLftISR_H */


/* [] END OF FILE */
