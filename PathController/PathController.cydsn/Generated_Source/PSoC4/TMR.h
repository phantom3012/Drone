/*******************************************************************************
* File Name: TMR.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the TMR
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

#if !defined(CY_TCPWM_TMR_H)
#define CY_TCPWM_TMR_H


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
} TMR_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  TMR_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define TMR_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define TMR_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define TMR_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define TMR_QUAD_ENCODING_MODES            (0lu)
#define TMR_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define TMR_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define TMR_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define TMR_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define TMR_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define TMR_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define TMR_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define TMR_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define TMR_TC_RUN_MODE                    (0lu)
#define TMR_TC_COUNTER_MODE                (0lu)
#define TMR_TC_COMP_CAP_MODE               (2lu)
#define TMR_TC_PRESCALER                   (0lu)

/* Signal modes */
#define TMR_TC_RELOAD_SIGNAL_MODE          (0lu)
#define TMR_TC_COUNT_SIGNAL_MODE           (3lu)
#define TMR_TC_START_SIGNAL_MODE           (0lu)
#define TMR_TC_STOP_SIGNAL_MODE            (0lu)
#define TMR_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define TMR_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define TMR_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define TMR_TC_START_SIGNAL_PRESENT        (0lu)
#define TMR_TC_STOP_SIGNAL_PRESENT         (0lu)
#define TMR_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TMR_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define TMR_PWM_KILL_EVENT                 (0lu)
#define TMR_PWM_STOP_EVENT                 (0lu)
#define TMR_PWM_MODE                       (4lu)
#define TMR_PWM_OUT_N_INVERT               (0lu)
#define TMR_PWM_OUT_INVERT                 (0lu)
#define TMR_PWM_ALIGN                      (0lu)
#define TMR_PWM_RUN_MODE                   (0lu)
#define TMR_PWM_DEAD_TIME_CYCLE            (0lu)
#define TMR_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define TMR_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define TMR_PWM_COUNT_SIGNAL_MODE          (3lu)
#define TMR_PWM_START_SIGNAL_MODE          (0lu)
#define TMR_PWM_STOP_SIGNAL_MODE           (0lu)
#define TMR_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define TMR_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define TMR_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define TMR_PWM_START_SIGNAL_PRESENT       (0lu)
#define TMR_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define TMR_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TMR_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define TMR_TC_PERIOD_VALUE                (65535lu)
#define TMR_TC_COMPARE_VALUE               (65535lu)
#define TMR_TC_COMPARE_BUF_VALUE           (65535lu)
#define TMR_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define TMR_PWM_PERIOD_VALUE               (65535lu)
#define TMR_PWM_PERIOD_BUF_VALUE           (65535lu)
#define TMR_PWM_PERIOD_SWAP                (0lu)
#define TMR_PWM_COMPARE_VALUE              (65535lu)
#define TMR_PWM_COMPARE_BUF_VALUE          (65535lu)
#define TMR_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define TMR__LEFT 0
#define TMR__RIGHT 1
#define TMR__CENTER 2
#define TMR__ASYMMETRIC 3

#define TMR__X1 0
#define TMR__X2 1
#define TMR__X4 2

#define TMR__PWM 4
#define TMR__PWM_DT 5
#define TMR__PWM_PR 6

#define TMR__INVERSE 1
#define TMR__DIRECT 0

#define TMR__CAPTURE 2
#define TMR__COMPARE 0

#define TMR__TRIG_LEVEL 3
#define TMR__TRIG_RISING 0
#define TMR__TRIG_FALLING 1
#define TMR__TRIG_BOTH 2

#define TMR__INTR_MASK_TC 1
#define TMR__INTR_MASK_CC_MATCH 2
#define TMR__INTR_MASK_NONE 0
#define TMR__INTR_MASK_TC_CC 3

#define TMR__UNCONFIG 8
#define TMR__TIMER 1
#define TMR__QUAD 3
#define TMR__PWM_SEL 7

#define TMR__COUNT_UP 0
#define TMR__COUNT_DOWN 1
#define TMR__COUNT_UPDOWN0 2
#define TMR__COUNT_UPDOWN1 3


