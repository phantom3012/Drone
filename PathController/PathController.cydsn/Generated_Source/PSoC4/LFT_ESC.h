/*******************************************************************************
* File Name: FRNTLFT_ESC.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the FRNTLFT_ESC
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

#if !defined(CY_TCPWM_FRNTLFT_ESC_H)
#define CY_TCPWM_FRNTLFT_ESC_H


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
} FRNTLFT_ESC_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  FRNTLFT_ESC_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define FRNTLFT_ESC_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define FRNTLFT_ESC_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define FRNTLFT_ESC_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define FRNTLFT_ESC_QUAD_ENCODING_MODES            (0lu)
#define FRNTLFT_ESC_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define FRNTLFT_ESC_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define FRNTLFT_ESC_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define FRNTLFT_ESC_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define FRNTLFT_ESC_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define FRNTLFT_ESC_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define FRNTLFT_ESC_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define FRNTLFT_ESC_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define FRNTLFT_ESC_TC_RUN_MODE                    (0lu)
#define FRNTLFT_ESC_TC_COUNTER_MODE                (0lu)
#define FRNTLFT_ESC_TC_COMP_CAP_MODE               (2lu)
#define FRNTLFT_ESC_TC_PRESCALER                   (0lu)

/* Signal modes */
#define FRNTLFT_ESC_TC_RELOAD_SIGNAL_MODE          (0lu)
#define FRNTLFT_ESC_TC_COUNT_SIGNAL_MODE           (3lu)
#define FRNTLFT_ESC_TC_START_SIGNAL_MODE           (0lu)
#define FRNTLFT_ESC_TC_STOP_SIGNAL_MODE            (0lu)
#define FRNTLFT_ESC_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define FRNTLFT_ESC_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define FRNTLFT_ESC_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define FRNTLFT_ESC_TC_START_SIGNAL_PRESENT        (0lu)
#define FRNTLFT_ESC_TC_STOP_SIGNAL_PRESENT         (0lu)
#define FRNTLFT_ESC_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define FRNTLFT_ESC_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define FRNTLFT_ESC_PWM_KILL_EVENT                 (0lu)
#define FRNTLFT_ESC_PWM_STOP_EVENT                 (0lu)
#define FRNTLFT_ESC_PWM_MODE                       (4lu)
#define FRNTLFT_ESC_PWM_OUT_N_INVERT               (0lu)
#define FRNTLFT_ESC_PWM_OUT_INVERT                 (0lu)
#define FRNTLFT_ESC_PWM_ALIGN                      (0lu)
#define FRNTLFT_ESC_PWM_RUN_MODE                   (0lu)
#define FRNTLFT_ESC_PWM_DEAD_TIME_CYCLE            (0lu)
#define FRNTLFT_ESC_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define FRNTLFT_ESC_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define FRNTLFT_ESC_PWM_COUNT_SIGNAL_MODE          (3lu)
#define FRNTLFT_ESC_PWM_START_SIGNAL_MODE          (0lu)
#define FRNTLFT_ESC_PWM_STOP_SIGNAL_MODE           (0lu)
#define FRNTLFT_ESC_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define FRNTLFT_ESC_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define FRNTLFT_ESC_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define FRNTLFT_ESC_PWM_START_SIGNAL_PRESENT       (0lu)
#define FRNTLFT_ESC_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define FRNTLFT_ESC_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define FRNTLFT_ESC_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define FRNTLFT_ESC_TC_PERIOD_VALUE                (65535lu)
#define FRNTLFT_ESC_TC_COMPARE_VALUE               (65535lu)
#define FRNTLFT_ESC_TC_COMPARE_BUF_VALUE           (65535lu)
#define FRNTLFT_ESC_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define FRNTLFT_ESC_PWM_PERIOD_VALUE               (65535lu)
#define FRNTLFT_ESC_PWM_PERIOD_BUF_VALUE           (65535lu)
#define FRNTLFT_ESC_PWM_PERIOD_SWAP                (0lu)
#define FRNTLFT_ESC_PWM_COMPARE_VALUE              (0lu)
#define FRNTLFT_ESC_PWM_COMPARE_BUF_VALUE          (65535lu)
#define FRNTLFT_ESC_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define FRNTLFT_ESC__LEFT 0
#define FRNTLFT_ESC__RIGHT 1
#define FRNTLFT_ESC__CENTER 2
#define FRNTLFT_ESC__ASYMMETRIC 3

