/*******************************************************************************
* File Name: BCKLFT_ESC.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the BCKLFT_ESC
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_BCKLFT_ESC_H)
#define CY_TCPWM_BCKLFT_ESC_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} BCKLFT_ESC_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  BCKLFT_ESC_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define BCKLFT_ESC_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define BCKLFT_ESC_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define BCKLFT_ESC_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define BCKLFT_ESC_QUAD_ENCODING_MODES            (0lu)
#define BCKLFT_ESC_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define BCKLFT_ESC_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define BCKLFT_ESC_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define BCKLFT_ESC_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define BCKLFT_ESC_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define BCKLFT_ESC_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define BCKLFT_ESC_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define BCKLFT_ESC_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define BCKLFT_ESC_TC_RUN_MODE                    (0lu)
#define BCKLFT_ESC_TC_COUNTER_MODE                (0lu)
#define BCKLFT_ESC_TC_COMP_CAP_MODE               (2lu)
#define BCKLFT_ESC_TC_PRESCALER                   (0lu)

/* Signal modes */
#define BCKLFT_ESC_TC_RELOAD_SIGNAL_MODE          (0lu)
#define BCKLFT_ESC_TC_COUNT_SIGNAL_MODE           (3lu)
#define BCKLFT_ESC_TC_START_SIGNAL_MODE           (0lu)
#define BCKLFT_ESC_TC_STOP_SIGNAL_MODE            (0lu)
#define BCKLFT_ESC_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define BCKLFT_ESC_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define BCKLFT_ESC_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define BCKLFT_ESC_TC_START_SIGNAL_PRESENT        (0lu)
#define BCKLFT_ESC_TC_STOP_SIGNAL_PRESENT         (0lu)
#define BCKLFT_ESC_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BCKLFT_ESC_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define BCKLFT_ESC_PWM_KILL_EVENT                 (0lu)
#define BCKLFT_ESC_PWM_STOP_EVENT                 (0lu)
#define BCKLFT_ESC_PWM_MODE                       (4lu)
#define BCKLFT_ESC_PWM_OUT_N_INVERT               (0lu)
#define BCKLFT_ESC_PWM_OUT_INVERT                 (0lu)
#define BCKLFT_ESC_PWM_ALIGN                      (0lu)
#define BCKLFT_ESC_PWM_RUN_MODE                   (0lu)
#define BCKLFT_ESC_PWM_DEAD_TIME_CYCLE            (0lu)
#define BCKLFT_ESC_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define BCKLFT_ESC_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define BCKLFT_ESC_PWM_COUNT_SIGNAL_MODE          (3lu)
#define BCKLFT_ESC_PWM_START_SIGNAL_MODE          (0lu)
#define BCKLFT_ESC_PWM_STOP_SIGNAL_MODE           (0lu)
#define BCKLFT_ESC_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define BCKLFT_ESC_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define BCKLFT_ESC_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define BCKLFT_ESC_PWM_START_SIGNAL_PRESENT       (0lu)
#define BCKLFT_ESC_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define BCKLFT_ESC_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BCKLFT_ESC_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define BCKLFT_ESC_TC_PERIOD_VALUE                (65535lu)
#define BCKLFT_ESC_TC_COMPARE_VALUE               (65535lu)
#define BCKLFT_ESC_TC_COMPARE_BUF_VALUE           (65535lu)
#define BCKLFT_ESC_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define BCKLFT_ESC_PWM_PERIOD_VALUE               (65535lu)
#define BCKLFT_ESC_PWM_PERIOD_BUF_VALUE           (65535lu)
#define BCKLFT_ESC_PWM_PERIOD_SWAP                (0lu)
#define BCKLFT_ESC_PWM_COMPARE_VALUE              (0lu)
#define BCKLFT_ESC_PWM_COMPARE_BUF_VALUE          (65535lu)
#define BCKLFT_ESC_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define BCKLFT_ESC__LEFT 0
#define BCKLFT_ESC__RIGHT 1
#define BCKLFT_ESC__CENTER 2
#define BCKLFT_ESC__ASYMMETRIC 3

#define BCKLFT_ESC__X1 0
#define BCKLFT_ESC__X2 1
#define BCKLFT_ESC__X4 2

#define BCKLFT_ESC__PWM 4
#define BCKLFT_ESC__PWM_DT 5
#define BCKLFT_ESC__PWM_PR 6