/* Prescaler */
#define TMR_PRESCALE_DIVBY1                ((uint32)(0u << TMR_PRESCALER_SHIFT))
#define TMR_PRESCALE_DIVBY2                ((uint32)(1u << TMR_PRESCALER_SHIFT))
#define TMR_PRESCALE_DIVBY4                ((uint32)(2u << TMR_PRESCALER_SHIFT))
#define TMR_PRESCALE_DIVBY8                ((uint32)(3u << TMR_PRESCALER_SHIFT))
#define TMR_PRESCALE_DIVBY16               ((uint32)(4u << TMR_PRESCALER_SHIFT))
#define TMR_PRESCALE_DIVBY32               ((uint32)(5u << TMR_PRESCALER_SHIFT))
#define TMR_PRESCALE_DIVBY64               ((uint32)(6u << TMR_PRESCALER_SHIFT))
#define TMR_PRESCALE_DIVBY128              ((uint32)(7u << TMR_PRESCALER_SHIFT))

/* TCPWM set modes */
#define TMR_MODE_TIMER_COMPARE             ((uint32)(TMR__COMPARE         <<  \
                                                                  TMR_MODE_SHIFT))
#define TMR_MODE_TIMER_CAPTURE             ((uint32)(TMR__CAPTURE         <<  \
                                                                  TMR_MODE_SHIFT))
#define TMR_MODE_QUAD                      ((uint32)(TMR__QUAD            <<  \
                                                                  TMR_MODE_SHIFT))
#define TMR_MODE_PWM                       ((uint32)(TMR__PWM             <<  \
                                                                  TMR_MODE_SHIFT))
#define TMR_MODE_PWM_DT                    ((uint32)(TMR__PWM_DT          <<  \
                                                                  TMR_MODE_SHIFT))
#define TMR_MODE_PWM_PR                    ((uint32)(TMR__PWM_PR          <<  \
                                                                  TMR_MODE_SHIFT))

/* Quad Modes */
#define TMR_MODE_X1                        ((uint32)(TMR__X1              <<  \
                                                                  TMR_QUAD_MODE_SHIFT))
#define TMR_MODE_X2                        ((uint32)(TMR__X2              <<  \
                                                                  TMR_QUAD_MODE_SHIFT))
#define TMR_MODE_X4                        ((uint32)(TMR__X4              <<  \
                                                                  TMR_QUAD_MODE_SHIFT))

/* Counter modes */
#define TMR_COUNT_UP                       ((uint32)(TMR__COUNT_UP        <<  \
                                                                  TMR_UPDOWN_SHIFT))
#define TMR_COUNT_DOWN                     ((uint32)(TMR__COUNT_DOWN      <<  \
                                                                  TMR_UPDOWN_SHIFT))
#define TMR_COUNT_UPDOWN0                  ((uint32)(TMR__COUNT_UPDOWN0   <<  \
                                                                  TMR_UPDOWN_SHIFT))
#define TMR_COUNT_UPDOWN1                  ((uint32)(TMR__COUNT_UPDOWN1   <<  \
                                                                  TMR_UPDOWN_SHIFT))

/* PWM output invert */
#define TMR_INVERT_LINE                    ((uint32)(TMR__INVERSE         <<  \
                                                                  TMR_INV_OUT_SHIFT))
#define TMR_INVERT_LINE_N                  ((uint32)(TMR__INVERSE         <<  \
                                                                  TMR_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define TMR_TRIG_RISING                    ((uint32)TMR__TRIG_RISING)
#define TMR_TRIG_FALLING                   ((uint32)TMR__TRIG_FALLING)
#define TMR_TRIG_BOTH                      ((uint32)TMR__TRIG_BOTH)
#define TMR_TRIG_LEVEL                     ((uint32)TMR__TRIG_LEVEL)