#define FRNTLFT_ESC__X1 0
#define FRNTLFT_ESC__X2 1
#define FRNTLFT_ESC__X4 2

#define FRNTLFT_ESC__PWM 4
#define FRNTLFT_ESC__PWM_DT 5
#define FRNTLFT_ESC__PWM_PR 6

#define FRNTLFT_ESC__INVERSE 1
#define FRNTLFT_ESC__DIRECT 0

#define FRNTLFT_ESC__CAPTURE 2
#define FRNTLFT_ESC__COMPARE 0

#define FRNTLFT_ESC__TRIG_LEVEL 3
#define FRNTLFT_ESC__TRIG_RISING 0
#define FRNTLFT_ESC__TRIG_FALLING 1
#define FRNTLFT_ESC__TRIG_BOTH 2

#define FRNTLFT_ESC__INTR_MASK_TC 1
#define FRNTLFT_ESC__INTR_MASK_CC_MATCH 2
#define FRNTLFT_ESC__INTR_MASK_NONE 0
#define FRNTLFT_ESC__INTR_MASK_TC_CC 3

#define FRNTLFT_ESC__UNCONFIG 8
#define FRNTLFT_ESC__TIMER 1
#define FRNTLFT_ESC__QUAD 3
#define FRNTLFT_ESC__PWM_SEL 7

#define FRNTLFT_ESC__COUNT_UP 0
#define FRNTLFT_ESC__COUNT_DOWN 1
#define FRNTLFT_ESC__COUNT_UPDOWN0 2
#define FRNTLFT_ESC__COUNT_UPDOWN1 3


/* Prescaler */
#define FRNTLFT_ESC_PRESCALE_DIVBY1                ((uint32)(0u << FRNTLFT_ESC_PRESCALER_SHIFT))
#define FRNTLFT_ESC_PRESCALE_DIVBY2                ((uint32)(1u << FRNTLFT_ESC_PRESCALER_SHIFT))
#define FRNTLFT_ESC_PRESCALE_DIVBY4                ((uint32)(2u << FRNTLFT_ESC_PRESCALER_SHIFT))
#define FRNTLFT_ESC_PRESCALE_DIVBY8                ((uint32)(3u << FRNTLFT_ESC_PRESCALER_SHIFT))
#define FRNTLFT_ESC_PRESCALE_DIVBY16               ((uint32)(4u << FRNTLFT_ESC_PRESCALER_SHIFT))
#define FRNTLFT_ESC_PRESCALE_DIVBY32               ((uint32)(5u << FRNTLFT_ESC_PRESCALER_SHIFT))
#define FRNTLFT_ESC_PRESCALE_DIVBY64               ((uint32)(6u << FRNTLFT_ESC_PRESCALER_SHIFT))
#define FRNTLFT_ESC_PRESCALE_DIVBY128              ((uint32)(7u << FRNTLFT_ESC_PRESCALER_SHIFT))

/* TCPWM set modes */
#define FRNTLFT_ESC_MODE_TIMER_COMPARE             ((uint32)(FRNTLFT_ESC__COMPARE         <<  \
                                                                  FRNTLFT_ESC_MODE_SHIFT))
#define FRNTLFT_ESC_MODE_TIMER_CAPTURE             ((uint32)(FRNTLFT_ESC__CAPTURE         <<  \
                                                                  FRNTLFT_ESC_MODE_SHIFT))
#define FRNTLFT_ESC_MODE_QUAD                      ((uint32)(FRNTLFT_ESC__QUAD            <<  \
                                                                  FRNTLFT_ESC_MODE_SHIFT))
