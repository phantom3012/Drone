/*******************************************************************************
* File Name: FRNTRGHT_ESC.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the FRNTRGHT_ESC
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

#if !defined(CY_TCPWM_FRNTRGHT_ESC_H)
#define CY_TCPWM_FRNTRGHT_ESC_H


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
} FRNTRGHT_ESC_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  FRNTRGHT_ESC_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define FRNTRGHT_ESC_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define FRNTRGHT_ESC_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define FRNTRGHT_ESC_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define FRNTRGHT_ESC_QUAD_ENCODING_MODES            (0lu)
#define FRNTRGHT_ESC_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define FRNTRGHT_ESC_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define FRNTRGHT_ESC_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define FRNTRGHT_ESC_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define FRNTRGHT_ESC_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define FRNTRGHT_ESC_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define FRNTRGHT_ESC_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define FRNTRGHT_ESC_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define FRNTRGHT_ESC_TC_RUN_MODE                    (0lu)
#define FRNTRGHT_ESC_TC_COUNTER_MODE                (0lu)
#define FRNTRGHT_ESC_TC_COMP_CAP_MODE               (2lu)
#define FRNTRGHT_ESC_TC_PRESCALER                   (0lu)

/* Signal modes */
#define FRNTRGHT_ESC_TC_RELOAD_SIGNAL_MODE          (0lu)
#define FRNTRGHT_ESC_TC_COUNT_SIGNAL_MODE           (3lu)
#define FRNTRGHT_ESC_TC_START_SIGNAL_MODE           (0lu)
#define FRNTRGHT_ESC_TC_STOP_SIGNAL_MODE            (0lu)
#define FRNTRGHT_ESC_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define FRNTRGHT_ESC_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define FRNTRGHT_ESC_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define FRNTRGHT_ESC_TC_START_SIGNAL_PRESENT        (0lu)
#define FRNTRGHT_ESC_TC_STOP_SIGNAL_PRESENT         (0lu)
#define FRNTRGHT_ESC_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define FRNTRGHT_ESC_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define FRNTRGHT_ESC_PWM_KILL_EVENT                 (0lu)
#define FRNTRGHT_ESC_PWM_STOP_EVENT                 (0lu)
#define FRNTRGHT_ESC_PWM_MODE                       (4lu)
#define FRNTRGHT_ESC_PWM_OUT_N_INVERT               (0lu)
#define FRNTRGHT_ESC_PWM_OUT_INVERT                 (0lu)
#define FRNTRGHT_ESC_PWM_ALIGN                      (0lu)
#define FRNTRGHT_ESC_PWM_RUN_MODE                   (0lu)
#define FRNTRGHT_ESC_PWM_DEAD_TIME_CYCLE            (0lu)
#define FRNTRGHT_ESC_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define FRNTRGHT_ESC_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define FRNTRGHT_ESC_PWM_COUNT_SIGNAL_MODE          (3lu)
#define FRNTRGHT_ESC_PWM_START_SIGNAL_MODE          (0lu)
#define FRNTRGHT_ESC_PWM_STOP_SIGNAL_MODE           (0lu)
#define FRNTRGHT_ESC_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define FRNTRGHT_ESC_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define FRNTRGHT_ESC_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define FRNTRGHT_ESC_PWM_START_SIGNAL_PRESENT       (0lu)
#define FRNTRGHT_ESC_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define FRNTRGHT_ESC_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define FRNTRGHT_ESC_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define FRNTRGHT_ESC_TC_PERIOD_VALUE                (65535lu)
#define FRNTRGHT_ESC_TC_COMPARE_VALUE               (65535lu)
#define FRNTRGHT_ESC_TC_COMPARE_BUF_VALUE           (65535lu)
#define FRNTRGHT_ESC_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define FRNTRGHT_ESC_PWM_PERIOD_VALUE               (65535lu)
#define FRNTRGHT_ESC_PWM_PERIOD_BUF_VALUE           (65535lu)
#define FRNTRGHT_ESC_PWM_PERIOD_SWAP                (0lu)
#define FRNTRGHT_ESC_PWM_COMPARE_VALUE              (0lu)
#define FRNTRGHT_ESC_PWM_COMPARE_BUF_VALUE          (65535lu)
#define FRNTRGHT_ESC_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define FRNTRGHT_ESC__LEFT 0
#define FRNTRGHT_ESC__RIGHT 1
#define FRNTRGHT_ESC__CENTER 2
#define FRNTRGHT_ESC__ASYMMETRIC 3