#define BCKLFT_ESC__INVERSE 1
#define BCKLFT_ESC__DIRECT 0

#define BCKLFT_ESC__CAPTURE 2
#define BCKLFT_ESC__COMPARE 0

#define BCKLFT_ESC__TRIG_LEVEL 3
#define BCKLFT_ESC__TRIG_RISING 0
#define BCKLFT_ESC__TRIG_FALLING 1
#define BCKLFT_ESC__TRIG_BOTH 2

#define BCKLFT_ESC__INTR_MASK_TC 1
#define BCKLFT_ESC__INTR_MASK_CC_MATCH 2
#define BCKLFT_ESC__INTR_MASK_NONE 0
#define BCKLFT_ESC__INTR_MASK_TC_CC 3

#define BCKLFT_ESC__UNCONFIG 8
#define BCKLFT_ESC__TIMER 1
#define BCKLFT_ESC__QUAD 3
#define BCKLFT_ESC__PWM_SEL 7

#define BCKLFT_ESC__COUNT_UP 0
#define BCKLFT_ESC__COUNT_DOWN 1
#define BCKLFT_ESC__COUNT_UPDOWN0 2
#define BCKLFT_ESC__COUNT_UPDOWN1 3


/* Prescaler */
#define BCKLFT_ESC_PRESCALE_DIVBY1                ((uint32)(0u << BCKLFT_ESC_PRESCALER_SHIFT))
#define BCKLFT_ESC_PRESCALE_DIVBY2                ((uint32)(1u << BCKLFT_ESC_PRESCALER_SHIFT))
#define BCKLFT_ESC_PRESCALE_DIVBY4                ((uint32)(2u << BCKLFT_ESC_PRESCALER_SHIFT))
#define BCKLFT_ESC_PRESCALE_DIVBY8                ((uint32)(3u << BCKLFT_ESC_PRESCALER_SHIFT))
#define BCKLFT_ESC_PRESCALE_DIVBY16               ((uint32)(4u << BCKLFT_ESC_PRESCALER_SHIFT))
#define BCKLFT_ESC_PRESCALE_DIVBY32               ((uint32)(5u << BCKLFT_ESC_PRESCALER_SHIFT))
#define BCKLFT_ESC_PRESCALE_DIVBY64               ((uint32)(6u << BCKLFT_ESC_PRESCALER_SHIFT))
#define BCKLFT_ESC_PRESCALE_DIVBY128              ((uint32)(7u << BCKLFT_ESC_PRESCALER_SHIFT))

/* TCPWM set modes */
#define BCKLFT_ESC_MODE_TIMER_COMPARE             ((uint32)(BCKLFT_ESC__COMPARE         <<  \
                                                                  BCKLFT_ESC_MODE_SHIFT))
#define BCKLFT_ESC_MODE_TIMER_CAPTURE             ((uint32)(BCKLFT_ESC__CAPTURE         <<  \
                                                                  BCKLFT_ESC_MODE_SHIFT))
#define BCKLFT_ESC_MODE_QUAD                      ((uint32)(BCKLFT_ESC__QUAD            <<  \
                                                                  BCKLFT_ESC_MODE_SHIFT))
#define BCKLFT_ESC_MODE_PWM                       ((uint32)(BCKLFT_ESC__PWM             <<  \
                                                                  BCKLFT_ESC_MODE_SHIFT))
#define BCKLFT_ESC_MODE_PWM_DT                    ((uint32)(BCKLFT_ESC__PWM_DT          <<  \
                                                                  BCKLFT_ESC_MODE_SHIFT))
#define BCKLFT_ESC_MODE_PWM_PR                    ((uint32)(BCKLFT_ESC__PWM_PR          <<  \
                                                                  BCKLFT_ESC_MODE_SHIFT))

/* Quad Modes */
#define BCKLFT_ESC_MODE_X1                        ((uint32)(BCKLFT_ESC__X1              <<  \
                                                                  BCKLFT_ESC_QUAD_MODE_SHIFT))
#define BCKLFT_ESC_MODE_X2                        ((uint32)(BCKLFT_ESC__X2              <<  \
                                                                  BCKLFT_ESC_QUAD_MODE_SHIFT))
#define BCKLFT_ESC_MODE_X4                        ((uint32)(BCKLFT_ESC__X4              <<  \
                                                                  BCKLFT_ESC_QUAD_MODE_SHIFT))