#define FRNTLFT_ESC_MODE_PWM                       ((uint32)(FRNTLFT_ESC__PWM             <<  \
                                                                  FRNTLFT_ESC_MODE_SHIFT))
#define FRNTLFT_ESC_MODE_PWM_DT                    ((uint32)(FRNTLFT_ESC__PWM_DT          <<  \
                                                                  FRNTLFT_ESC_MODE_SHIFT))
#define FRNTLFT_ESC_MODE_PWM_PR                    ((uint32)(FRNTLFT_ESC__PWM_PR          <<  \
                                                                  FRNTLFT_ESC_MODE_SHIFT))

/* Quad Modes */
#define FRNTLFT_ESC_MODE_X1                        ((uint32)(FRNTLFT_ESC__X1              <<  \
                                                                  FRNTLFT_ESC_QUAD_MODE_SHIFT))
#define FRNTLFT_ESC_MODE_X2                        ((uint32)(FRNTLFT_ESC__X2              <<  \
                                                                  FRNTLFT_ESC_QUAD_MODE_SHIFT))
#define FRNTLFT_ESC_MODE_X4                        ((uint32)(FRNTLFT_ESC__X4              <<  \
                                                                  FRNTLFT_ESC_QUAD_MODE_SHIFT))

/* Counter modes */
#define FRNTLFT_ESC_COUNT_UP                       ((uint32)(FRNTLFT_ESC__COUNT_UP        <<  \
                                                                  FRNTLFT_ESC_UPDOWN_SHIFT))
#define FRNTLFT_ESC_COUNT_DOWN                     ((uint32)(FRNTLFT_ESC__COUNT_DOWN      <<  \
                                                                  FRNTLFT_ESC_UPDOWN_SHIFT))
#define FRNTLFT_ESC_COUNT_UPDOWN0                  ((uint32)(FRNTLFT_ESC__COUNT_UPDOWN0   <<  \
                                                                  FRNTLFT_ESC_UPDOWN_SHIFT))
#define FRNTLFT_ESC_COUNT_UPDOWN1                  ((uint32)(FRNTLFT_ESC__COUNT_UPDOWN1   <<  \
                                                                  FRNTLFT_ESC_UPDOWN_SHIFT))

/* PWM output invert */
#define FRNTLFT_ESC_INVERT_LINE                    ((uint32)(FRNTLFT_ESC__INVERSE         <<  \
                                                                  FRNTLFT_ESC_INV_OUT_SHIFT))
#define FRNTLFT_ESC_INVERT_LINE_N                  ((uint32)(FRNTLFT_ESC__INVERSE         <<  \
                                                                  FRNTLFT_ESC_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define FRNTLFT_ESC_TRIG_RISING                    ((uint32)FRNTLFT_ESC__TRIG_RISING)
#define FRNTLFT_ESC_TRIG_FALLING                   ((uint32)FRNTLFT_ESC__TRIG_FALLING)
#define FRNTLFT_ESC_TRIG_BOTH                      ((uint32)FRNTLFT_ESC__TRIG_BOTH)
#define FRNTLFT_ESC_TRIG_LEVEL                     ((uint32)FRNTLFT_ESC__TRIG_LEVEL)