#define FRNTRGHT_ESC__X1 0
#define FRNTRGHT_ESC__X2 1
#define FRNTRGHT_ESC__X4 2

#define FRNTRGHT_ESC__PWM 4
#define FRNTRGHT_ESC__PWM_DT 5
#define FRNTRGHT_ESC__PWM_PR 6

#define FRNTRGHT_ESC__INVERSE 1
#define FRNTRGHT_ESC__DIRECT 0

#define FRNTRGHT_ESC__CAPTURE 2
#define FRNTRGHT_ESC__COMPARE 0

#define FRNTRGHT_ESC__TRIG_LEVEL 3
#define FRNTRGHT_ESC__TRIG_RISING 0
#define FRNTRGHT_ESC__TRIG_FALLING 1
#define FRNTRGHT_ESC__TRIG_BOTH 2

#define FRNTRGHT_ESC__INTR_MASK_TC 1
#define FRNTRGHT_ESC__INTR_MASK_CC_MATCH 2
#define FRNTRGHT_ESC__INTR_MASK_NONE 0
#define FRNTRGHT_ESC__INTR_MASK_TC_CC 3

#define FRNTRGHT_ESC__UNCONFIG 8
#define FRNTRGHT_ESC__TIMER 1
#define FRNTRGHT_ESC__QUAD 3
#define FRNTRGHT_ESC__PWM_SEL 7

#define FRNTRGHT_ESC__COUNT_UP 0
#define FRNTRGHT_ESC__COUNT_DOWN 1
#define FRNTRGHT_ESC__COUNT_UPDOWN0 2
#define FRNTRGHT_ESC__COUNT_UPDOWN1 3


/* Prescaler */
#define FRNTRGHT_ESC_PRESCALE_DIVBY1                ((uint32)(0u << FRNTRGHT_ESC_PRESCALER_SHIFT))
#define FRNTRGHT_ESC_PRESCALE_DIVBY2                ((uint32)(1u << FRNTRGHT_ESC_PRESCALER_SHIFT))
#define FRNTRGHT_ESC_PRESCALE_DIVBY4                ((uint32)(2u << FRNTRGHT_ESC_PRESCALER_SHIFT))
#define FRNTRGHT_ESC_PRESCALE_DIVBY8                ((uint32)(3u << FRNTRGHT_ESC_PRESCALER_SHIFT))
#define FRNTRGHT_ESC_PRESCALE_DIVBY16               ((uint32)(4u << FRNTRGHT_ESC_PRESCALER_SHIFT))
#define FRNTRGHT_ESC_PRESCALE_DIVBY32               ((uint32)(5u << FRNTRGHT_ESC_PRESCALER_SHIFT))
#define FRNTRGHT_ESC_PRESCALE_DIVBY64               ((uint32)(6u << FRNTRGHT_ESC_PRESCALER_SHIFT))
#define FRNTRGHT_ESC_PRESCALE_DIVBY128              ((uint32)(7u << FRNTRGHT_ESC_PRESCALER_SHIFT))

/* TCPWM set modes */
#define FRNTRGHT_ESC_MODE_TIMER_COMPARE             ((uint32)(FRNTRGHT_ESC__COMPARE         <<  \
                                                                  FRNTRGHT_ESC_MODE_SHIFT))
#define FRNTRGHT_ESC_MODE_TIMER_CAPTURE             ((uint32)(FRNTRGHT_ESC__CAPTURE         <<  \
                                                                  FRNTRGHT_ESC_MODE_SHIFT))
#define FRNTRGHT_ESC_MODE_QUAD                      ((uint32)(FRNTRGHT_ESC__QUAD            <<  \
                                                                  FRNTRGHT_ESC_MODE_SHIFT))