/* Interrupt mask */
#define TMR_INTR_MASK_TC                   ((uint32)TMR__INTR_MASK_TC)
#define TMR_INTR_MASK_CC_MATCH             ((uint32)TMR__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define TMR_CC_MATCH_SET                   (0x00u)
#define TMR_CC_MATCH_CLEAR                 (0x01u)
#define TMR_CC_MATCH_INVERT                (0x02u)
#define TMR_CC_MATCH_NO_CHANGE             (0x03u)
#define TMR_OVERLOW_SET                    (0x00u)
#define TMR_OVERLOW_CLEAR                  (0x04u)
#define TMR_OVERLOW_INVERT                 (0x08u)
#define TMR_OVERLOW_NO_CHANGE              (0x0Cu)
#define TMR_UNDERFLOW_SET                  (0x00u)
#define TMR_UNDERFLOW_CLEAR                (0x10u)
#define TMR_UNDERFLOW_INVERT               (0x20u)
#define TMR_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define TMR_PWM_MODE_LEFT                  (TMR_CC_MATCH_CLEAR        |   \
                                                         TMR_OVERLOW_SET           |   \
                                                         TMR_UNDERFLOW_NO_CHANGE)
#define TMR_PWM_MODE_RIGHT                 (TMR_CC_MATCH_SET          |   \
                                                         TMR_OVERLOW_NO_CHANGE     |   \
                                                         TMR_UNDERFLOW_CLEAR)
#define TMR_PWM_MODE_ASYM                  (TMR_CC_MATCH_INVERT       |   \
                                                         TMR_OVERLOW_SET           |   \
                                                         TMR_UNDERFLOW_CLEAR)

#if (TMR_CY_TCPWM_V2)
    #if(TMR_CY_TCPWM_4000)
        #define TMR_PWM_MODE_CENTER                (TMR_CC_MATCH_INVERT       |   \
                                                                 TMR_OVERLOW_NO_CHANGE     |   \
                                                                 TMR_UNDERFLOW_CLEAR)
    #else
        #define TMR_PWM_MODE_CENTER                (TMR_CC_MATCH_INVERT       |   \
                                                                 TMR_OVERLOW_SET           |   \
                                                                 TMR_UNDERFLOW_CLEAR)
    #endif /* (TMR_CY_TCPWM_4000) */
#else
    #define TMR_PWM_MODE_CENTER                (TMR_CC_MATCH_INVERT       |   \
                                                             TMR_OVERLOW_NO_CHANGE     |   \
                                                             TMR_UNDERFLOW_CLEAR)
#endif /* (TMR_CY_TCPWM_NEW) */

/* Command operations without condition */
#define TMR_CMD_CAPTURE                    (0u)
#define TMR_CMD_RELOAD                     (8u)
#define TMR_CMD_STOP                       (16u)
#define TMR_CMD_START                      (24u)

/* Status */
#define TMR_STATUS_DOWN                    (1u)
#define TMR_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   TMR_Init(void);
void   TMR_Enable(void);
void   TMR_Start(void);
void   TMR_Stop(void);

void   TMR_SetMode(uint32 mode);
void   TMR_SetCounterMode(uint32 counterMode);
void   TMR_SetPWMMode(uint32 modeMask);
void   TMR_SetQDMode(uint32 qdMode);

void   TMR_SetPrescaler(uint32 prescaler);
void   TMR_TriggerCommand(uint32 mask, uint32 command);
void   TMR_SetOneShot(uint32 oneShotEnable);
uint32 TMR_ReadStatus(void);

void   TMR_SetPWMSyncKill(uint32 syncKillEnable);
void   TMR_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   TMR_SetPWMDeadTime(uint32 deadTime);
void   TMR_SetPWMInvert(uint32 mask);

void   TMR_SetInterruptMode(uint32 interruptMask);
uint32 TMR_GetInterruptSourceMasked(void);
uint32 TMR_GetInterruptSource(void);
void   TMR_ClearInterrupt(uint32 interruptMask);
void   TMR_SetInterrupt(uint32 interruptMask);

void   TMR_WriteCounter(uint32 count);
uint32 TMR_ReadCounter(void);

uint32 TMR_ReadCapture(void);
uint32 TMR_ReadCaptureBuf(void);

void   TMR_WritePeriod(uint32 period);
uint32 TMR_ReadPeriod(void);
void   TMR_WritePeriodBuf(uint32 periodBuf);
uint32 TMR_ReadPeriodBuf(void);

void   TMR_WriteCompare(uint32 compare);
uint32 TMR_ReadCompare(void);
void   TMR_WriteCompareBuf(uint32 compareBuf);
uint32 TMR_ReadCompareBuf(void);

