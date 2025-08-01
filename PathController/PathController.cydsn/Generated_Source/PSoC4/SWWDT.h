/*******************************************************************************
* File Name: SWWDT.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the SWWDT
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

#if !defined(CY_TCPWM_SWWDT_H)
#define CY_TCPWM_SWWDT_H


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
} SWWDT_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  SWWDT_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define SWWDT_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define SWWDT_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define SWWDT_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define SWWDT_QUAD_ENCODING_MODES            (0lu)
#define SWWDT_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define SWWDT_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define SWWDT_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define SWWDT_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define SWWDT_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define SWWDT_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define SWWDT_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define SWWDT_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define SWWDT_TC_RUN_MODE                    (0lu)
#define SWWDT_TC_COUNTER_MODE                (0lu)
#define SWWDT_TC_COMP_CAP_MODE               (2lu)
#define SWWDT_TC_PRESCALER                   (0lu)

/* Signal modes */
#define SWWDT_TC_RELOAD_SIGNAL_MODE          (0lu)
#define SWWDT_TC_COUNT_SIGNAL_MODE           (3lu)
#define SWWDT_TC_START_SIGNAL_MODE           (0lu)
#define SWWDT_TC_STOP_SIGNAL_MODE            (0lu)
#define SWWDT_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define SWWDT_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define SWWDT_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define SWWDT_TC_START_SIGNAL_PRESENT        (0lu)
#define SWWDT_TC_STOP_SIGNAL_PRESENT         (0lu)
#define SWWDT_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SWWDT_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define SWWDT_PWM_KILL_EVENT                 (0lu)
#define SWWDT_PWM_STOP_EVENT                 (0lu)
#define SWWDT_PWM_MODE                       (4lu)
#define SWWDT_PWM_OUT_N_INVERT               (0lu)
#define SWWDT_PWM_OUT_INVERT                 (0lu)
#define SWWDT_PWM_ALIGN                      (0lu)
#define SWWDT_PWM_RUN_MODE                   (0lu)
#define SWWDT_PWM_DEAD_TIME_CYCLE            (0lu)
#define SWWDT_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define SWWDT_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define SWWDT_PWM_COUNT_SIGNAL_MODE          (3lu)
#define SWWDT_PWM_START_SIGNAL_MODE          (0lu)
#define SWWDT_PWM_STOP_SIGNAL_MODE           (0lu)
#define SWWDT_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define SWWDT_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define SWWDT_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define SWWDT_PWM_START_SIGNAL_PRESENT       (0lu)
#define SWWDT_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define SWWDT_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SWWDT_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define SWWDT_TC_PERIOD_VALUE                (40000lu)
#define SWWDT_TC_COMPARE_VALUE               (65535lu)
#define SWWDT_TC_COMPARE_BUF_VALUE           (65535lu)
#define SWWDT_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define SWWDT_PWM_PERIOD_VALUE               (65535lu)
#define SWWDT_PWM_PERIOD_BUF_VALUE           (65535lu)
#define SWWDT_PWM_PERIOD_SWAP                (0lu)
#define SWWDT_PWM_COMPARE_VALUE              (65535lu)
#define SWWDT_PWM_COMPARE_BUF_VALUE          (65535lu)
#define SWWDT_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define SWWDT__LEFT 0
#define SWWDT__RIGHT 1
#define SWWDT__CENTER 2
#define SWWDT__ASYMMETRIC 3

#define SWWDT__X1 0
#define SWWDT__X2 1
#define SWWDT__X4 2

#define SWWDT__PWM 4
#define SWWDT__PWM_DT 5
#define SWWDT__PWM_PR 6

#define SWWDT__INVERSE 1
#define SWWDT__DIRECT 0

#define SWWDT__CAPTURE 2
#define SWWDT__COMPARE 0

#define SWWDT__TRIG_LEVEL 3
#define SWWDT__TRIG_RISING 0
#define SWWDT__TRIG_FALLING 1
#define SWWDT__TRIG_BOTH 2

#define SWWDT__INTR_MASK_TC 1
#define SWWDT__INTR_MASK_CC_MATCH 2
#define SWWDT__INTR_MASK_NONE 0
#define SWWDT__INTR_MASK_TC_CC 3