#define FRNTRGHT_ESC_MODE_PWM                       ((uint32)(FRNTRGHT_ESC__PWM             <<  \
                                                                  FRNTRGHT_ESC_MODE_SHIFT))
#define FRNTRGHT_ESC_MODE_PWM_DT                    ((uint32)(FRNTRGHT_ESC__PWM_DT          <<  \
                                                                  FRNTRGHT_ESC_MODE_SHIFT))
#define FRNTRGHT_ESC_MODE_PWM_PR                    ((uint32)(FRNTRGHT_ESC__PWM_PR          <<  \
                                                                  FRNTRGHT_ESC_MODE_SHIFT))

/* Quad Modes */
#define FRNTRGHT_ESC_MODE_X1                        ((uint32)(FRNTRGHT_ESC__X1              <<  \
                                                                  FRNTRGHT_ESC_QUAD_MODE_SHIFT))
#define FRNTRGHT_ESC_MODE_X2                        ((uint32)(FRNTRGHT_ESC__X2              <<  \
                                                                  FRNTRGHT_ESC_QUAD_MODE_SHIFT))
#define FRNTRGHT_ESC_MODE_X4                        ((uint32)(FRNTRGHT_ESC__X4              <<  \
                                                                  FRNTRGHT_ESC_QUAD_MODE_SHIFT))

/* Counter modes */
#define FRNTRGHT_ESC_COUNT_UP                       ((uint32)(FRNTRGHT_ESC__COUNT_UP        <<  \
                                                                  FRNTRGHT_ESC_UPDOWN_SHIFT))
#define FRNTRGHT_ESC_COUNT_DOWN                     ((uint32)(FRNTRGHT_ESC__COUNT_DOWN      <<  \
                                                                  FRNTRGHT_ESC_UPDOWN_SHIFT))
#define FRNTRGHT_ESC_COUNT_UPDOWN0                  ((uint32)(FRNTRGHT_ESC__COUNT_UPDOWN0   <<  \
                                                                  FRNTRGHT_ESC_UPDOWN_SHIFT))
#define FRNTRGHT_ESC_COUNT_UPDOWN1                  ((uint32)(FRNTRGHT_ESC__COUNT_UPDOWN1   <<  \
                                                                  FRNTRGHT_ESC_UPDOWN_SHIFT))

/* PWM output invert */
#define FRNTRGHT_ESC_INVERT_LINE                    ((uint32)(FRNTRGHT_ESC__INVERSE         <<  \
                                                                  FRNTRGHT_ESC_INV_OUT_SHIFT))
#define FRNTRGHT_ESC_INVERT_LINE_N                  ((uint32)(FRNTRGHT_ESC__INVERSE         <<  \
                                                                  FRNTRGHT_ESC_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define FRNTRGHT_ESC_TRIG_RISING                    ((uint32)FRNTRGHT_ESC__TRIG_RISING)
#define FRNTRGHT_ESC_TRIG_FALLING                   ((uint32)FRNTRGHT_ESC__TRIG_FALLING)
#define FRNTRGHT_ESC_TRIG_BOTH                      ((uint32)FRNTRGHT_ESC__TRIG_BOTH)
#define FRNTRGHT_ESC_TRIG_LEVEL                     ((uint32)FRNTRGHT_ESC__TRIG_LEVEL)