void   TMR_SetPeriodSwap(uint32 swapEnable);
void   TMR_SetCompareSwap(uint32 swapEnable);

void   TMR_SetCaptureMode(uint32 triggerMode);
void   TMR_SetReloadMode(uint32 triggerMode);
void   TMR_SetStartMode(uint32 triggerMode);
void   TMR_SetStopMode(uint32 triggerMode);
void   TMR_SetCountMode(uint32 triggerMode);

void   TMR_SaveConfig(void);
void   TMR_RestoreConfig(void);
void   TMR_Sleep(void);
void   TMR_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define TMR_BLOCK_CONTROL_REG              (*(reg32 *) TMR_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TMR_BLOCK_CONTROL_PTR              ( (reg32 *) TMR_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TMR_COMMAND_REG                    (*(reg32 *) TMR_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TMR_COMMAND_PTR                    ( (reg32 *) TMR_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TMR_INTRRUPT_CAUSE_REG             (*(reg32 *) TMR_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TMR_INTRRUPT_CAUSE_PTR             ( (reg32 *) TMR_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TMR_CONTROL_REG                    (*(reg32 *) TMR_cy_m0s8_tcpwm_1__CTRL )
#define TMR_CONTROL_PTR                    ( (reg32 *) TMR_cy_m0s8_tcpwm_1__CTRL )
#define TMR_STATUS_REG                     (*(reg32 *) TMR_cy_m0s8_tcpwm_1__STATUS )
#define TMR_STATUS_PTR                     ( (reg32 *) TMR_cy_m0s8_tcpwm_1__STATUS )
#define TMR_COUNTER_REG                    (*(reg32 *) TMR_cy_m0s8_tcpwm_1__COUNTER )
#define TMR_COUNTER_PTR                    ( (reg32 *) TMR_cy_m0s8_tcpwm_1__COUNTER )
#define TMR_COMP_CAP_REG                   (*(reg32 *) TMR_cy_m0s8_tcpwm_1__CC )
#define TMR_COMP_CAP_PTR                   ( (reg32 *) TMR_cy_m0s8_tcpwm_1__CC )
#define TMR_COMP_CAP_BUF_REG               (*(reg32 *) TMR_cy_m0s8_tcpwm_1__CC_BUFF )
#define TMR_COMP_CAP_BUF_PTR               ( (reg32 *) TMR_cy_m0s8_tcpwm_1__CC_BUFF )
#define TMR_PERIOD_REG                     (*(reg32 *) TMR_cy_m0s8_tcpwm_1__PERIOD )
#define TMR_PERIOD_PTR                     ( (reg32 *) TMR_cy_m0s8_tcpwm_1__PERIOD )
#define TMR_PERIOD_BUF_REG                 (*(reg32 *) TMR_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TMR_PERIOD_BUF_PTR                 ( (reg32 *) TMR_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TMR_TRIG_CONTROL0_REG              (*(reg32 *) TMR_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TMR_TRIG_CONTROL0_PTR              ( (reg32 *) TMR_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TMR_TRIG_CONTROL1_REG              (*(reg32 *) TMR_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TMR_TRIG_CONTROL1_PTR              ( (reg32 *) TMR_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TMR_TRIG_CONTROL2_REG              (*(reg32 *) TMR_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TMR_TRIG_CONTROL2_PTR              ( (reg32 *) TMR_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TMR_INTERRUPT_REQ_REG              (*(reg32 *) TMR_cy_m0s8_tcpwm_1__INTR )
#define TMR_INTERRUPT_REQ_PTR              ( (reg32 *) TMR_cy_m0s8_tcpwm_1__INTR )
#define TMR_INTERRUPT_SET_REG              (*(reg32 *) TMR_cy_m0s8_tcpwm_1__INTR_SET )
#define TMR_INTERRUPT_SET_PTR              ( (reg32 *) TMR_cy_m0s8_tcpwm_1__INTR_SET )
#define TMR_INTERRUPT_MASK_REG             (*(reg32 *) TMR_cy_m0s8_tcpwm_1__INTR_MASK )
#define TMR_INTERRUPT_MASK_PTR             ( (reg32 *) TMR_cy_m0s8_tcpwm_1__INTR_MASK )
#define TMR_INTERRUPT_MASKED_REG           (*(reg32 *) TMR_cy_m0s8_tcpwm_1__INTR_MASKED )
#define TMR_INTERRUPT_MASKED_PTR           ( (reg32 *) TMR_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define TMR_MASK                           ((uint32)TMR_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define TMR_RELOAD_CC_SHIFT                (0u)
#define TMR_RELOAD_PERIOD_SHIFT            (1u)
#define TMR_PWM_SYNC_KILL_SHIFT            (2u)
#define TMR_PWM_STOP_KILL_SHIFT            (3u)
#define TMR_PRESCALER_SHIFT                (8u)
#define TMR_UPDOWN_SHIFT                   (16u)
#define TMR_ONESHOT_SHIFT                  (18u)
#define TMR_QUAD_MODE_SHIFT                (20u)
#define TMR_INV_OUT_SHIFT                  (20u)
#define TMR_INV_COMPL_OUT_SHIFT            (21u)
#define TMR_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define TMR_RELOAD_CC_MASK                 ((uint32)(TMR_1BIT_MASK        <<  \
                                                                            TMR_RELOAD_CC_SHIFT))
#define TMR_RELOAD_PERIOD_MASK             ((uint32)(TMR_1BIT_MASK        <<  \
                                                                            TMR_RELOAD_PERIOD_SHIFT))
#define TMR_PWM_SYNC_KILL_MASK             ((uint32)(TMR_1BIT_MASK        <<  \
                                                                            TMR_PWM_SYNC_KILL_SHIFT))