/* Interrupt mask */
#define FRNTLFT_ESC_INTR_MASK_TC                   ((uint32)FRNTLFT_ESC__INTR_MASK_TC)
#define FRNTLFT_ESC_INTR_MASK_CC_MATCH             ((uint32)FRNTLFT_ESC__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define FRNTLFT_ESC_CC_MATCH_SET                   (0x00u)
#define FRNTLFT_ESC_CC_MATCH_CLEAR                 (0x01u)
#define FRNTLFT_ESC_CC_MATCH_INVERT                (0x02u)
#define FRNTLFT_ESC_CC_MATCH_NO_CHANGE             (0x03u)
#define FRNTLFT_ESC_OVERLOW_SET                    (0x00u)
#define FRNTLFT_ESC_OVERLOW_CLEAR                  (0x04u)
#define FRNTLFT_ESC_OVERLOW_INVERT                 (0x08u)
#define FRNTLFT_ESC_OVERLOW_NO_CHANGE              (0x0Cu)
#define FRNTLFT_ESC_UNDERFLOW_SET                  (0x00u)
#define FRNTLFT_ESC_UNDERFLOW_CLEAR                (0x10u)
#define FRNTLFT_ESC_UNDERFLOW_INVERT               (0x20u)
#define FRNTLFT_ESC_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define FRNTLFT_ESC_PWM_MODE_LEFT                  (FRNTLFT_ESC_CC_MATCH_CLEAR        |   \
                                                         FRNTLFT_ESC_OVERLOW_SET           |   \
                                                         FRNTLFT_ESC_UNDERFLOW_NO_CHANGE)
#define FRNTLFT_ESC_PWM_MODE_RIGHT                 (FRNTLFT_ESC_CC_MATCH_SET          |   \
                                                         FRNTLFT_ESC_OVERLOW_NO_CHANGE     |   \
                                                         FRNTLFT_ESC_UNDERFLOW_CLEAR)
#define FRNTLFT_ESC_PWM_MODE_ASYM                  (FRNTLFT_ESC_CC_MATCH_INVERT       |   \
                                                         FRNTLFT_ESC_OVERLOW_SET           |   \
                                                         FRNTLFT_ESC_UNDERFLOW_CLEAR)

#if (FRNTLFT_ESC_CY_TCPWM_V2)
    #if(FRNTLFT_ESC_CY_TCPWM_4000)
        #define FRNTLFT_ESC_PWM_MODE_CENTER                (FRNTLFT_ESC_CC_MATCH_INVERT       |   \
                                                                 FRNTLFT_ESC_OVERLOW_NO_CHANGE     |   \
                                                                 FRNTLFT_ESC_UNDERFLOW_CLEAR)
    #else
        #define FRNTLFT_ESC_PWM_MODE_CENTER                (FRNTLFT_ESC_CC_MATCH_INVERT       |   \
                                                                 FRNTLFT_ESC_OVERLOW_SET           |   \
                                                                 FRNTLFT_ESC_UNDERFLOW_CLEAR)
    #endif /* (FRNTLFT_ESC_CY_TCPWM_4000) */
#else
    #define FRNTLFT_ESC_PWM_MODE_CENTER                (FRNTLFT_ESC_CC_MATCH_INVERT       |   \
                                                             FRNTLFT_ESC_OVERLOW_NO_CHANGE     |   \
                                                             FRNTLFT_ESC_UNDERFLOW_CLEAR)
#endif /* (FRNTLFT_ESC_CY_TCPWM_NEW) */

/* Command operations without condition */
#define FRNTLFT_ESC_CMD_CAPTURE                    (0u)
#define FRNTLFT_ESC_CMD_RELOAD                     (8u)
#define FRNTLFT_ESC_CMD_STOP                       (16u)
#define FRNTLFT_ESC_CMD_START                      (24u)

/* Status */
#define FRNTLFT_ESC_STATUS_DOWN                    (1u)
#define FRNTLFT_ESC_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   FRNTLFT_ESC_Init(void);
void   FRNTLFT_ESC_Enable(void);
void   FRNTLFT_ESC_Start(void);
void   FRNTLFT_ESC_Stop(void);

void   FRNTLFT_ESC_SetMode(uint32 mode);
void   FRNTLFT_ESC_SetCounterMode(uint32 counterMode);
void   FRNTLFT_ESC_SetPWMMode(uint32 modeMask);
void   FRNTLFT_ESC_SetQDMode(uint32 qdMode);

void   FRNTLFT_ESC_SetPrescaler(uint32 prescaler);
void   FRNTLFT_ESC_TriggerCommand(uint32 mask, uint32 command);
void   FRNTLFT_ESC_SetOneShot(uint32 oneShotEnable);
uint32 FRNTLFT_ESC_ReadStatus(void);