/* Counter modes */
#define BCKLFT_ESC_COUNT_UP                       ((uint32)(BCKLFT_ESC__COUNT_UP        <<  \
                                                                  BCKLFT_ESC_UPDOWN_SHIFT))
#define BCKLFT_ESC_COUNT_DOWN                     ((uint32)(BCKLFT_ESC__COUNT_DOWN      <<  \
                                                                  BCKLFT_ESC_UPDOWN_SHIFT))
#define BCKLFT_ESC_COUNT_UPDOWN0                  ((uint32)(BCKLFT_ESC__COUNT_UPDOWN0   <<  \
                                                                  BCKLFT_ESC_UPDOWN_SHIFT))
#define BCKLFT_ESC_COUNT_UPDOWN1                  ((uint32)(BCKLFT_ESC__COUNT_UPDOWN1   <<  \
                                                                  BCKLFT_ESC_UPDOWN_SHIFT))

/* PWM output invert */
#define BCKLFT_ESC_INVERT_LINE                    ((uint32)(BCKLFT_ESC__INVERSE         <<  \
                                                                  BCKLFT_ESC_INV_OUT_SHIFT))
#define BCKLFT_ESC_INVERT_LINE_N                  ((uint32)(BCKLFT_ESC__INVERSE         <<  \
                                                                  BCKLFT_ESC_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define BCKLFT_ESC_TRIG_RISING                    ((uint32)BCKLFT_ESC__TRIG_RISING)
#define BCKLFT_ESC_TRIG_FALLING                   ((uint32)BCKLFT_ESC__TRIG_FALLING)
#define BCKLFT_ESC_TRIG_BOTH                      ((uint32)BCKLFT_ESC__TRIG_BOTH)
#define BCKLFT_ESC_TRIG_LEVEL                     ((uint32)BCKLFT_ESC__TRIG_LEVEL)

/* Interrupt mask */
#define BCKLFT_ESC_INTR_MASK_TC                   ((uint32)BCKLFT_ESC__INTR_MASK_TC)
#define BCKLFT_ESC_INTR_MASK_CC_MATCH             ((uint32)BCKLFT_ESC__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define BCKLFT_ESC_CC_MATCH_SET                   (0x00u)
#define BCKLFT_ESC_CC_MATCH_CLEAR                 (0x01u)
#define BCKLFT_ESC_CC_MATCH_INVERT                (0x02u)
#define BCKLFT_ESC_CC_MATCH_NO_CHANGE             (0x03u)
#define BCKLFT_ESC_OVERLOW_SET                    (0x00u)
#define BCKLFT_ESC_OVERLOW_CLEAR                  (0x04u)
#define BCKLFT_ESC_OVERLOW_INVERT                 (0x08u)
#define BCKLFT_ESC_OVERLOW_NO_CHANGE              (0x0Cu)
#define BCKLFT_ESC_UNDERFLOW_SET                  (0x00u)
#define BCKLFT_ESC_UNDERFLOW_CLEAR                (0x10u)
#define BCKLFT_ESC_UNDERFLOW_INVERT               (0x20u)
#define BCKLFT_ESC_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define BCKLFT_ESC_PWM_MODE_LEFT                  (BCKLFT_ESC_CC_MATCH_CLEAR        |   \
                                                         BCKLFT_ESC_OVERLOW_SET           |   \
                                                         BCKLFT_ESC_UNDERFLOW_NO_CHANGE)
#define BCKLFT_ESC_PWM_MODE_RIGHT                 (BCKLFT_ESC_CC_MATCH_SET          |   \
                                                         BCKLFT_ESC_OVERLOW_NO_CHANGE     |   \
                                                         BCKLFT_ESC_UNDERFLOW_CLEAR)
#define BCKLFT_ESC_PWM_MODE_ASYM                  (BCKLFT_ESC_CC_MATCH_INVERT       |   \
                                                         BCKLFT_ESC_OVERLOW_SET           |   \
                                                         BCKLFT_ESC_UNDERFLOW_CLEAR)

#if (BCKLFT_ESC_CY_TCPWM_V2)
    #if(BCKLFT_ESC_CY_TCPWM_4000)
        #define BCKLFT_ESC_PWM_MODE_CENTER                (BCKLFT_ESC_CC_MATCH_INVERT       |   \
                                                                 BCKLFT_ESC_OVERLOW_NO_CHANGE     |   \
                                                                 BCKLFT_ESC_UNDERFLOW_CLEAR)
    #else
        #define BCKLFT_ESC_PWM_MODE_CENTER                (BCKLFT_ESC_CC_MATCH_INVERT       |   \
                                                                 BCKLFT_ESC_OVERLOW_SET           |   \
                                                                 BCKLFT_ESC_UNDERFLOW_CLEAR)
    #endif /* (BCKLFT_ESC_CY_TCPWM_4000) */