/* Interrupt mask */
#define FRNTRGHT_ESC_INTR_MASK_TC                   ((uint32)FRNTRGHT_ESC__INTR_MASK_TC)
#define FRNTRGHT_ESC_INTR_MASK_CC_MATCH             ((uint32)FRNTRGHT_ESC__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define FRNTRGHT_ESC_CC_MATCH_SET                   (0x00u)
#define FRNTRGHT_ESC_CC_MATCH_CLEAR                 (0x01u)
#define FRNTRGHT_ESC_CC_MATCH_INVERT                (0x02u)
#define FRNTRGHT_ESC_CC_MATCH_NO_CHANGE             (0x03u)
#define FRNTRGHT_ESC_OVERLOW_SET                    (0x00u)
#define FRNTRGHT_ESC_OVERLOW_CLEAR                  (0x04u)
#define FRNTRGHT_ESC_OVERLOW_INVERT                 (0x08u)
#define FRNTRGHT_ESC_OVERLOW_NO_CHANGE              (0x0Cu)
#define FRNTRGHT_ESC_UNDERFLOW_SET                  (0x00u)
#define FRNTRGHT_ESC_UNDERFLOW_CLEAR                (0x10u)
#define FRNTRGHT_ESC_UNDERFLOW_INVERT               (0x20u)
#define FRNTRGHT_ESC_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define FRNTRGHT_ESC_PWM_MODE_LEFT                  (FRNTRGHT_ESC_CC_MATCH_CLEAR        |   \
                                                         FRNTRGHT_ESC_OVERLOW_SET           |   \
                                                         FRNTRGHT_ESC_UNDERFLOW_NO_CHANGE)
#define FRNTRGHT_ESC_PWM_MODE_RIGHT                 (FRNTRGHT_ESC_CC_MATCH_SET          |   \
                                                         FRNTRGHT_ESC_OVERLOW_NO_CHANGE     |   \
                                                         FRNTRGHT_ESC_UNDERFLOW_CLEAR)
#define FRNTRGHT_ESC_PWM_MODE_ASYM                  (FRNTRGHT_ESC_CC_MATCH_INVERT       |   \
                                                         FRNTRGHT_ESC_OVERLOW_SET           |   \
                                                         FRNTRGHT_ESC_UNDERFLOW_CLEAR)

#if (FRNTRGHT_ESC_CY_TCPWM_V2)
    #if(FRNTRGHT_ESC_CY_TCPWM_4000)
        #define FRNTRGHT_ESC_PWM_MODE_CENTER                (FRNTRGHT_ESC_CC_MATCH_INVERT       |   \
                                                                 FRNTRGHT_ESC_OVERLOW_NO_CHANGE     |   \
                                                                 FRNTRGHT_ESC_UNDERFLOW_CLEAR)
    #else
        #define FRNTRGHT_ESC_PWM_MODE_CENTER                (FRNTRGHT_ESC_CC_MATCH_INVERT       |   \
                                                                 FRNTRGHT_ESC_OVERLOW_SET           |   \
                                                                 FRNTRGHT_ESC_UNDERFLOW_CLEAR)
    #endif /* (FRNTRGHT_ESC_CY_TCPWM_4000) */
#else
    #define FRNTRGHT_ESC_PWM_MODE_CENTER                (FRNTRGHT_ESC_CC_MATCH_INVERT       |   \
                                                             FRNTRGHT_ESC_OVERLOW_NO_CHANGE     |   \
                                                             FRNTRGHT_ESC_UNDERFLOW_CLEAR)
#endif /* (FRNTRGHT_ESC_CY_TCPWM_NEW) */

/* Command operations without condition */
#define FRNTRGHT_ESC_CMD_CAPTURE                    (0u)
#define FRNTRGHT_ESC_CMD_RELOAD                     (8u)
#define FRNTRGHT_ESC_CMD_STOP                       (16u)
#define FRNTRGHT_ESC_CMD_START                      (24u)

/* Status */
#define FRNTRGHT_ESC_STATUS_DOWN                    (1u)
#define FRNTRGHT_ESC_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   FRNTRGHT_ESC_Init(void);
void   FRNTRGHT_ESC_Enable(void);
void   FRNTRGHT_ESC_Start(void);
void   FRNTRGHT_ESC_Stop(void);

void   FRNTRGHT_ESC_SetMode(uint32 mode);
void   FRNTRGHT_ESC_SetCounterMode(uint32 counterMode);
void   FRNTRGHT_ESC_SetPWMMode(uint32 modeMask);
void   FRNTRGHT_ESC_SetQDMode(uint32 qdMode);

