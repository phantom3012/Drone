/*******************************************************************************
* File Name: RGHT_ESC.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the RGHT_ESC
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

#if !defined(CY_TCPWM_RGHT_ESC_H)
#define CY_TCPWM_RGHT_ESC_H


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
} RGHT_ESC_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  RGHT_ESC_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define RGHT_ESC_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define RGHT_ESC_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define RGHT_ESC_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define RGHT_ESC_QUAD_ENCODING_MODES            (0lu)
#define RGHT_ESC_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define RGHT_ESC_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define RGHT_ESC_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define RGHT_ESC_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define RGHT_ESC_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define RGHT_ESC_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define RGHT_ESC_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define RGHT_ESC_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define RGHT_ESC_TC_RUN_MODE                    (0lu)
#define RGHT_ESC_TC_COUNTER_MODE                (0lu)
#define RGHT_ESC_TC_COMP_CAP_MODE               (2lu)
#define RGHT_ESC_TC_PRESCALER                   (0lu)

/* Signal modes */
#define RGHT_ESC_TC_RELOAD_SIGNAL_MODE          (0lu)
#define RGHT_ESC_TC_COUNT_SIGNAL_MODE           (3lu)
#define RGHT_ESC_TC_START_SIGNAL_MODE           (0lu)
#define RGHT_ESC_TC_STOP_SIGNAL_MODE            (0lu)
#define RGHT_ESC_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define RGHT_ESC_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define RGHT_ESC_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define RGHT_ESC_TC_START_SIGNAL_PRESENT        (0lu)
#define RGHT_ESC_TC_STOP_SIGNAL_PRESENT         (0lu)
#define RGHT_ESC_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define RGHT_ESC_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define RGHT_ESC_PWM_KILL_EVENT                 (0lu)
#define RGHT_ESC_PWM_STOP_EVENT                 (0lu)
#define RGHT_ESC_PWM_MODE                       (4lu)
#define RGHT_ESC_PWM_OUT_N_INVERT               (0lu)
#define RGHT_ESC_PWM_OUT_INVERT                 (0lu)
#define RGHT_ESC_PWM_ALIGN                      (0lu)
#define RGHT_ESC_PWM_RUN_MODE                   (0lu)
#define RGHT_ESC_PWM_DEAD_TIME_CYCLE            (0lu)
#define RGHT_ESC_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define RGHT_ESC_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define RGHT_ESC_PWM_COUNT_SIGNAL_MODE          (3lu)
#define RGHT_ESC_PWM_START_SIGNAL_MODE          (0lu)
#define RGHT_ESC_PWM_STOP_SIGNAL_MODE           (0lu)
#define RGHT_ESC_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define RGHT_ESC_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define RGHT_ESC_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define RGHT_ESC_PWM_START_SIGNAL_PRESENT       (0lu)
#define RGHT_ESC_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define RGHT_ESC_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define RGHT_ESC_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define RGHT_ESC_TC_PERIOD_VALUE                (65535lu)
#define RGHT_ESC_TC_COMPARE_VALUE               (65535lu)
#define RGHT_ESC_TC_COMPARE_BUF_VALUE           (65535lu)
#define RGHT_ESC_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define RGHT_ESC_PWM_PERIOD_VALUE               (65535lu)
#define RGHT_ESC_PWM_PERIOD_BUF_VALUE           (65535lu)
#define RGHT_ESC_PWM_PERIOD_SWAP                (0lu)
#define RGHT_ESC_PWM_COMPARE_VALUE              (0lu)
#define RGHT_ESC_PWM_COMPARE_BUF_VALUE          (65535lu)
#define RGHT_ESC_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define RGHT_ESC__LEFT 0
#define RGHT_ESC__RIGHT 1
#define RGHT_ESC__CENTER 2
#define RGHT_ESC__ASYMMETRIC 3

#define RGHT_ESC__X1 0
#define RGHT_ESC__X2 1
#define RGHT_ESC__X4 2

#define RGHT_ESC__PWM 4
#define RGHT_ESC__PWM_DT 5
#define RGHT_ESC__PWM_PR 6