#else
    #define BCKLFT_ESC_PWM_MODE_CENTER                (BCKLFT_ESC_CC_MATCH_INVERT       |   \
                                                             BCKLFT_ESC_OVERLOW_NO_CHANGE     |   \
                                                             BCKLFT_ESC_UNDERFLOW_CLEAR)
#endif /* (BCKLFT_ESC_CY_TCPWM_NEW) */

/* Command operations without condition */
#define BCKLFT_ESC_CMD_CAPTURE                    (0u)
#define BCKLFT_ESC_CMD_RELOAD                     (8u)
#define BCKLFT_ESC_CMD_STOP                       (16u)
#define BCKLFT_ESC_CMD_START                      (24u)

/* Status */
#define BCKLFT_ESC_STATUS_DOWN                    (1u)
#define BCKLFT_ESC_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   BCKLFT_ESC_Init(void);
void   BCKLFT_ESC_Enable(void);
void   BCKLFT_ESC_Start(void);
void   BCKLFT_ESC_Stop(void);

void   BCKLFT_ESC_SetMode(uint32 mode);
void   BCKLFT_ESC_SetCounterMode(uint32 counterMode);
void   BCKLFT_ESC_SetPWMMode(uint32 modeMask);
void   BCKLFT_ESC_SetQDMode(uint32 qdMode);

void   BCKLFT_ESC_SetPrescaler(uint32 prescaler);
void   BCKLFT_ESC_TriggerCommand(uint32 mask, uint32 command);
void   BCKLFT_ESC_SetOneShot(uint32 oneShotEnable);
uint32 BCKLFT_ESC_ReadStatus(void);

void   BCKLFT_ESC_SetPWMSyncKill(uint32 syncKillEnable);
void   BCKLFT_ESC_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   BCKLFT_ESC_SetPWMDeadTime(uint32 deadTime);
void   BCKLFT_ESC_SetPWMInvert(uint32 mask);

void   BCKLFT_ESC_SetInterruptMode(uint32 interruptMask);
uint32 BCKLFT_ESC_GetInterruptSourceMasked(void);
uint32 BCKLFT_ESC_GetInterruptSource(void);
void   BCKLFT_ESC_ClearInterrupt(uint32 interruptMask);
void   BCKLFT_ESC_SetInterrupt(uint32 interruptMask);

void   BCKLFT_ESC_WriteCounter(uint32 count);
uint32 BCKLFT_ESC_ReadCounter(void);

uint32 BCKLFT_ESC_ReadCapture(void);
uint32 BCKLFT_ESC_ReadCaptureBuf(void);

void   BCKLFT_ESC_WritePeriod(uint32 period);
uint32 BCKLFT_ESC_ReadPeriod(void);
void   BCKLFT_ESC_WritePeriodBuf(uint32 periodBuf);
uint32 BCKLFT_ESC_ReadPeriodBuf(void);

void   BCKLFT_ESC_WriteCompare(uint32 compare);
uint32 BCKLFT_ESC_ReadCompare(void);
void   BCKLFT_ESC_WriteCompareBuf(uint32 compareBuf);
uint32 BCKLFT_ESC_ReadCompareBuf(void);

void   BCKLFT_ESC_SetPeriodSwap(uint32 swapEnable);
void   BCKLFT_ESC_SetCompareSwap(uint32 swapEnable);

void   BCKLFT_ESC_SetCaptureMode(uint32 triggerMode);
void   BCKLFT_ESC_SetReloadMode(uint32 triggerMode);
void   BCKLFT_ESC_SetStartMode(uint32 triggerMode);
void   BCKLFT_ESC_SetStopMode(uint32 triggerMode);
void   BCKLFT_ESC_SetCountMode(uint32 triggerMode);