#define SWWDT__UNCONFIG 8
#define SWWDT__TIMER 1
#define SWWDT__QUAD 3
#define SWWDT__PWM_SEL 7

#define SWWDT__COUNT_UP 0
#define SWWDT__COUNT_DOWN 1
#define SWWDT__COUNT_UPDOWN0 2
#define SWWDT__COUNT_UPDOWN1 3


/* Prescaler */
#define SWWDT_PRESCALE_DIVBY1                ((uint32)(0u << SWWDT_PRESCALER_SHIFT))
#define SWWDT_PRESCALE_DIVBY2                ((uint32)(1u << SWWDT_PRESCALER_SHIFT))
#define SWWDT_PRESCALE_DIVBY4                ((uint32)(2u << SWWDT_PRESCALER_SHIFT))
#define SWWDT_PRESCALE_DIVBY8                ((uint32)(3u << SWWDT_PRESCALER_SHIFT))
#define SWWDT_PRESCALE_DIVBY16               ((uint32)(4u << SWWDT_PRESCALER_SHIFT))
#define SWWDT_PRESCALE_DIVBY32               ((uint32)(5u << SWWDT_PRESCALER_SHIFT))
#define SWWDT_PRESCALE_DIVBY64               ((uint32)(6u << SWWDT_PRESCALER_SHIFT))
#define SWWDT_PRESCALE_DIVBY128              ((uint32)(7u << SWWDT_PRESCALER_SHIFT))

/* TCPWM set modes */
#define SWWDT_MODE_TIMER_COMPARE             ((uint32)(SWWDT__COMPARE         <<  \
                                                                  SWWDT_MODE_SHIFT))
#define SWWDT_MODE_TIMER_CAPTURE             ((uint32)(SWWDT__CAPTURE         <<  \
                                                                  SWWDT_MODE_SHIFT))
#define SWWDT_MODE_QUAD                      ((uint32)(SWWDT__QUAD            <<  \
                                                                  SWWDT_MODE_SHIFT))
#define SWWDT_MODE_PWM                       ((uint32)(SWWDT__PWM             <<  \
                                                                  SWWDT_MODE_SHIFT))
#define SWWDT_MODE_PWM_DT                    ((uint32)(SWWDT__PWM_DT          <<  \
                                                                  SWWDT_MODE_SHIFT))
#define SWWDT_MODE_PWM_PR                    ((uint32)(SWWDT__PWM_PR          <<  \
                                                                  SWWDT_MODE_SHIFT))

/* Quad Modes */
#define SWWDT_MODE_X1                        ((uint32)(SWWDT__X1              <<  \
                                                                  SWWDT_QUAD_MODE_SHIFT))
#define SWWDT_MODE_X2                        ((uint32)(SWWDT__X2              <<  \
                                                                  SWWDT_QUAD_MODE_SHIFT))
#define SWWDT_MODE_X4                        ((uint32)(SWWDT__X4              <<  \
                                                                  SWWDT_QUAD_MODE_SHIFT))

/* Counter modes */
#define SWWDT_COUNT_UP                       ((uint32)(SWWDT__COUNT_UP        <<  \
                                                                  SWWDT_UPDOWN_SHIFT))
#define SWWDT_COUNT_DOWN                     ((uint32)(SWWDT__COUNT_DOWN      <<  \
                                                                  SWWDT_UPDOWN_SHIFT))
#define SWWDT_COUNT_UPDOWN0                  ((uint32)(SWWDT__COUNT_UPDOWN0   <<  \
                                                                  SWWDT_UPDOWN_SHIFT))
#define SWWDT_COUNT_UPDOWN1                  ((uint32)(SWWDT__COUNT_UPDOWN1   <<  \
                                                                  SWWDT_UPDOWN_SHIFT))

/* PWM output invert */
#define SWWDT_INVERT_LINE                    ((uint32)(SWWDT__INVERSE         <<  \
                                                                  SWWDT_INV_OUT_SHIFT))
#define SWWDT_INVERT_LINE_N                  ((uint32)(SWWDT__INVERSE         <<  \
                                                                  SWWDT_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define SWWDT_TRIG_RISING                    ((uint32)SWWDT__TRIG_RISING)