#define RGHT_ESC__INVERSE 1
#define RGHT_ESC__DIRECT 0

#define RGHT_ESC__CAPTURE 2
#define RGHT_ESC__COMPARE 0

#define RGHT_ESC__TRIG_LEVEL 3
#define RGHT_ESC__TRIG_RISING 0
#define RGHT_ESC__TRIG_FALLING 1
#define RGHT_ESC__TRIG_BOTH 2

#define RGHT_ESC__INTR_MASK_TC 1
#define RGHT_ESC__INTR_MASK_CC_MATCH 2
#define RGHT_ESC__INTR_MASK_NONE 0
#define RGHT_ESC__INTR_MASK_TC_CC 3

#define RGHT_ESC__UNCONFIG 8
#define RGHT_ESC__TIMER 1
#define RGHT_ESC__QUAD 3
#define RGHT_ESC__PWM_SEL 7

#define RGHT_ESC__COUNT_UP 0
#define RGHT_ESC__COUNT_DOWN 1
#define RGHT_ESC__COUNT_UPDOWN0 2
#define RGHT_ESC__COUNT_UPDOWN1 3


/* Prescaler */
#define RGHT_ESC_PRESCALE_DIVBY1                ((uint32)(0u << RGHT_ESC_PRESCALER_SHIFT))
#define RGHT_ESC_PRESCALE_DIVBY2                ((uint32)(1u << RGHT_ESC_PRESCALER_SHIFT))
#define RGHT_ESC_PRESCALE_DIVBY4                ((uint32)(2u << RGHT_ESC_PRESCALER_SHIFT))
#define RGHT_ESC_PRESCALE_DIVBY8                ((uint32)(3u << RGHT_ESC_PRESCALER_SHIFT))
#define RGHT_ESC_PRESCALE_DIVBY16               ((uint32)(4u << RGHT_ESC_PRESCALER_SHIFT))
#define RGHT_ESC_PRESCALE_DIVBY32               ((uint32)(5u << RGHT_ESC_PRESCALER_SHIFT))
#define RGHT_ESC_PRESCALE_DIVBY64               ((uint32)(6u << RGHT_ESC_PRESCALER_SHIFT))
#define RGHT_ESC_PRESCALE_DIVBY128              ((uint32)(7u << RGHT_ESC_PRESCALER_SHIFT))

/* TCPWM set modes */
#define RGHT_ESC_MODE_TIMER_COMPARE             ((uint32)(RGHT_ESC__COMPARE         <<  \
                                                                  RGHT_ESC_MODE_SHIFT))
#define RGHT_ESC_MODE_TIMER_CAPTURE             ((uint32)(RGHT_ESC__CAPTURE         <<  \
                                                                  RGHT_ESC_MODE_SHIFT))
#define RGHT_ESC_MODE_QUAD                      ((uint32)(RGHT_ESC__QUAD            <<  \
                                                                  RGHT_ESC_MODE_SHIFT))
#define RGHT_ESC_MODE_PWM                       ((uint32)(RGHT_ESC__PWM             <<  \
                                                                  RGHT_ESC_MODE_SHIFT))
#define RGHT_ESC_MODE_PWM_DT                    ((uint32)(RGHT_ESC__PWM_DT          <<  \
                                                                  RGHT_ESC_MODE_SHIFT))
#define RGHT_ESC_MODE_PWM_PR                    ((uint32)(RGHT_ESC__PWM_PR          <<  \
                                                                  RGHT_ESC_MODE_SHIFT))

/* Quad Modes */
#define RGHT_ESC_MODE_X1                        ((uint32)(RGHT_ESC__X1              <<  \
                                                                  RGHT_ESC_QUAD_MODE_SHIFT))
#define RGHT_ESC_MODE_X2                        ((uint32)(RGHT_ESC__X2              <<  \
                                                                  RGHT_ESC_QUAD_MODE_SHIFT))
#define RGHT_ESC_MODE_X4                        ((uint32)(RGHT_ESC__X4              <<  \
                                                                  RGHT_ESC_QUAD_MODE_SHIFT))