void   BCKLFT_ESC_SaveConfig(void);
void   BCKLFT_ESC_RestoreConfig(void);
void   BCKLFT_ESC_Sleep(void);
void   BCKLFT_ESC_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define BCKLFT_ESC_BLOCK_CONTROL_REG              (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BCKLFT_ESC_BLOCK_CONTROL_PTR              ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BCKLFT_ESC_COMMAND_REG                    (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BCKLFT_ESC_COMMAND_PTR                    ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BCKLFT_ESC_INTRRUPT_CAUSE_REG             (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BCKLFT_ESC_INTRRUPT_CAUSE_PTR             ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BCKLFT_ESC_CONTROL_REG                    (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__CTRL )
#define BCKLFT_ESC_CONTROL_PTR                    ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__CTRL )
#define BCKLFT_ESC_STATUS_REG                     (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__STATUS )
#define BCKLFT_ESC_STATUS_PTR                     ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__STATUS )
#define BCKLFT_ESC_COUNTER_REG                    (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__COUNTER )
#define BCKLFT_ESC_COUNTER_PTR                    ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__COUNTER )
#define BCKLFT_ESC_COMP_CAP_REG                   (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__CC )
#define BCKLFT_ESC_COMP_CAP_PTR                   ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__CC )
#define BCKLFT_ESC_COMP_CAP_BUF_REG               (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__CC_BUFF )
#define BCKLFT_ESC_COMP_CAP_BUF_PTR               ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__CC_BUFF )
#define BCKLFT_ESC_PERIOD_REG                     (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__PERIOD )
#define BCKLFT_ESC_PERIOD_PTR                     ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__PERIOD )
#define BCKLFT_ESC_PERIOD_BUF_REG                 (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BCKLFT_ESC_PERIOD_BUF_PTR                 ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BCKLFT_ESC_TRIG_CONTROL0_REG              (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BCKLFT_ESC_TRIG_CONTROL0_PTR              ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BCKLFT_ESC_TRIG_CONTROL1_REG              (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BCKLFT_ESC_TRIG_CONTROL1_PTR              ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BCKLFT_ESC_TRIG_CONTROL2_REG              (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BCKLFT_ESC_TRIG_CONTROL2_PTR              ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BCKLFT_ESC_INTERRUPT_REQ_REG              (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__INTR )
#define BCKLFT_ESC_INTERRUPT_REQ_PTR              ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__INTR )
#define BCKLFT_ESC_INTERRUPT_SET_REG              (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__INTR_SET )
#define BCKLFT_ESC_INTERRUPT_SET_PTR              ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__INTR_SET )
#define BCKLFT_ESC_INTERRUPT_MASK_REG             (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__INTR_MASK )
#define BCKLFT_ESC_INTERRUPT_MASK_PTR             ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__INTR_MASK )
#define BCKLFT_ESC_INTERRUPT_MASKED_REG           (*(reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__INTR_MASKED )
#define BCKLFT_ESC_INTERRUPT_MASKED_PTR           ( (reg32 *) BCKLFT_ESC_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define BCKLFT_ESC_MASK                           ((uint32)BCKLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define BCKLFT_ESC_RELOAD_CC_SHIFT                (0u)
#define BCKLFT_ESC_RELOAD_PERIOD_SHIFT            (1u)
#define BCKLFT_ESC_PWM_SYNC_KILL_SHIFT            (2u)
#define BCKLFT_ESC_PWM_STOP_KILL_SHIFT            (3u)
#define BCKLFT_ESC_PRESCALER_SHIFT                (8u)
#define BCKLFT_ESC_UPDOWN_SHIFT                   (16u)
#define BCKLFT_ESC_ONESHOT_SHIFT                  (18u)
#define BCKLFT_ESC_QUAD_MODE_SHIFT                (20u)
#define BCKLFT_ESC_INV_OUT_SHIFT                  (20u)
#define BCKLFT_ESC_INV_COMPL_OUT_SHIFT            (21u)
#define BCKLFT_ESC_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define BCKLFT_ESC_RELOAD_CC_MASK                 ((uint32)(BCKLFT_ESC_1BIT_MASK        <<  \
                                                                            BCKLFT_ESC_RELOAD_CC_SHIFT))
#define BCKLFT_ESC_RELOAD_PERIOD_MASK             ((uint32)(BCKLFT_ESC_1BIT_MASK        <<  \
                                                                            BCKLFT_ESC_RELOAD_PERIOD_SHIFT))
#define BCKLFT_ESC_PWM_SYNC_KILL_MASK             ((uint32)(BCKLFT_ESC_1BIT_MASK        <<  \
                                                                            BCKLFT_ESC_PWM_SYNC_KILL_SHIFT))