#define SWWDT_TRIG_FALLING                   ((uint32)SWWDT__TRIG_FALLING)
#define SWWDT_TRIG_BOTH                      ((uint32)SWWDT__TRIG_BOTH)
#define SWWDT_TRIG_LEVEL                     ((uint32)SWWDT__TRIG_LEVEL)

/* Interrupt mask */
#define SWWDT_INTR_MASK_TC                   ((uint32)SWWDT__INTR_MASK_TC)
#define SWWDT_INTR_MASK_CC_MATCH             ((uint32)SWWDT__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define SWWDT_CC_MATCH_SET                   (0x00u)
#define SWWDT_CC_MATCH_CLEAR                 (0x01u)
#define SWWDT_CC_MATCH_INVERT                (0x02u)
#define SWWDT_CC_MATCH_NO_CHANGE             (0x03u)
#define SWWDT_OVERLOW_SET                    (0x00u)
#define SWWDT_OVERLOW_CLEAR                  (0x04u)
#define SWWDT_OVERLOW_INVERT                 (0x08u)
#define SWWDT_OVERLOW_NO_CHANGE              (0x0Cu)
#define SWWDT_UNDERFLOW_SET                  (0x00u)
#define SWWDT_UNDERFLOW_CLEAR                (0x10u)
#define SWWDT_UNDERFLOW_INVERT               (0x20u)
#define SWWDT_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define SWWDT_PWM_MODE_LEFT                  (SWWDT_CC_MATCH_CLEAR        |   \
                                                         SWWDT_OVERLOW_SET           |   \
                                                         SWWDT_UNDERFLOW_NO_CHANGE)
#define SWWDT_PWM_MODE_RIGHT                 (SWWDT_CC_MATCH_SET          |   \
                                                         SWWDT_OVERLOW_NO_CHANGE     |   \
                                                         SWWDT_UNDERFLOW_CLEAR)
#define SWWDT_PWM_MODE_ASYM                  (SWWDT_CC_MATCH_INVERT       |   \
                                                         SWWDT_OVERLOW_SET           |   \
                                                         SWWDT_UNDERFLOW_CLEAR)

#if (SWWDT_CY_TCPWM_V2)
    #if(SWWDT_CY_TCPWM_4000)
        #define SWWDT_PWM_MODE_CENTER                (SWWDT_CC_MATCH_INVERT       |   \
                                                                 SWWDT_OVERLOW_NO_CHANGE     |   \
                                                                 SWWDT_UNDERFLOW_CLEAR)
    #else
        #define SWWDT_PWM_MODE_CENTER                (SWWDT_CC_MATCH_INVERT       |   \
                                                                 SWWDT_OVERLOW_SET           |   \
                                                                 SWWDT_UNDERFLOW_CLEAR)
    #endif /* (SWWDT_CY_TCPWM_4000) */
#else
    #define SWWDT_PWM_MODE_CENTER                (SWWDT_CC_MATCH_INVERT       |   \
                                                             SWWDT_OVERLOW_NO_CHANGE     |   \
                                                             SWWDT_UNDERFLOW_CLEAR)
#endif /* (SWWDT_CY_TCPWM_NEW) */

/* Command operations without condition */
#define SWWDT_CMD_CAPTURE                    (0u)
#define SWWDT_CMD_RELOAD                     (8u)
#define SWWDT_CMD_STOP                       (16u)
#define SWWDT_CMD_START                      (24u)

/* Status */
#define SWWDT_STATUS_DOWN                    (1u)
#define SWWDT_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   SWWDT_Init(void);
void   SWWDT_Enable(void);
void   SWWDT_Start(void);
void   SWWDT_Stop(void);

void   SWWDT_SetMode(uint32 mode);
void   SWWDT_SetCounterMode(uint32 counterMode);
void   SWWDT_SetPWMMode(uint32 modeMask);
void   SWWDT_SetQDMode(uint32 qdMode);

void   SWWDT_SetPrescaler(uint32 prescaler);
void   SWWDT_TriggerCommand(uint32 mask, uint32 command);
void   SWWDT_SetOneShot(uint32 oneShotEnable);
uint32 SWWDT_ReadStatus(void);

void   SWWDT_SetPWMSyncKill(uint32 syncKillEnable);
void   SWWDT_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   SWWDT_SetPWMDeadTime(uint32 deadTime);
void   SWWDT_SetPWMInvert(uint32 mask);