/* Counter modes */
#define RGHT_ESC_COUNT_UP                       ((uint32)(RGHT_ESC__COUNT_UP        <<  \
                                                                  RGHT_ESC_UPDOWN_SHIFT))
#define RGHT_ESC_COUNT_DOWN                     ((uint32)(RGHT_ESC__COUNT_DOWN      <<  \
                                                                  RGHT_ESC_UPDOWN_SHIFT))
#define RGHT_ESC_COUNT_UPDOWN0                  ((uint32)(RGHT_ESC__COUNT_UPDOWN0   <<  \
                                                                  RGHT_ESC_UPDOWN_SHIFT))
#define RGHT_ESC_COUNT_UPDOWN1                  ((uint32)(RGHT_ESC__COUNT_UPDOWN1   <<  \
                                                                  RGHT_ESC_UPDOWN_SHIFT))

/* PWM output invert */
#define RGHT_ESC_INVERT_LINE                    ((uint32)(RGHT_ESC__INVERSE         <<  \
                                                                  RGHT_ESC_INV_OUT_SHIFT))
#define RGHT_ESC_INVERT_LINE_N                  ((uint32)(RGHT_ESC__INVERSE         <<  \
                                                                  RGHT_ESC_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define RGHT_ESC_TRIG_RISING                    ((uint32)RGHT_ESC__TRIG_RISING)
#define RGHT_ESC_TRIG_FALLING                   ((uint32)RGHT_ESC__TRIG_FALLING)
#define RGHT_ESC_TRIG_BOTH                      ((uint32)RGHT_ESC__TRIG_BOTH)
#define RGHT_ESC_TRIG_LEVEL                     ((uint32)RGHT_ESC__TRIG_LEVEL)

/* Interrupt mask */
#define RGHT_ESC_INTR_MASK_TC                   ((uint32)RGHT_ESC__INTR_MASK_TC)
#define RGHT_ESC_INTR_MASK_CC_MATCH             ((uint32)RGHT_ESC__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define RGHT_ESC_CC_MATCH_SET                   (0x00u)
#define RGHT_ESC_CC_MATCH_CLEAR                 (0x01u)
#define RGHT_ESC_CC_MATCH_INVERT                (0x02u)
#define RGHT_ESC_CC_MATCH_NO_CHANGE             (0x03u)
#define RGHT_ESC_OVERLOW_SET                    (0x00u)
#define RGHT_ESC_OVERLOW_CLEAR                  (0x04u)
#define RGHT_ESC_OVERLOW_INVERT                 (0x08u)
#define RGHT_ESC_OVERLOW_NO_CHANGE              (0x0Cu)
#define RGHT_ESC_UNDERFLOW_SET                  (0x00u)
#define RGHT_ESC_UNDERFLOW_CLEAR                (0x10u)
#define RGHT_ESC_UNDERFLOW_INVERT               (0x20u)
#define RGHT_ESC_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define RGHT_ESC_PWM_MODE_LEFT                  (RGHT_ESC_CC_MATCH_CLEAR        |   \
                                                         RGHT_ESC_OVERLOW_SET           |   \
                                                         RGHT_ESC_UNDERFLOW_NO_CHANGE)
#define RGHT_ESC_PWM_MODE_RIGHT                 (RGHT_ESC_CC_MATCH_SET          |   \
                                                         RGHT_ESC_OVERLOW_NO_CHANGE     |   \
                                                         RGHT_ESC_UNDERFLOW_CLEAR)
#define RGHT_ESC_PWM_MODE_ASYM                  (RGHT_ESC_CC_MATCH_INVERT       |   \
                                                         RGHT_ESC_OVERLOW_SET           |   \
                                                         RGHT_ESC_UNDERFLOW_CLEAR)

#if (RGHT_ESC_CY_TCPWM_V2)
    #if(RGHT_ESC_CY_TCPWM_4000)
        #define RGHT_ESC_PWM_MODE_CENTER                (RGHT_ESC_CC_MATCH_INVERT       |   \
                                                                 RGHT_ESC_OVERLOW_NO_CHANGE     |   \
                                                                 RGHT_ESC_UNDERFLOW_CLEAR)
    #else
        #define RGHT_ESC_PWM_MODE_CENTER                (RGHT_ESC_CC_MATCH_INVERT       |   \
                                                                 RGHT_ESC_OVERLOW_SET           |   \
                                                                 RGHT_ESC_UNDERFLOW_CLEAR)
    #endif /* (RGHT_ESC_CY_TCPWM_4000) */