void   FRNTRGHT_ESC_SetPrescaler(uint32 prescaler);
void   FRNTRGHT_ESC_TriggerCommand(uint32 mask, uint32 command);
void   FRNTRGHT_ESC_SetOneShot(uint32 oneShotEnable);
uint32 FRNTRGHT_ESC_ReadStatus(void);

void   FRNTRGHT_ESC_SetPWMSyncKill(uint32 syncKillEnable);
void   FRNTRGHT_ESC_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   FRNTRGHT_ESC_SetPWMDeadTime(uint32 deadTime);
void   FRNTRGHT_ESC_SetPWMInvert(uint32 mask);

void   FRNTRGHT_ESC_SetInterruptMode(uint32 interruptMask);
uint32 FRNTRGHT_ESC_GetInterruptSourceMasked(void);
uint32 FRNTRGHT_ESC_GetInterruptSource(void);
void   FRNTRGHT_ESC_ClearInterrupt(uint32 interruptMask);
void   FRNTRGHT_ESC_SetInterrupt(uint32 interruptMask);

void   FRNTRGHT_ESC_WriteCounter(uint32 count);
uint32 FRNTRGHT_ESC_ReadCounter(void);

uint32 FRNTRGHT_ESC_ReadCapture(void);
uint32 FRNTRGHT_ESC_ReadCaptureBuf(void);

void   FRNTRGHT_ESC_WritePeriod(uint32 period);
uint32 FRNTRGHT_ESC_ReadPeriod(void);
void   FRNTRGHT_ESC_WritePeriodBuf(uint32 periodBuf);
uint32 FRNTRGHT_ESC_ReadPeriodBuf(void);

void   FRNTRGHT_ESC_WriteCompare(uint32 compare);
uint32 FRNTRGHT_ESC_ReadCompare(void);
void   FRNTRGHT_ESC_WriteCompareBuf(uint32 compareBuf);
uint32 FRNTRGHT_ESC_ReadCompareBuf(void);

void   FRNTRGHT_ESC_SetPeriodSwap(uint32 swapEnable);
void   FRNTRGHT_ESC_SetCompareSwap(uint32 swapEnable);

void   FRNTRGHT_ESC_SetCaptureMode(uint32 triggerMode);
void   FRNTRGHT_ESC_SetReloadMode(uint32 triggerMode);
void   FRNTRGHT_ESC_SetStartMode(uint32 triggerMode);
void   FRNTRGHT_ESC_SetStopMode(uint32 triggerMode);
void   FRNTRGHT_ESC_SetCountMode(uint32 triggerMode);

