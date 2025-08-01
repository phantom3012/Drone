/*******************************************************************************
* File Name: GyroISR.h
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
#if !defined(CY_ISR_GyroISR_H)
#define CY_ISR_GyroISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void GyroISR_Start(void);
void GyroISR_StartEx(cyisraddress address);
void GyroISR_Stop(void);

CY_ISR_PROTO(GyroISR_Interrupt);

void GyroISR_SetVector(cyisraddress address);
cyisraddress GyroISR_GetVector(void);

void GyroISR_SetPriority(uint8 priority);
uint8 GyroISR_GetPriority(void);

void GyroISR_Enable(void);
uint8 GyroISR_GetState(void);
void GyroISR_Disable(void);

void GyroISR_SetPending(void);
void GyroISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the GyroISR ISR. */
#define GyroISR_INTC_VECTOR            ((reg32 *) GyroISR__INTC_VECT)

/* Address of the GyroISR ISR priority. */
#define GyroISR_INTC_PRIOR             ((reg32 *) GyroISR__INTC_PRIOR_REG)

/* Priority of the GyroISR interrupt. */
#define GyroISR_INTC_PRIOR_NUMBER      GyroISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable GyroISR interrupt. */
#define GyroISR_INTC_SET_EN            ((reg32 *) GyroISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the GyroISR interrupt. */
#define GyroISR_INTC_CLR_EN            ((reg32 *) GyroISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the GyroISR interrupt state to pending. */
#define GyroISR_INTC_SET_PD            ((reg32 *) GyroISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the GyroISR interrupt. */
#define GyroISR_INTC_CLR_PD            ((reg32 *) GyroISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_GyroISR_H */


/* [] END OF FILE */