void   SWWDT_SetInterruptMode(uint32 interruptMask);
uint32 SWWDT_GetInterruptSourceMasked(void);
uint32 SWWDT_GetInterruptSource(void);
void   SWWDT_ClearInterrupt(uint32 interruptMask);
void   SWWDT_SetInterrupt(uint32 interruptMask);

void   SWWDT_WriteCounter(uint32 count);
uint32 SWWDT_ReadCounter(void);

uint32 SWWDT_ReadCapture(void);
uint32 SWWDT_ReadCaptureBuf(void);

void   SWWDT_WritePeriod(uint32 period);
uint32 SWWDT_ReadPeriod(void);
void   SWWDT_WritePeriodBuf(uint32 periodBuf);
uint32 SWWDT_ReadPeriodBuf(void);

void   SWWDT_WriteCompare(uint32 compare);
uint32 SWWDT_ReadCompare(void);
void   SWWDT_WriteCompareBuf(uint32 compareBuf);
uint32 SWWDT_ReadCompareBuf(void);

void   SWWDT_SetPeriodSwap(uint32 swapEnable);
void   SWWDT_SetCompareSwap(uint32 swapEnable);

void   SWWDT_SetCaptureMode(uint32 triggerMode);
void   SWWDT_SetReloadMode(uint32 triggerMode);
void   SWWDT_SetStartMode(uint32 triggerMode);
void   SWWDT_SetStopMode(uint32 triggerMode);
void   SWWDT_SetCountMode(uint32 triggerMode);

void   SWWDT_SaveConfig(void);
void   SWWDT_RestoreConfig(void);
void   SWWDT_Sleep(void);
void   SWWDT_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define SWWDT_BLOCK_CONTROL_REG              (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SWWDT_BLOCK_CONTROL_PTR              ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SWWDT_COMMAND_REG                    (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SWWDT_COMMAND_PTR                    ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SWWDT_INTRRUPT_CAUSE_REG             (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SWWDT_INTRRUPT_CAUSE_PTR             ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SWWDT_CONTROL_REG                    (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__CTRL )
#define SWWDT_CONTROL_PTR                    ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__CTRL )
#define SWWDT_STATUS_REG                     (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__STATUS )
#define SWWDT_STATUS_PTR                     ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__STATUS )
#define SWWDT_COUNTER_REG                    (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__COUNTER )
#define SWWDT_COUNTER_PTR                    ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__COUNTER )
#define SWWDT_COMP_CAP_REG                   (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__CC )
#define SWWDT_COMP_CAP_PTR                   ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__CC )
#define SWWDT_COMP_CAP_BUF_REG               (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__CC_BUFF )
#define SWWDT_COMP_CAP_BUF_PTR               ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__CC_BUFF )
#define SWWDT_PERIOD_REG                     (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__PERIOD )
#define SWWDT_PERIOD_PTR                     ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__PERIOD )
#define SWWDT_PERIOD_BUF_REG                 (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SWWDT_PERIOD_BUF_PTR                 ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SWWDT_TRIG_CONTROL0_REG              (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SWWDT_TRIG_CONTROL0_PTR              ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SWWDT_TRIG_CONTROL1_REG              (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SWWDT_TRIG_CONTROL1_PTR              ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SWWDT_TRIG_CONTROL2_REG              (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SWWDT_TRIG_CONTROL2_PTR              ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SWWDT_INTERRUPT_REQ_REG              (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__INTR )
#define SWWDT_INTERRUPT_REQ_PTR              ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__INTR )
#define SWWDT_INTERRUPT_SET_REG              (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__INTR_SET )
#define SWWDT_INTERRUPT_SET_PTR              ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__INTR_SET )
#define SWWDT_INTERRUPT_MASK_REG             (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__INTR_MASK )
#define SWWDT_INTERRUPT_MASK_PTR             ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__INTR_MASK )
#define SWWDT_INTERRUPT_MASKED_REG           (*(reg32 *) SWWDT_cy_m0s8_tcpwm_1__INTR_MASKED )
#define SWWDT_INTERRUPT_MASKED_PTR           ( (reg32 *) SWWDT_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define SWWDT_MASK                           ((uint32)SWWDT_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define SWWDT_RELOAD_CC_SHIFT                (0u)
#define SWWDT_RELOAD_PERIOD_SHIFT            (1u)
#define SWWDT_PWM_SYNC_KILL_SHIFT            (2u)
#define SWWDT_PWM_STOP_KILL_SHIFT            (3u)
#define SWWDT_PRESCALER_SHIFT                (8u)
#define SWWDT_UPDOWN_SHIFT                   (16u)
#define SWWDT_ONESHOT_SHIFT                  (18u)
#define SWWDT_QUAD_MODE_SHIFT                (20u)
#define SWWDT_INV_OUT_SHIFT                  (20u)
#define SWWDT_INV_COMPL_OUT_SHIFT            (21u)
#define SWWDT_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define SWWDT_RELOAD_CC_MASK                 ((uint32)(SWWDT_1BIT_MASK        <<  \
                                                                            SWWDT_RELOAD_CC_SHIFT))
#define SWWDT_RELOAD_PERIOD_MASK             ((uint32)(SWWDT_1BIT_MASK        <<  \
                                                                            SWWDT_RELOAD_PERIOD_SHIFT))