void   FRNTLFT_ESC_SetPWMSyncKill(uint32 syncKillEnable);
void   FRNTLFT_ESC_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   FRNTLFT_ESC_SetPWMDeadTime(uint32 deadTime);
void   FRNTLFT_ESC_SetPWMInvert(uint32 mask);

void   FRNTLFT_ESC_SetInterruptMode(uint32 interruptMask);
uint32 FRNTLFT_ESC_GetInterruptSourceMasked(void);
uint32 FRNTLFT_ESC_GetInterruptSource(void);
void   FRNTLFT_ESC_ClearInterrupt(uint32 interruptMask);
void   FRNTLFT_ESC_SetInterrupt(uint32 interruptMask);

void   FRNTFRNTLFT_ESC_WriteCounter(uint32 count);
uint32 FRNTLFT_ESC_ReadCounter(void);

uint32 FRNTLFT_ESC_ReadCapture(void);
uint32 FRNTLFT_ESC_ReadCaptureBuf(void);

void   FRNTFRNTLFT_ESC_WritePeriod(uint32 period);
uint32 FRNTLFT_ESC_ReadPeriod(void);
void   FRNTFRNTLFT_ESC_WritePeriodBuf(uint32 periodBuf);
uint32 FRNTLFT_ESC_ReadPeriodBuf(void);

void   FRNTFRNTLFT_ESC_WriteCompare(uint32 compare);
uint32 FRNTLFT_ESC_ReadCompare(void);
void   FRNTFRNTLFT_ESC_WriteCompareBuf(uint32 compareBuf);
uint32 FRNTLFT_ESC_ReadCompareBuf(void);

void   FRNTLFT_ESC_SetPeriodSwap(uint32 swapEnable);
void   FRNTLFT_ESC_SetCompareSwap(uint32 swapEnable);

void   FRNTLFT_ESC_SetCaptureMode(uint32 triggerMode);
void   FRNTLFT_ESC_SetReloadMode(uint32 triggerMode);
void   FRNTLFT_ESC_SetStartMode(uint32 triggerMode);
void   FRNTLFT_ESC_SetStopMode(uint32 triggerMode);
void   FRNTLFT_ESC_SetCountMode(uint32 triggerMode);