#define BCKLFT_ESC_PWM_STOP_KILL_MASK             ((uint32)(BCKLFT_ESC_1BIT_MASK        <<  \
                                                                            BCKLFT_ESC_PWM_STOP_KILL_SHIFT))
#define BCKLFT_ESC_PRESCALER_MASK                 ((uint32)(BCKLFT_ESC_8BIT_MASK        <<  \
                                                                            BCKLFT_ESC_PRESCALER_SHIFT))
#define BCKLFT_ESC_UPDOWN_MASK                    ((uint32)(BCKLFT_ESC_2BIT_MASK        <<  \
                                                                            BCKLFT_ESC_UPDOWN_SHIFT))
#define BCKLFT_ESC_ONESHOT_MASK                   ((uint32)(BCKLFT_ESC_1BIT_MASK        <<  \
                                                                            BCKLFT_ESC_ONESHOT_SHIFT))
#define BCKLFT_ESC_QUAD_MODE_MASK                 ((uint32)(BCKLFT_ESC_3BIT_MASK        <<  \
                                                                            BCKLFT_ESC_QUAD_MODE_SHIFT))
#define BCKLFT_ESC_INV_OUT_MASK                   ((uint32)(BCKLFT_ESC_2BIT_MASK        <<  \
                                                                            BCKLFT_ESC_INV_OUT_SHIFT))
#define BCKLFT_ESC_MODE_MASK                      ((uint32)(BCKLFT_ESC_3BIT_MASK        <<  \
                                                                            BCKLFT_ESC_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define BCKLFT_ESC_CAPTURE_SHIFT                  (0u)
#define BCKLFT_ESC_COUNT_SHIFT                    (2u)
#define BCKLFT_ESC_RELOAD_SHIFT                   (4u)
#define BCKLFT_ESC_STOP_SHIFT                     (6u)
#define BCKLFT_ESC_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define BCKLFT_ESC_CAPTURE_MASK                   ((uint32)(BCKLFT_ESC_2BIT_MASK        <<  \
                                                                  BCKLFT_ESC_CAPTURE_SHIFT))
#define BCKLFT_ESC_COUNT_MASK                     ((uint32)(BCKLFT_ESC_2BIT_MASK        <<  \
                                                                  BCKLFT_ESC_COUNT_SHIFT))
#define BCKLFT_ESC_RELOAD_MASK                    ((uint32)(BCKLFT_ESC_2BIT_MASK        <<  \
                                                                  BCKLFT_ESC_RELOAD_SHIFT))
#define BCKLFT_ESC_STOP_MASK                      ((uint32)(BCKLFT_ESC_2BIT_MASK        <<  \
                                                                  BCKLFT_ESC_STOP_SHIFT))
#define BCKLFT_ESC_START_MASK                     ((uint32)(BCKLFT_ESC_2BIT_MASK        <<  \
                                                                  BCKLFT_ESC_START_SHIFT))

/* MASK */
#define BCKLFT_ESC_1BIT_MASK                      ((uint32)0x01u)
#define BCKLFT_ESC_2BIT_MASK                      ((uint32)0x03u)
#define BCKLFT_ESC_3BIT_MASK                      ((uint32)0x07u)
#define BCKLFT_ESC_6BIT_MASK                      ((uint32)0x3Fu)
#define BCKLFT_ESC_8BIT_MASK                      ((uint32)0xFFu)
#define BCKLFT_ESC_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define BCKLFT_ESC_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define BCKLFT_ESC_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(BCKLFT_ESC_QUAD_ENCODING_MODES     << BCKLFT_ESC_QUAD_MODE_SHIFT))       |\
         ((uint32)(BCKLFT_ESC_CONFIG                  << BCKLFT_ESC_MODE_SHIFT)))

#define BCKLFT_ESC_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(BCKLFT_ESC_PWM_STOP_EVENT          << BCKLFT_ESC_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(BCKLFT_ESC_PWM_OUT_INVERT          << BCKLFT_ESC_INV_OUT_SHIFT))         |\
         ((uint32)(BCKLFT_ESC_PWM_OUT_N_INVERT        << BCKLFT_ESC_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(BCKLFT_ESC_PWM_MODE                << BCKLFT_ESC_MODE_SHIFT)))

#define BCKLFT_ESC_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(BCKLFT_ESC_PWM_RUN_MODE         << BCKLFT_ESC_ONESHOT_SHIFT))
            