#else
    #define RGHT_ESC_PWM_MODE_CENTER                (RGHT_ESC_CC_MATCH_INVERT       |   \
                                                             RGHT_ESC_OVERLOW_NO_CHANGE     |   \
                                                             RGHT_ESC_UNDERFLOW_CLEAR)
#endif /* (RGHT_ESC_CY_TCPWM_NEW) */

/* Command operations without condition */
#define RGHT_ESC_CMD_CAPTURE                    (0u)
#define RGHT_ESC_CMD_RELOAD                     (8u)
#define RGHT_ESC_CMD_STOP                       (16u)
#define RGHT_ESC_CMD_START                      (24u)

/* Status */
#define RGHT_ESC_STATUS_DOWN                    (1u)
#define RGHT_ESC_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   RGHT_ESC_Init(void);
void   RGHT_ESC_Enable(void);
void   RGHT_ESC_Start(void);
void   RGHT_ESC_Stop(void);

void   RGHT_ESC_SetMode(uint32 mode);
void   RGHT_ESC_SetCounterMode(uint32 counterMode);
void   RGHT_ESC_SetPWMMode(uint32 modeMask);
void   RGHT_ESC_SetQDMode(uint32 qdMode);

void   RGHT_ESC_SetPrescaler(uint32 prescaler);
void   RGHT_ESC_TriggerCommand(uint32 mask, uint32 command);
void   RGHT_ESC_SetOneShot(uint32 oneShotEnable);
uint32 RGHT_ESC_ReadStatus(void);

void   RGHT_ESC_SetPWMSyncKill(uint32 syncKillEnable);
void   RGHT_ESC_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   RGHT_ESC_SetPWMDeadTime(uint32 deadTime);
void   RGHT_ESC_SetPWMInvert(uint32 mask);

void   RGHT_ESC_SetInterruptMode(uint32 interruptMask);
uint32 RGHT_ESC_GetInterruptSourceMasked(void);
uint32 RGHT_ESC_GetInterruptSource(void);
void   RGHT_ESC_ClearInterrupt(uint32 interruptMask);
void   RGHT_ESC_SetInterrupt(uint32 interruptMask);

void   RGHT_ESC_WriteCounter(uint32 count);
uint32 RGHT_ESC_ReadCounter(void);

uint32 RGHT_ESC_ReadCapture(void);
uint32 RGHT_ESC_ReadCaptureBuf(void);

void   RGHT_ESC_WritePeriod(uint32 period);
uint32 RGHT_ESC_ReadPeriod(void);
void   RGHT_ESC_WritePeriodBuf(uint32 periodBuf);
uint32 RGHT_ESC_ReadPeriodBuf(void);

void   RGHT_ESC_WriteCompare(uint32 compare);
uint32 RGHT_ESC_ReadCompare(void);
void   RGHT_ESC_WriteCompareBuf(uint32 compareBuf);
uint32 RGHT_ESC_ReadCompareBuf(void);

void   RGHT_ESC_SetPeriodSwap(uint32 swapEnable);
void   RGHT_ESC_SetCompareSwap(uint32 swapEnable);

void   RGHT_ESC_SetCaptureMode(uint32 triggerMode);
void   RGHT_ESC_SetReloadMode(uint32 triggerMode);
void   RGHT_ESC_SetStartMode(uint32 triggerMode);
void   RGHT_ESC_SetStopMode(uint32 triggerMode);
void   RGHT_ESC_SetCountMode(uint32 triggerMode);