#define TMR_PWM_STOP_KILL_MASK             ((uint32)(TMR_1BIT_MASK        <<  \
                                                                            TMR_PWM_STOP_KILL_SHIFT))
#define TMR_PRESCALER_MASK                 ((uint32)(TMR_8BIT_MASK        <<  \
                                                                            TMR_PRESCALER_SHIFT))
#define TMR_UPDOWN_MASK                    ((uint32)(TMR_2BIT_MASK        <<  \
                                                                            TMR_UPDOWN_SHIFT))
#define TMR_ONESHOT_MASK                   ((uint32)(TMR_1BIT_MASK        <<  \
                                                                            TMR_ONESHOT_SHIFT))
#define TMR_QUAD_MODE_MASK                 ((uint32)(TMR_3BIT_MASK        <<  \
                                                                            TMR_QUAD_MODE_SHIFT))
#define TMR_INV_OUT_MASK                   ((uint32)(TMR_2BIT_MASK        <<  \
                                                                            TMR_INV_OUT_SHIFT))
#define TMR_MODE_MASK                      ((uint32)(TMR_3BIT_MASK        <<  \
                                                                            TMR_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define TMR_CAPTURE_SHIFT                  (0u)
#define TMR_COUNT_SHIFT                    (2u)
#define TMR_RELOAD_SHIFT                   (4u)
#define TMR_STOP_SHIFT                     (6u)
#define TMR_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define TMR_CAPTURE_MASK                   ((uint32)(TMR_2BIT_MASK        <<  \
                                                                  TMR_CAPTURE_SHIFT))
#define TMR_COUNT_MASK                     ((uint32)(TMR_2BIT_MASK        <<  \
                                                                  TMR_COUNT_SHIFT))
#define TMR_RELOAD_MASK                    ((uint32)(TMR_2BIT_MASK        <<  \
                                                                  TMR_RELOAD_SHIFT))
#define TMR_STOP_MASK                      ((uint32)(TMR_2BIT_MASK        <<  \
                                                                  TMR_STOP_SHIFT))
#define TMR_START_MASK                     ((uint32)(TMR_2BIT_MASK        <<  \
                                                                  TMR_START_SHIFT))

/* MASK */
#define TMR_1BIT_MASK                      ((uint32)0x01u)
#define TMR_2BIT_MASK                      ((uint32)0x03u)
#define TMR_3BIT_MASK                      ((uint32)0x07u)
#define TMR_6BIT_MASK                      ((uint32)0x3Fu)
#define TMR_8BIT_MASK                      ((uint32)0xFFu)
#define TMR_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define TMR_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define TMR_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(TMR_QUAD_ENCODING_MODES     << TMR_QUAD_MODE_SHIFT))       |\
         ((uint32)(TMR_CONFIG                  << TMR_MODE_SHIFT)))