void   FRNTLFT_ESC_SaveConfig(void);
void   FRNTLFT_ESC_RestoreConfig(void);
void   FRNTLFT_ESC_Sleep(void);
void   FRNTFRNTLFT_ESC_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define FRNTLFT_ESC_BLOCK_CONTROL_REG              (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define FRNTLFT_ESC_BLOCK_CONTROL_PTR              ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define FRNTLFT_ESC_COMMAND_REG                    (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define FRNTLFT_ESC_COMMAND_PTR                    ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define FRNTLFT_ESC_INTRRUPT_CAUSE_REG             (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define FRNTLFT_ESC_INTRRUPT_CAUSE_PTR             ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define FRNTLFT_ESC_CONTROL_REG                    (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__CTRL )
#define FRNTLFT_ESC_CONTROL_PTR                    ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__CTRL )
#define FRNTLFT_ESC_STATUS_REG                     (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__STATUS )
#define FRNTLFT_ESC_STATUS_PTR                     ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__STATUS )
#define FRNTLFT_ESC_COUNTER_REG                    (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__COUNTER )
#define FRNTLFT_ESC_COUNTER_PTR                    ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__COUNTER )
#define FRNTLFT_ESC_COMP_CAP_REG                   (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__CC )
#define FRNTLFT_ESC_COMP_CAP_PTR                   ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__CC )
#define FRNTLFT_ESC_COMP_CAP_BUF_REG               (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__CC_BUFF )
#define FRNTLFT_ESC_COMP_CAP_BUF_PTR               ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__CC_BUFF )
#define FRNTLFT_ESC_PERIOD_REG                     (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__PERIOD )
#define FRNTLFT_ESC_PERIOD_PTR                     ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__PERIOD )
#define FRNTLFT_ESC_PERIOD_BUF_REG                 (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define FRNTLFT_ESC_PERIOD_BUF_PTR                 ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define FRNTLFT_ESC_TRIG_CONTROL0_REG              (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define FRNTLFT_ESC_TRIG_CONTROL0_PTR              ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define FRNTLFT_ESC_TRIG_CONTROL1_REG              (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define FRNTLFT_ESC_TRIG_CONTROL1_PTR              ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define FRNTLFT_ESC_TRIG_CONTROL2_REG              (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define FRNTLFT_ESC_TRIG_CONTROL2_PTR              ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define FRNTLFT_ESC_INTERRUPT_REQ_REG              (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__INTR )
#define FRNTLFT_ESC_INTERRUPT_REQ_PTR              ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__INTR )
#define FRNTLFT_ESC_INTERRUPT_SET_REG              (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__INTR_SET )
#define FRNTLFT_ESC_INTERRUPT_SET_PTR              ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__INTR_SET )
#define FRNTLFT_ESC_INTERRUPT_MASK_REG             (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__INTR_MASK )
#define FRNTLFT_ESC_INTERRUPT_MASK_PTR             ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__INTR_MASK )
#define FRNTLFT_ESC_INTERRUPT_MASKED_REG           (*(reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__INTR_MASKED )
#define FRNTLFT_ESC_INTERRUPT_MASKED_PTR           ( (reg32 *) FRNTLFT_ESC_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define FRNTLFT_ESC_MASK                           ((uint32)FRNTLFT_ESC_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define FRNTLFT_ESC_RELOAD_CC_SHIFT                (0u)
#define FRNTLFT_ESC_RELOAD_PERIOD_SHIFT            (1u)
#define FRNTLFT_ESC_PWM_SYNC_KILL_SHIFT            (2u)
#define FRNTLFT_ESC_PWM_STOP_KILL_SHIFT            (3u)
#define FRNTLFT_ESC_PRESCALER_SHIFT                (8u)
#define FRNTLFT_ESC_UPDOWN_SHIFT                   (16u)
#define FRNTLFT_ESC_ONESHOT_SHIFT                  (18u)
#define FRNTLFT_ESC_QUAD_MODE_SHIFT                (20u)
#define FRNTLFT_ESC_INV_OUT_SHIFT                  (20u)
#define FRNTLFT_ESC_INV_COMPL_OUT_SHIFT            (21u)
#define FRNTLFT_ESC_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define FRNTLFT_ESC_RELOAD_CC_MASK                 ((uint32)(FRNTLFT_ESC_1BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_RELOAD_CC_SHIFT))
#define FRNTLFT_ESC_RELOAD_PERIOD_MASK             ((uint32)(FRNTLFT_ESC_1BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_RELOAD_PERIOD_SHIFT))
#define FRNTLFT_ESC_PWM_SYNC_KILL_MASK             ((uint32)(FRNTLFT_ESC_1BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_PWM_SYNC_KILL_SHIFT))
#define FRNTLFT_ESC_PWM_STOP_KILL_MASK             ((uint32)(FRNTLFT_ESC_1BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_PWM_STOP_KILL_SHIFT))
#define FRNTLFT_ESC_PRESCALER_MASK                 ((uint32)(FRNTLFT_ESC_8BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_PRESCALER_SHIFT))
#define FRNTLFT_ESC_UPDOWN_MASK                    ((uint32)(FRNTLFT_ESC_2BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_UPDOWN_SHIFT))
#define FRNTLFT_ESC_ONESHOT_MASK                   ((uint32)(FRNTLFT_ESC_1BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_ONESHOT_SHIFT))
#define FRNTLFT_ESC_QUAD_MODE_MASK                 ((uint32)(FRNTLFT_ESC_3BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_QUAD_MODE_SHIFT))
#define FRNTLFT_ESC_INV_OUT_MASK                   ((uint32)(FRNTLFT_ESC_2BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_INV_OUT_SHIFT))
#define FRNTLFT_ESC_MODE_MASK                      ((uint32)(FRNTLFT_ESC_3BIT_MASK        <<  \
                                                                            FRNTLFT_ESC_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define FRNTLFT_ESC_CAPTURE_SHIFT                  (0u)
#define FRNTLFT_ESC_COUNT_SHIFT                    (2u)
#define FRNTLFT_ESC_RELOAD_SHIFT                   (4u)
#define FRNTLFT_ESC_STOP_SHIFT                     (6u)
#define FRNTLFT_ESC_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define FRNTLFT_ESC_CAPTURE_MASK                   ((uint32)(FRNTLFT_ESC_2BIT_MASK        <<  \
                                                                  FRNTLFT_ESC_CAPTURE_SHIFT))
#define FRNTLFT_ESC_COUNT_MASK                     ((uint32)(FRNTLFT_ESC_2BIT_MASK        <<  \
                                                                  FRNTLFT_ESC_COUNT_SHIFT))