void   RGHT_ESC_SaveConfig(void);
void   RGHT_ESC_RestoreConfig(void);
void   RGHT_ESC_Sleep(void);
void   RGHT_ESC_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define RGHT_ESC_BLOCK_CONTROL_REG              (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define RGHT_ESC_BLOCK_CONTROL_PTR              ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define RGHT_ESC_COMMAND_REG                    (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define RGHT_ESC_COMMAND_PTR                    ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define RGHT_ESC_INTRRUPT_CAUSE_REG             (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define RGHT_ESC_INTRRUPT_CAUSE_PTR             ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define RGHT_ESC_CONTROL_REG                    (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__CTRL )
#define RGHT_ESC_CONTROL_PTR                    ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__CTRL )
#define RGHT_ESC_STATUS_REG                     (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__STATUS )
#define RGHT_ESC_STATUS_PTR                     ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__STATUS )
#define RGHT_ESC_COUNTER_REG                    (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__COUNTER )
#define RGHT_ESC_COUNTER_PTR                    ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__COUNTER )
#define RGHT_ESC_COMP_CAP_REG                   (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__CC )
#define RGHT_ESC_COMP_CAP_PTR                   ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__CC )
#define RGHT_ESC_COMP_CAP_BUF_REG               (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__CC_BUFF )
#define RGHT_ESC_COMP_CAP_BUF_PTR               ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__CC_BUFF )
#define RGHT_ESC_PERIOD_REG                     (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__PERIOD )
#define RGHT_ESC_PERIOD_PTR                     ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__PERIOD )
#define RGHT_ESC_PERIOD_BUF_REG                 (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define RGHT_ESC_PERIOD_BUF_PTR                 ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define RGHT_ESC_TRIG_CONTROL0_REG              (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define RGHT_ESC_TRIG_CONTROL0_PTR              ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define RGHT_ESC_TRIG_CONTROL1_REG              (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define RGHT_ESC_TRIG_CONTROL1_PTR              ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define RGHT_ESC_TRIG_CONTROL2_REG              (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define RGHT_ESC_TRIG_CONTROL2_PTR              ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define RGHT_ESC_INTERRUPT_REQ_REG              (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__INTR )
#define RGHT_ESC_INTERRUPT_REQ_PTR              ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__INTR )
#define RGHT_ESC_INTERRUPT_SET_REG              (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__INTR_SET )
#define RGHT_ESC_INTERRUPT_SET_PTR              ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__INTR_SET )
#define RGHT_ESC_INTERRUPT_MASK_REG             (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__INTR_MASK )
#define RGHT_ESC_INTERRUPT_MASK_PTR             ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__INTR_MASK )
#define RGHT_ESC_INTERRUPT_MASKED_REG           (*(reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__INTR_MASKED )
#define RGHT_ESC_INTERRUPT_MASKED_PTR           ( (reg32 *) RGHT_ESC_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define RGHT_ESC_MASK                           ((uint32)RGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define RGHT_ESC_RELOAD_CC_SHIFT                (0u)
#define RGHT_ESC_RELOAD_PERIOD_SHIFT            (1u)
#define RGHT_ESC_PWM_SYNC_KILL_SHIFT            (2u)
#define RGHT_ESC_PWM_STOP_KILL_SHIFT            (3u)
#define RGHT_ESC_PRESCALER_SHIFT                (8u)
#define RGHT_ESC_UPDOWN_SHIFT                   (16u)
#define RGHT_ESC_ONESHOT_SHIFT                  (18u)
#define RGHT_ESC_QUAD_MODE_SHIFT                (20u)
#define RGHT_ESC_INV_OUT_SHIFT                  (20u)
#define RGHT_ESC_INV_COMPL_OUT_SHIFT            (21u)
#define RGHT_ESC_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define RGHT_ESC_RELOAD_CC_MASK                 ((uint32)(RGHT_ESC_1BIT_MASK        <<  \
                                                                            RGHT_ESC_RELOAD_CC_SHIFT))
#define RGHT_ESC_RELOAD_PERIOD_MASK             ((uint32)(RGHT_ESC_1BIT_MASK        <<  \
                                                                            RGHT_ESC_RELOAD_PERIOD_SHIFT))
#define RGHT_ESC_PWM_SYNC_KILL_MASK             ((uint32)(RGHT_ESC_1BIT_MASK        <<  \
                                                                            RGHT_ESC_PWM_SYNC_KILL_SHIFT))