void   FRNTRGHT_ESC_SaveConfig(void);
void   FRNTRGHT_ESC_RestoreConfig(void);
void   FRNTRGHT_ESC_Sleep(void);
void   FRNTRGHT_ESC_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define FRNTRGHT_ESC_BLOCK_CONTROL_REG              (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define FRNTRGHT_ESC_BLOCK_CONTROL_PTR              ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define FRNTRGHT_ESC_COMMAND_REG                    (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define FRNTRGHT_ESC_COMMAND_PTR                    ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define FRNTRGHT_ESC_INTRRUPT_CAUSE_REG             (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define FRNTRGHT_ESC_INTRRUPT_CAUSE_PTR             ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define FRNTRGHT_ESC_CONTROL_REG                    (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__CTRL )
#define FRNTRGHT_ESC_CONTROL_PTR                    ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__CTRL )
#define FRNTRGHT_ESC_STATUS_REG                     (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__STATUS )
#define FRNTRGHT_ESC_STATUS_PTR                     ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__STATUS )
#define FRNTRGHT_ESC_COUNTER_REG                    (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__COUNTER )
#define FRNTRGHT_ESC_COUNTER_PTR                    ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__COUNTER )
#define FRNTRGHT_ESC_COMP_CAP_REG                   (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__CC )
#define FRNTRGHT_ESC_COMP_CAP_PTR                   ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__CC )
#define FRNTRGHT_ESC_COMP_CAP_BUF_REG               (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__CC_BUFF )
#define FRNTRGHT_ESC_COMP_CAP_BUF_PTR               ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__CC_BUFF )
#define FRNTRGHT_ESC_PERIOD_REG                     (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__PERIOD )
#define FRNTRGHT_ESC_PERIOD_PTR                     ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__PERIOD )
#define FRNTRGHT_ESC_PERIOD_BUF_REG                 (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define FRNTRGHT_ESC_PERIOD_BUF_PTR                 ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define FRNTRGHT_ESC_TRIG_CONTROL0_REG              (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define FRNTRGHT_ESC_TRIG_CONTROL0_PTR              ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define FRNTRGHT_ESC_TRIG_CONTROL1_REG              (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define FRNTRGHT_ESC_TRIG_CONTROL1_PTR              ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define FRNTRGHT_ESC_TRIG_CONTROL2_REG              (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define FRNTRGHT_ESC_TRIG_CONTROL2_PTR              ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define FRNTRGHT_ESC_INTERRUPT_REQ_REG              (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__INTR )
#define FRNTRGHT_ESC_INTERRUPT_REQ_PTR              ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__INTR )
#define FRNTRGHT_ESC_INTERRUPT_SET_REG              (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__INTR_SET )
#define FRNTRGHT_ESC_INTERRUPT_SET_PTR              ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__INTR_SET )
#define FRNTRGHT_ESC_INTERRUPT_MASK_REG             (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__INTR_MASK )
#define FRNTRGHT_ESC_INTERRUPT_MASK_PTR             ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__INTR_MASK )
#define FRNTRGHT_ESC_INTERRUPT_MASKED_REG           (*(reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__INTR_MASKED )
#define FRNTRGHT_ESC_INTERRUPT_MASKED_PTR           ( (reg32 *) FRNTRGHT_ESC_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define FRNTRGHT_ESC_MASK                           ((uint32)FRNTRGHT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define FRNTRGHT_ESC_RELOAD_CC_SHIFT                (0u)
#define FRNTRGHT_ESC_RELOAD_PERIOD_SHIFT            (1u)
#define FRNTRGHT_ESC_PWM_SYNC_KILL_SHIFT            (2u)
#define FRNTRGHT_ESC_PWM_STOP_KILL_SHIFT            (3u)
#define FRNTRGHT_ESC_PRESCALER_SHIFT                (8u)
#define FRNTRGHT_ESC_UPDOWN_SHIFT                   (16u)
#define FRNTRGHT_ESC_ONESHOT_SHIFT                  (18u)
#define FRNTRGHT_ESC_QUAD_MODE_SHIFT                (20u)
#define FRNTRGHT_ESC_INV_OUT_SHIFT                  (20u)
#define FRNTRGHT_ESC_INV_COMPL_OUT_SHIFT            (21u)
#define FRNTRGHT_ESC_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define FRNTRGHT_ESC_RELOAD_CC_MASK                 ((uint32)(FRNTRGHT_ESC_1BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_RELOAD_CC_SHIFT))
#define FRNTRGHT_ESC_RELOAD_PERIOD_MASK             ((uint32)(FRNTRGHT_ESC_1BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_RELOAD_PERIOD_SHIFT))
#define FRNTRGHT_ESC_PWM_SYNC_KILL_MASK             ((uint32)(FRNTRGHT_ESC_1BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_PWM_SYNC_KILL_SHIFT))
#define FRNTRGHT_ESC_PWM_STOP_KILL_MASK             ((uint32)(FRNTRGHT_ESC_1BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_PWM_STOP_KILL_SHIFT))
#define FRNTRGHT_ESC_PRESCALER_MASK                 ((uint32)(FRNTRGHT_ESC_8BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_PRESCALER_SHIFT))
#define FRNTRGHT_ESC_UPDOWN_MASK                    ((uint32)(FRNTRGHT_ESC_2BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_UPDOWN_SHIFT))
#define FRNTRGHT_ESC_ONESHOT_MASK                   ((uint32)(FRNTRGHT_ESC_1BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_ONESHOT_SHIFT))
#define FRNTRGHT_ESC_QUAD_MODE_MASK                 ((uint32)(FRNTRGHT_ESC_3BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_QUAD_MODE_SHIFT))
#define FRNTRGHT_ESC_INV_OUT_MASK                   ((uint32)(FRNTRGHT_ESC_2BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_INV_OUT_SHIFT))
#define FRNTRGHT_ESC_MODE_MASK                      ((uint32)(FRNTRGHT_ESC_3BIT_MASK        <<  \
                                                                            FRNTRGHT_ESC_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define FRNTRGHT_ESC_CAPTURE_SHIFT                  (0u)
#define FRNTRGHT_ESC_COUNT_SHIFT                    (2u)
#define FRNTRGHT_ESC_RELOAD_SHIFT                   (4u)
#define FRNTRGHT_ESC_STOP_SHIFT                     (6u)
#define FRNTRGHT_ESC_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define FRNTRGHT_ESC_CAPTURE_MASK                   ((uint32)(FRNTRGHT_ESC_2BIT_MASK        <<  \
                                                                  FRNTRGHT_ESC_CAPTURE_SHIFT))
#define FRNTRGHT_ESC_COUNT_MASK                     ((uint32)(FRNTRGHT_ESC_2BIT_MASK        <<  \
                                                                  FRNTRGHT_ESC_COUNT_SHIFT))
