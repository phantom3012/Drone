/*******************************************************************************
* File Name: A2D_intClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_A2D_intClock_H)
#define CY_CLOCK_A2D_intClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void A2D_intClock_StartEx(uint32 alignClkDiv);
#define A2D_intClock_Start() \
    A2D_intClock_StartEx(A2D_intClock__PA_DIV_ID)

#else

void A2D_intClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void A2D_intClock_Stop(void);

void A2D_intClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 A2D_intClock_GetDividerRegister(void);
uint8  A2D_intClock_GetFractionalDividerRegister(void);

#define A2D_intClock_Enable()                         A2D_intClock_Start()
#define A2D_intClock_Disable()                        A2D_intClock_Stop()
#define A2D_intClock_SetDividerRegister(clkDivider, reset)  \
    A2D_intClock_SetFractionalDividerRegister((clkDivider), 0u)
#define A2D_intClock_SetDivider(clkDivider)           A2D_intClock_SetDividerRegister((clkDivider), 1u)
#define A2D_intClock_SetDividerValue(clkDivider)      A2D_intClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define A2D_intClock_DIV_ID     A2D_intClock__DIV_ID

#define A2D_intClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define A2D_intClock_CTRL_REG   (*(reg32 *)A2D_intClock__CTRL_REGISTER)
#define A2D_intClock_DIV_REG    (*(reg32 *)A2D_intClock__DIV_REGISTER)

#define A2D_intClock_CMD_DIV_SHIFT          (0u)
#define A2D_intClock_CMD_PA_DIV_SHIFT       (8u)
#define A2D_intClock_CMD_DISABLE_SHIFT      (30u)
#define A2D_intClock_CMD_ENABLE_SHIFT       (31u)

#define A2D_intClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << A2D_intClock_CMD_DISABLE_SHIFT))
#define A2D_intClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << A2D_intClock_CMD_ENABLE_SHIFT))

#define A2D_intClock_DIV_FRAC_MASK  (0x000000F8u)
#define A2D_intClock_DIV_FRAC_SHIFT (3u)
#define A2D_intClock_DIV_INT_MASK   (0xFFFFFF00u)
#define A2D_intClock_DIV_INT_SHIFT  (8u)

#else 

#define A2D_intClock_DIV_REG        (*(reg32 *)A2D_intClock__REGISTER)
#define A2D_intClock_ENABLE_REG     A2D_intClock_DIV_REG
#define A2D_intClock_DIV_FRAC_MASK  A2D_intClock__FRAC_MASK
#define A2D_intClock_DIV_FRAC_SHIFT (16u)
#define A2D_intClock_DIV_INT_MASK   A2D_intClock__DIVIDER_MASK
#define A2D_intClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_A2D_intClock_H) */

/* [] END OF FILE */