#define BCKLFT_ESC_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(BCKLFT_ESC_PWM_ALIGN            << BCKLFT_ESC_UPDOWN_SHIFT))

#define BCKLFT_ESC_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(BCKLFT_ESC_PWM_KILL_EVENT      << BCKLFT_ESC_PWM_SYNC_KILL_SHIFT))

#define BCKLFT_ESC_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(BCKLFT_ESC_PWM_DEAD_TIME_CYCLE  << BCKLFT_ESC_PRESCALER_SHIFT))

#define BCKLFT_ESC_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(BCKLFT_ESC_PWM_PRESCALER        << BCKLFT_ESC_PRESCALER_SHIFT))

#define BCKLFT_ESC_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(BCKLFT_ESC_TC_PRESCALER            << BCKLFT_ESC_PRESCALER_SHIFT))       |\
         ((uint32)(BCKLFT_ESC_TC_COUNTER_MODE         << BCKLFT_ESC_UPDOWN_SHIFT))          |\
         ((uint32)(BCKLFT_ESC_TC_RUN_MODE             << BCKLFT_ESC_ONESHOT_SHIFT))         |\
         ((uint32)(BCKLFT_ESC_TC_COMP_CAP_MODE        << BCKLFT_ESC_MODE_SHIFT)))
        
#define BCKLFT_ESC_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(BCKLFT_ESC_QUAD_PHIA_SIGNAL_MODE   << BCKLFT_ESC_COUNT_SHIFT))           |\
         ((uint32)(BCKLFT_ESC_QUAD_INDEX_SIGNAL_MODE  << BCKLFT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(BCKLFT_ESC_QUAD_STOP_SIGNAL_MODE   << BCKLFT_ESC_STOP_SHIFT))            |\
         ((uint32)(BCKLFT_ESC_QUAD_PHIB_SIGNAL_MODE   << BCKLFT_ESC_START_SHIFT)))

#define BCKLFT_ESC_PWM_SIGNALS_MODES                                                              \
        (((uint32)(BCKLFT_ESC_PWM_SWITCH_SIGNAL_MODE  << BCKLFT_ESC_CAPTURE_SHIFT))         |\
         ((uint32)(BCKLFT_ESC_PWM_COUNT_SIGNAL_MODE   << BCKLFT_ESC_COUNT_SHIFT))           |\
         ((uint32)(BCKLFT_ESC_PWM_RELOAD_SIGNAL_MODE  << BCKLFT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(BCKLFT_ESC_PWM_STOP_SIGNAL_MODE    << BCKLFT_ESC_STOP_SHIFT))            |\
         ((uint32)(BCKLFT_ESC_PWM_START_SIGNAL_MODE   << BCKLFT_ESC_START_SHIFT)))

#define BCKLFT_ESC_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(BCKLFT_ESC_TC_CAPTURE_SIGNAL_MODE  << BCKLFT_ESC_CAPTURE_SHIFT))         |\
         ((uint32)(BCKLFT_ESC_TC_COUNT_SIGNAL_MODE    << BCKLFT_ESC_COUNT_SHIFT))           |\
         ((uint32)(BCKLFT_ESC_TC_RELOAD_SIGNAL_MODE   << BCKLFT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(BCKLFT_ESC_TC_STOP_SIGNAL_MODE     << BCKLFT_ESC_STOP_SHIFT))            |\
         ((uint32)(BCKLFT_ESC_TC_START_SIGNAL_MODE    << BCKLFT_ESC_START_SHIFT)))
        
#define BCKLFT_ESC_TIMER_UPDOWN_CNT_USED                                                          \
                ((BCKLFT_ESC__COUNT_UPDOWN0 == BCKLFT_ESC_TC_COUNTER_MODE)                  ||\
                 (BCKLFT_ESC__COUNT_UPDOWN1 == BCKLFT_ESC_TC_COUNTER_MODE))

#define BCKLFT_ESC_PWM_UPDOWN_CNT_USED                                                            \
                ((BCKLFT_ESC__CENTER == BCKLFT_ESC_PWM_ALIGN)                               ||\
                 (BCKLFT_ESC__ASYMMETRIC == BCKLFT_ESC_PWM_ALIGN))               
        
#define BCKLFT_ESC_PWM_PR_INIT_VALUE              (1u)
#define BCKLFT_ESC_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_BCKLFT_ESC_H */

/* [] END OF FILE */