#define FRNTLFT_ESC_RELOAD_MASK                    ((uint32)(FRNTLFT_ESC_2BIT_MASK        <<  \
                                                                  FRNTLFT_ESC_RELOAD_SHIFT))
#define FRNTLFT_ESC_STOP_MASK                      ((uint32)(FRNTLFT_ESC_2BIT_MASK        <<  \
                                                                  FRNTLFT_ESC_STOP_SHIFT))
#define FRNTLFT_ESC_START_MASK                     ((uint32)(FRNTLFT_ESC_2BIT_MASK        <<  \
                                                                  FRNTLFT_ESC_START_SHIFT))

/* MASK */
#define FRNTLFT_ESC_1BIT_MASK                      ((uint32)0x01u)
#define FRNTLFT_ESC_2BIT_MASK                      ((uint32)0x03u)
#define FRNTLFT_ESC_3BIT_MASK                      ((uint32)0x07u)
#define FRNTLFT_ESC_6BIT_MASK                      ((uint32)0x3Fu)
#define FRNTLFT_ESC_8BIT_MASK                      ((uint32)0xFFu)
#define FRNTLFT_ESC_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define FRNTLFT_ESC_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define FRNTLFT_ESC_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(FRNTLFT_ESC_QUAD_ENCODING_MODES     << FRNTLFT_ESC_QUAD_MODE_SHIFT))       |\
         ((uint32)(FRNTLFT_ESC_CONFIG                  << FRNTLFT_ESC_MODE_SHIFT)))

#define FRNTLFT_ESC_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(FRNTLFT_ESC_PWM_STOP_EVENT          << FRNTLFT_ESC_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(FRNTLFT_ESC_PWM_OUT_INVERT          << FRNTLFT_ESC_INV_OUT_SHIFT))         |\
         ((uint32)(FRNTLFT_ESC_PWM_OUT_N_INVERT        << FRNTLFT_ESC_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(FRNTLFT_ESC_PWM_MODE                << FRNTLFT_ESC_MODE_SHIFT)))

#define FRNTLFT_ESC_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(FRNTLFT_ESC_PWM_RUN_MODE         << FRNTLFT_ESC_ONESHOT_SHIFT))
            
#define FRNTLFT_ESC_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(FRNTLFT_ESC_PWM_ALIGN            << FRNTLFT_ESC_UPDOWN_SHIFT))

#define FRNTLFT_ESC_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(FRNTLFT_ESC_PWM_KILL_EVENT      << FRNTLFT_ESC_PWM_SYNC_KILL_SHIFT))

#define FRNTLFT_ESC_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(FRNTLFT_ESC_PWM_DEAD_TIME_CYCLE  << FRNTLFT_ESC_PRESCALER_SHIFT))

#define FRNTLFT_ESC_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(FRNTLFT_ESC_PWM_PRESCALER        << FRNTLFT_ESC_PRESCALER_SHIFT))