#define SWWDT_PWM_SYNC_KILL_MASK             ((uint32)(SWWDT_1BIT_MASK        <<  \
                                                                            SWWDT_PWM_SYNC_KILL_SHIFT))
#define SWWDT_PWM_STOP_KILL_MASK             ((uint32)(SWWDT_1BIT_MASK        <<  \
                                                                            SWWDT_PWM_STOP_KILL_SHIFT))
#define SWWDT_PRESCALER_MASK                 ((uint32)(SWWDT_8BIT_MASK        <<  \
                                                                            SWWDT_PRESCALER_SHIFT))
#define SWWDT_UPDOWN_MASK                    ((uint32)(SWWDT_2BIT_MASK        <<  \
                                                                            SWWDT_UPDOWN_SHIFT))
#define SWWDT_ONESHOT_MASK                   ((uint32)(SWWDT_1BIT_MASK        <<  \
                                                                            SWWDT_ONESHOT_SHIFT))
#define SWWDT_QUAD_MODE_MASK                 ((uint32)(SWWDT_3BIT_MASK        <<  \
                                                                            SWWDT_QUAD_MODE_SHIFT))
#define SWWDT_INV_OUT_MASK                   ((uint32)(SWWDT_2BIT_MASK        <<  \
                                                                            SWWDT_INV_OUT_SHIFT))
#define SWWDT_MODE_MASK                      ((uint32)(SWWDT_3BIT_MASK        <<  \
                                                                            SWWDT_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define SWWDT_CAPTURE_SHIFT                  (0u)
#define SWWDT_COUNT_SHIFT                    (2u)
#define SWWDT_RELOAD_SHIFT                   (4u)
#define SWWDT_STOP_SHIFT                     (6u)
#define SWWDT_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define SWWDT_CAPTURE_MASK                   ((uint32)(SWWDT_2BIT_MASK        <<  \
                                                                  SWWDT_CAPTURE_SHIFT))
#define SWWDT_COUNT_MASK                     ((uint32)(SWWDT_2BIT_MASK        <<  \
                                                                  SWWDT_COUNT_SHIFT))
#define SWWDT_RELOAD_MASK                    ((uint32)(SWWDT_2BIT_MASK        <<  \
                                                                  SWWDT_RELOAD_SHIFT))
#define SWWDT_STOP_MASK                      ((uint32)(SWWDT_2BIT_MASK        <<  \
                                                                  SWWDT_STOP_SHIFT))
#define SWWDT_START_MASK                     ((uint32)(SWWDT_2BIT_MASK        <<  \
                                                                  SWWDT_START_SHIFT))

/* MASK */
#define SWWDT_1BIT_MASK                      ((uint32)0x01u)
#define SWWDT_2BIT_MASK                      ((uint32)0x03u)
#define SWWDT_3BIT_MASK                      ((uint32)0x07u)
#define SWWDT_6BIT_MASK                      ((uint32)0x3Fu)
#define SWWDT_8BIT_MASK                      ((uint32)0xFFu)
#define SWWDT_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define SWWDT_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define SWWDT_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(SWWDT_QUAD_ENCODING_MODES     << SWWDT_QUAD_MODE_SHIFT))       |\
         ((uint32)(SWWDT_CONFIG                  << SWWDT_MODE_SHIFT)))