#define RGHT_ESC_PWM_STOP_KILL_MASK             ((uint32)(RGHT_ESC_1BIT_MASK        <<  \
                                                                            RGHT_ESC_PWM_STOP_KILL_SHIFT))
#define RGHT_ESC_PRESCALER_MASK                 ((uint32)(RGHT_ESC_8BIT_MASK        <<  \
                                                                            RGHT_ESC_PRESCALER_SHIFT))
#define RGHT_ESC_UPDOWN_MASK                    ((uint32)(RGHT_ESC_2BIT_MASK        <<  \
                                                                            RGHT_ESC_UPDOWN_SHIFT))
#define RGHT_ESC_ONESHOT_MASK                   ((uint32)(RGHT_ESC_1BIT_MASK        <<  \
                                                                            RGHT_ESC_ONESHOT_SHIFT))
#define RGHT_ESC_QUAD_MODE_MASK                 ((uint32)(RGHT_ESC_3BIT_MASK        <<  \
                                                                            RGHT_ESC_QUAD_MODE_SHIFT))
#define RGHT_ESC_INV_OUT_MASK                   ((uint32)(RGHT_ESC_2BIT_MASK        <<  \
                                                                            RGHT_ESC_INV_OUT_SHIFT))
#define RGHT_ESC_MODE_MASK                      ((uint32)(RGHT_ESC_3BIT_MASK        <<  \
                                                                            RGHT_ESC_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define RGHT_ESC_CAPTURE_SHIFT                  (0u)
#define RGHT_ESC_COUNT_SHIFT                    (2u)
#define RGHT_ESC_RELOAD_SHIFT                   (4u)
#define RGHT_ESC_STOP_SHIFT                     (6u)
#define RGHT_ESC_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define RGHT_ESC_CAPTURE_MASK                   ((uint32)(RGHT_ESC_2BIT_MASK        <<  \
                                                                  RGHT_ESC_CAPTURE_SHIFT))
#define RGHT_ESC_COUNT_MASK                     ((uint32)(RGHT_ESC_2BIT_MASK        <<  \
                                                                  RGHT_ESC_COUNT_SHIFT))
#define RGHT_ESC_RELOAD_MASK                    ((uint32)(RGHT_ESC_2BIT_MASK        <<  \
                                                                  RGHT_ESC_RELOAD_SHIFT))
#define RGHT_ESC_STOP_MASK                      ((uint32)(RGHT_ESC_2BIT_MASK        <<  \
                                                                  RGHT_ESC_STOP_SHIFT))
#define RGHT_ESC_START_MASK                     ((uint32)(RGHT_ESC_2BIT_MASK        <<  \
                                                                  RGHT_ESC_START_SHIFT))

/* MASK */
#define RGHT_ESC_1BIT_MASK                      ((uint32)0x01u)
#define RGHT_ESC_2BIT_MASK                      ((uint32)0x03u)
#define RGHT_ESC_3BIT_MASK                      ((uint32)0x07u)
#define RGHT_ESC_6BIT_MASK                      ((uint32)0x3Fu)
#define RGHT_ESC_8BIT_MASK                      ((uint32)0xFFu)
#define RGHT_ESC_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define RGHT_ESC_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define RGHT_ESC_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(RGHT_ESC_QUAD_ENCODING_MODES     << RGHT_ESC_QUAD_MODE_SHIFT))       |\
         ((uint32)(RGHT_ESC_CONFIG                  << RGHT_ESC_MODE_SHIFT)))

#define RGHT_ESC_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(RGHT_ESC_PWM_STOP_EVENT          << RGHT_ESC_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(RGHT_ESC_PWM_OUT_INVERT          << RGHT_ESC_INV_OUT_SHIFT))         |\
         ((uint32)(RGHT_ESC_PWM_OUT_N_INVERT        << RGHT_ESC_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(RGHT_ESC_PWM_MODE                << RGHT_ESC_MODE_SHIFT)))

#define RGHT_ESC_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(RGHT_ESC_PWM_RUN_MODE         << RGHT_ESC_ONESHOT_SHIFT))
            