#define FRNTLFT_ESC_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(FRNTLFT_ESC_TC_PRESCALER            << FRNTLFT_ESC_PRESCALER_SHIFT))       |\
         ((uint32)(FRNTLFT_ESC_TC_COUNTER_MODE         << FRNTLFT_ESC_UPDOWN_SHIFT))          |\
         ((uint32)(FRNTLFT_ESC_TC_RUN_MODE             << FRNTLFT_ESC_ONESHOT_SHIFT))         |\
         ((uint32)(FRNTLFT_ESC_TC_COMP_CAP_MODE        << FRNTLFT_ESC_MODE_SHIFT)))
        
#define FRNTLFT_ESC_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(FRNTLFT_ESC_QUAD_PHIA_SIGNAL_MODE   << FRNTLFT_ESC_COUNT_SHIFT))           |\
         ((uint32)(FRNTLFT_ESC_QUAD_INDEX_SIGNAL_MODE  << FRNTLFT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(FRNTLFT_ESC_QUAD_STOP_SIGNAL_MODE   << FRNTLFT_ESC_STOP_SHIFT))            |\
         ((uint32)(FRNTLFT_ESC_QUAD_PHIB_SIGNAL_MODE   << FRNTLFT_ESC_START_SHIFT)))

#define FRNTLFT_ESC_PWM_SIGNALS_MODES                                                              \
        (((uint32)(FRNTLFT_ESC_PWM_SWITCH_SIGNAL_MODE  << FRNTLFT_ESC_CAPTURE_SHIFT))         |\
         ((uint32)(FRNTLFT_ESC_PWM_COUNT_SIGNAL_MODE   << FRNTLFT_ESC_COUNT_SHIFT))           |\
         ((uint32)(FRNTLFT_ESC_PWM_RELOAD_SIGNAL_MODE  << FRNTLFT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(FRNTLFT_ESC_PWM_STOP_SIGNAL_MODE    << FRNTLFT_ESC_STOP_SHIFT))            |\
         ((uint32)(FRNTLFT_ESC_PWM_START_SIGNAL_MODE   << FRNTLFT_ESC_START_SHIFT)))

#define FRNTLFT_ESC_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(FRNTLFT_ESC_TC_CAPTURE_SIGNAL_MODE  << FRNTLFT_ESC_CAPTURE_SHIFT))         |\
         ((uint32)(FRNTLFT_ESC_TC_COUNT_SIGNAL_MODE    << FRNTLFT_ESC_COUNT_SHIFT))           |\
         ((uint32)(FRNTLFT_ESC_TC_RELOAD_SIGNAL_MODE   << FRNTLFT_ESC_RELOAD_SHIFT))          |\
         ((uint32)(FRNTLFT_ESC_TC_STOP_SIGNAL_MODE     << FRNTLFT_ESC_STOP_SHIFT))            |\
         ((uint32)(FRNTLFT_ESC_TC_START_SIGNAL_MODE    << FRNTLFT_ESC_START_SHIFT)))
        
#define FRNTLFT_ESC_TIMER_UPDOWN_CNT_USED                                                          \
                ((FRNTLFT_ESC__COUNT_UPDOWN0 == FRNTLFT_ESC_TC_COUNTER_MODE)                  ||\
                 (FRNTLFT_ESC__COUNT_UPDOWN1 == FRNTLFT_ESC_TC_COUNTER_MODE))

#define FRNTLFT_ESC_PWM_UPDOWN_CNT_USED                                                            \
                ((FRNTLFT_ESC__CENTER == FRNTLFT_ESC_PWM_ALIGN)                               ||\
                 (FRNTLFT_ESC__ASYMMETRIC == FRNTLFT_ESC_PWM_ALIGN))               
        
#define FRNTLFT_ESC_PWM_PR_INIT_VALUE              (1u)
#define FRNTLFT_ESC_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_FRNTLFT_ESC_H */

/* [] END OF FILE */