#define SWWDT_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(SWWDT_PWM_STOP_EVENT          << SWWDT_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(SWWDT_PWM_OUT_INVERT          << SWWDT_INV_OUT_SHIFT))         |\
         ((uint32)(SWWDT_PWM_OUT_N_INVERT        << SWWDT_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(SWWDT_PWM_MODE                << SWWDT_MODE_SHIFT)))

#define SWWDT_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(SWWDT_PWM_RUN_MODE         << SWWDT_ONESHOT_SHIFT))
            
#define SWWDT_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(SWWDT_PWM_ALIGN            << SWWDT_UPDOWN_SHIFT))

#define SWWDT_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(SWWDT_PWM_KILL_EVENT      << SWWDT_PWM_SYNC_KILL_SHIFT))

#define SWWDT_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(SWWDT_PWM_DEAD_TIME_CYCLE  << SWWDT_PRESCALER_SHIFT))

#define SWWDT_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(SWWDT_PWM_PRESCALER        << SWWDT_PRESCALER_SHIFT))

#define SWWDT_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(SWWDT_TC_PRESCALER            << SWWDT_PRESCALER_SHIFT))       |\
         ((uint32)(SWWDT_TC_COUNTER_MODE         << SWWDT_UPDOWN_SHIFT))          |\
         ((uint32)(SWWDT_TC_RUN_MODE             << SWWDT_ONESHOT_SHIFT))         |\
         ((uint32)(SWWDT_TC_COMP_CAP_MODE        << SWWDT_MODE_SHIFT)))
        
#define SWWDT_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(SWWDT_QUAD_PHIA_SIGNAL_MODE   << SWWDT_COUNT_SHIFT))           |\
         ((uint32)(SWWDT_QUAD_INDEX_SIGNAL_MODE  << SWWDT_RELOAD_SHIFT))          |\
         ((uint32)(SWWDT_QUAD_STOP_SIGNAL_MODE   << SWWDT_STOP_SHIFT))            |\
         ((uint32)(SWWDT_QUAD_PHIB_SIGNAL_MODE   << SWWDT_START_SHIFT)))

#define SWWDT_PWM_SIGNALS_MODES                                                              \
        (((uint32)(SWWDT_PWM_SWITCH_SIGNAL_MODE  << SWWDT_CAPTURE_SHIFT))         |\
         ((uint32)(SWWDT_PWM_COUNT_SIGNAL_MODE   << SWWDT_COUNT_SHIFT))           |\
         ((uint32)(SWWDT_PWM_RELOAD_SIGNAL_MODE  << SWWDT_RELOAD_SHIFT))          |\
         ((uint32)(SWWDT_PWM_STOP_SIGNAL_MODE    << SWWDT_STOP_SHIFT))            |\
         ((uint32)(SWWDT_PWM_START_SIGNAL_MODE   << SWWDT_START_SHIFT)))

#define SWWDT_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(SWWDT_TC_CAPTURE_SIGNAL_MODE  << SWWDT_CAPTURE_SHIFT))         |\
         ((uint32)(SWWDT_TC_COUNT_SIGNAL_MODE    << SWWDT_COUNT_SHIFT))           |\
         ((uint32)(SWWDT_TC_RELOAD_SIGNAL_MODE   << SWWDT_RELOAD_SHIFT))          |\
         ((uint32)(SWWDT_TC_STOP_SIGNAL_MODE     << SWWDT_STOP_SHIFT))            |\
         ((uint32)(SWWDT_TC_START_SIGNAL_MODE    << SWWDT_START_SHIFT)))
        
#define SWWDT_TIMER_UPDOWN_CNT_USED                                                          \
                ((SWWDT__COUNT_UPDOWN0 == SWWDT_TC_COUNTER_MODE)                  ||\
                 (SWWDT__COUNT_UPDOWN1 == SWWDT_TC_COUNTER_MODE))

#define SWWDT_PWM_UPDOWN_CNT_USED                                                            \
                ((SWWDT__CENTER == SWWDT_PWM_ALIGN)                               ||\
                 (SWWDT__ASYMMETRIC == SWWDT_PWM_ALIGN))               
        
#define SWWDT_PWM_PR_INIT_VALUE              (1u)
#define SWWDT_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_SWWDT_H */

/* [] END OF FILE */