#define TMR_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(TMR_PWM_STOP_EVENT          << TMR_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(TMR_PWM_OUT_INVERT          << TMR_INV_OUT_SHIFT))         |\
         ((uint32)(TMR_PWM_OUT_N_INVERT        << TMR_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(TMR_PWM_MODE                << TMR_MODE_SHIFT)))

#define TMR_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(TMR_PWM_RUN_MODE         << TMR_ONESHOT_SHIFT))
            
#define TMR_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(TMR_PWM_ALIGN            << TMR_UPDOWN_SHIFT))

#define TMR_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(TMR_PWM_KILL_EVENT      << TMR_PWM_SYNC_KILL_SHIFT))

#define TMR_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(TMR_PWM_DEAD_TIME_CYCLE  << TMR_PRESCALER_SHIFT))

#define TMR_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(TMR_PWM_PRESCALER        << TMR_PRESCALER_SHIFT))

#define TMR_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(TMR_TC_PRESCALER            << TMR_PRESCALER_SHIFT))       |\
         ((uint32)(TMR_TC_COUNTER_MODE         << TMR_UPDOWN_SHIFT))          |\
         ((uint32)(TMR_TC_RUN_MODE             << TMR_ONESHOT_SHIFT))         |\
         ((uint32)(TMR_TC_COMP_CAP_MODE        << TMR_MODE_SHIFT)))
        
#define TMR_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(TMR_QUAD_PHIA_SIGNAL_MODE   << TMR_COUNT_SHIFT))           |\
         ((uint32)(TMR_QUAD_INDEX_SIGNAL_MODE  << TMR_RELOAD_SHIFT))          |\
         ((uint32)(TMR_QUAD_STOP_SIGNAL_MODE   << TMR_STOP_SHIFT))            |\
         ((uint32)(TMR_QUAD_PHIB_SIGNAL_MODE   << TMR_START_SHIFT)))

#define TMR_PWM_SIGNALS_MODES                                                              \
        (((uint32)(TMR_PWM_SWITCH_SIGNAL_MODE  << TMR_CAPTURE_SHIFT))         |\
         ((uint32)(TMR_PWM_COUNT_SIGNAL_MODE   << TMR_COUNT_SHIFT))           |\
         ((uint32)(TMR_PWM_RELOAD_SIGNAL_MODE  << TMR_RELOAD_SHIFT))          |\
         ((uint32)(TMR_PWM_STOP_SIGNAL_MODE    << TMR_STOP_SHIFT))            |\
         ((uint32)(TMR_PWM_START_SIGNAL_MODE   << TMR_START_SHIFT)))

#define TMR_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(TMR_TC_CAPTURE_SIGNAL_MODE  << TMR_CAPTURE_SHIFT))         |\
         ((uint32)(TMR_TC_COUNT_SIGNAL_MODE    << TMR_COUNT_SHIFT))           |\
         ((uint32)(TMR_TC_RELOAD_SIGNAL_MODE   << TMR_RELOAD_SHIFT))          |\
         ((uint32)(TMR_TC_STOP_SIGNAL_MODE     << TMR_STOP_SHIFT))            |\
         ((uint32)(TMR_TC_START_SIGNAL_MODE    << TMR_START_SHIFT)))
        
#define TMR_TIMER_UPDOWN_CNT_USED                                                          \
                ((TMR__COUNT_UPDOWN0 == TMR_TC_COUNTER_MODE)                  ||\
                 (TMR__COUNT_UPDOWN1 == TMR_TC_COUNTER_MODE))

#define TMR_PWM_UPDOWN_CNT_USED                                                            \
                ((TMR__CENTER == TMR_PWM_ALIGN)                               ||\
                 (TMR__ASYMMETRIC == TMR_PWM_ALIGN))               
        
#define TMR_PWM_PR_INIT_VALUE              (1u)
#define TMR_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_TMR_H */

/* [] END OF FILE */