#define FRNTRGHT_ESC_RELOAD_MASK                    ((uint32)(FRNTRGHT_ESC_2BIT_MASK        <<  \
                                                                  FRNTRGHT_ESC_RELOAD_SHIFT))
#define FRNTRGHT_ESC_STOP_MASK                      ((uint32)(FRNTRGHT_ESC_2BIT_MASK        <<  \
                                                                  FRNTRGHT_ESC_STOP_SHIFT))
#define FRNTRGHT_ESC_START_MASK                     ((uint32)(FRNTRGHT_ESC_2BIT_MASK        <<  \
                                                                  FRNTRGHT_ESC_START_SHIFT))

/* MASK */
#define FRNTRGHT_ESC_1BIT_MASK                      ((uint32)0x01u)
#define FRNTRGHT_ESC_2BIT_MASK                      ((uint32)0x03u)
#define FRNTRGHT_ESC_3BIT_MASK                      ((uint32)0x07u)
#define FRNTRGHT_ESC_6BIT_MASK                      ((uint32)0x3Fu)
#define FRNTRGHT_ESC_8BIT_MASK                      ((uint32)0xFFu)
#define FRNTRGHT_ESC_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define FRNTRGHT_ESC_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define FRNTRGHT_ESC_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(FRNTRGHT_ESC_QUAD_ENCODING_MODES     << FRNTRGHT_ESC_QUAD_MODE_SHIFT))       |\
         ((uint32)(FRNTRGHT_ESC_CONFIG                  << FRNTRGHT_ESC_MODE_SHIFT)))

#define FRNTRGHT_ESC_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(FRNTRGHT_ESC_PWM_STOP_EVENT          << FRNTRGHT_ESC_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(FRNTRGHT_ESC_PWM_OUT_INVERT          << FRNTRGHT_ESC_INV_OUT_SHIFT))         |\
         ((uint32)(FRNTRGHT_ESC_PWM_OUT_N_INVERT        << FRNTRGHT_ESC_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(FRNTRGHT_ESC_PWM_MODE                << FRNTRGHT_ESC_MODE_SHIFT)))

#define FRNTRGHT_ESC_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(FRNTRGHT_ESC_PWM_RUN_MODE         << FRNTRGHT_ESC_ONESHOT_SHIFT))
            
#define FRNTRGHT_ESC_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(FRNTRGHT_ESC_PWM_ALIGN            << FRNTRGHT_ESC_UPDOWN_SHIFT))

#define FRNTRGHT_ESC_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(FRNTRGHT_ESC_PWM_KILL_EVENT      << FRNTRGHT_ESC_PWM_SYNC_KILL_SHIFT))

#define FRNTRGHT_ESC_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(FRNTRGHT_ESC_PWM_DEAD_TIME_CYCLE  << FRNTRGHT_ESC_PRESCALER_SHIFT))

#define FRNTRGHT_ESC_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(FRNTRGHT_ESC_PWM_PRESCALER        << FRNTRGHT_ESC_PRESCALER_SHIFT))