#define RGHT_ESC_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(RGHT_ESC_PWM_ALIGN            << RGHT_ESC_UPDOWN_SHIFT))

#define RGHT_ESC_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(RGHT_ESC_PWM_KILL_EVENT      << RGHT_ESC_PWM_SYNC_KILL_SHIFT))

#define RGHT_ESC_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(RGHT_ESC_PWM_DEAD_TIME_CYCLE  << RGHT_ESC_PRESCALER_SHIFT))

#define RGHT_ESC_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(RGHT_ESC_PWM_PRESCALER        << RGHT_ESC_PRESCALER_SHIFT))

#define RGHT_ESC_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(RGHT_ESC_TC_PRESCALER            << RGHT_ESC_PRESCALER_SHIFT))       |\
         ((uint32)(RGHT_ESC_TC_COUNTER_MODE         << RGHT_ESC_UPDOWN_SHIFT))          |\
         ((uint32)(RGHT_ESC_TC_RUN_MODE             << RGHT_ESC_ONESHOT_SHIFT))         |\
         ((uint32)(RGHT_ESC_TC_COMP_CAP_MODE        << RGHT_ESC_MODE_SHIFT)))
        
#define RGHT_ESC_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(RGHT_ESC_QUAD_PHIA_SIGNAL_MODE   << RGHT_ESC_COUNT_SHIFT))           |\
         ((uint32)(RGHT_ESC_QUAD_INDEX_SIGNAL_MODE  << RGHT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(RGHT_ESC_QUAD_STOP_SIGNAL_MODE   << RGHT_ESC_STOP_SHIFT))            |\
         ((uint32)(RGHT_ESC_QUAD_PHIB_SIGNAL_MODE   << RGHT_ESC_START_SHIFT)))

#define RGHT_ESC_PWM_SIGNALS_MODES                                                              \
        (((uint32)(RGHT_ESC_PWM_SWITCH_SIGNAL_MODE  << RGHT_ESC_CAPTURE_SHIFT))         |\
         ((uint32)(RGHT_ESC_PWM_COUNT_SIGNAL_MODE   << RGHT_ESC_COUNT_SHIFT))           |\
         ((uint32)(RGHT_ESC_PWM_RELOAD_SIGNAL_MODE  << RGHT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(RGHT_ESC_PWM_STOP_SIGNAL_MODE    << RGHT_ESC_STOP_SHIFT))            |\
         ((uint32)(RGHT_ESC_PWM_START_SIGNAL_MODE   << RGHT_ESC_START_SHIFT)))

#define RGHT_ESC_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(RGHT_ESC_TC_CAPTURE_SIGNAL_MODE  << RGHT_ESC_CAPTURE_SHIFT))         |\
         ((uint32)(RGHT_ESC_TC_COUNT_SIGNAL_MODE    << RGHT_ESC_COUNT_SHIFT))           |\
         ((uint32)(RGHT_ESC_TC_RELOAD_SIGNAL_MODE   << RGHT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(RGHT_ESC_TC_STOP_SIGNAL_MODE     << RGHT_ESC_STOP_SHIFT))            |\
         ((uint32)(RGHT_ESC_TC_START_SIGNAL_MODE    << RGHT_ESC_START_SHIFT)))
        
#define RGHT_ESC_TIMER_UPDOWN_CNT_USED                                                          \
                ((RGHT_ESC__COUNT_UPDOWN0 == RGHT_ESC_TC_COUNTER_MODE)                  ||\
                 (RGHT_ESC__COUNT_UPDOWN1 == RGHT_ESC_TC_COUNTER_MODE))

#define RGHT_ESC_PWM_UPDOWN_CNT_USED                                                            \
                ((RGHT_ESC__CENTER == RGHT_ESC_PWM_ALIGN)                               ||\
                 (RGHT_ESC__ASYMMETRIC == RGHT_ESC_PWM_ALIGN))               
        
#define RGHT_ESC_PWM_PR_INIT_VALUE              (1u)
#define RGHT_ESC_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_RGHT_ESC_H */

/* [] END OF FILE */