#define FRNTRGHT_ESC_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(FRNTRGHT_ESC_TC_PRESCALER            << FRNTRGHT_ESC_PRESCALER_SHIFT))       |\
         ((uint32)(FRNTRGHT_ESC_TC_COUNTER_MODE         << FRNTRGHT_ESC_UPDOWN_SHIFT))          |\
         ((uint32)(FRNTRGHT_ESC_TC_RUN_MODE             << FRNTRGHT_ESC_ONESHOT_SHIFT))         |\
         ((uint32)(FRNTRGHT_ESC_TC_COMP_CAP_MODE        << FRNTRGHT_ESC_MODE_SHIFT)))
        
#define FRNTRGHT_ESC_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(FRNTRGHT_ESC_QUAD_PHIA_SIGNAL_MODE   << FRNTRGHT_ESC_COUNT_SHIFT))           |\
         ((uint32)(FRNTRGHT_ESC_QUAD_INDEX_SIGNAL_MODE  << FRNTRGHT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(FRNTRGHT_ESC_QUAD_STOP_SIGNAL_MODE   << FRNTRGHT_ESC_STOP_SHIFT))            |\
         ((uint32)(FRNTRGHT_ESC_QUAD_PHIB_SIGNAL_MODE   << FRNTRGHT_ESC_START_SHIFT)))

#define FRNTRGHT_ESC_PWM_SIGNALS_MODES                                                              \
        (((uint32)(FRNTRGHT_ESC_PWM_SWITCH_SIGNAL_MODE  << FRNTRGHT_ESC_CAPTURE_SHIFT))         |\
         ((uint32)(FRNTRGHT_ESC_PWM_COUNT_SIGNAL_MODE   << FRNTRGHT_ESC_COUNT_SHIFT))           |\
         ((uint32)(FRNTRGHT_ESC_PWM_RELOAD_SIGNAL_MODE  << FRNTRGHT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(FRNTRGHT_ESC_PWM_STOP_SIGNAL_MODE    << FRNTRGHT_ESC_STOP_SHIFT))            |\
         ((uint32)(FRNTRGHT_ESC_PWM_START_SIGNAL_MODE   << FRNTRGHT_ESC_START_SHIFT)))

#define FRNTRGHT_ESC_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(FRNTRGHT_ESC_TC_CAPTURE_SIGNAL_MODE  << FRNTRGHT_ESC_CAPTURE_SHIFT))         |\
         ((uint32)(FRNTRGHT_ESC_TC_COUNT_SIGNAL_MODE    << FRNTRGHT_ESC_COUNT_SHIFT))           |\
         ((uint32)(FRNTRGHT_ESC_TC_RELOAD_SIGNAL_MODE   << FRNTRGHT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(FRNTRGHT_ESC_TC_STOP_SIGNAL_MODE     << FRNTRGHT_ESC_STOP_SHIFT))            |\
         ((uint32)(FRNTRGHT_ESC_TC_START_SIGNAL_MODE    << FRNTRGHT_ESC_START_SHIFT)))
        
#define FRNTRGHT_ESC_TIMER_UPDOWN_CNT_USED                                                          \
                ((FRNTRGHT_ESC__COUNT_UPDOWN0 == FRNTRGHT_ESC_TC_COUNTER_MODE)                  ||\
                 (FRNTRGHT_ESC__COUNT_UPDOWN1 == FRNTRGHT_ESC_TC_COUNTER_MODE))

#define FRNTRGHT_ESC_PWM_UPDOWN_CNT_USED                                                            \
                ((FRNTRGHT_ESC__CENTER == FRNTRGHT_ESC_PWM_ALIGN)                               ||\
                 (FRNTRGHT_ESC__ASYMMETRIC == FRNTRGHT_ESC_PWM_ALIGN))               
        
#define FRNTRGHT_ESC_PWM_PR_INIT_VALUE              (1u)
#define FRNTRGHT_ESC_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_FRNTRGHT_ESC_H */

/* [] END OF FILE */
