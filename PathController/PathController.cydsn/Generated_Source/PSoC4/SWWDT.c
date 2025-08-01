/*******************************************************************************
* File Name: SWWDT.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the SWWDT
*  component
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

#include "SWWDT.h"

uint8 SWWDT_initVar = 0u;


/*******************************************************************************
* Function Name: SWWDT_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default SWWDT configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (SWWDT__QUAD == SWWDT_CONFIG)
        SWWDT_CONTROL_REG = SWWDT_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SWWDT_TRIG_CONTROL1_REG  = SWWDT_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        SWWDT_SetInterruptMode(SWWDT_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        SWWDT_SetCounterMode(SWWDT_COUNT_DOWN);
        SWWDT_WritePeriod(SWWDT_QUAD_PERIOD_INIT_VALUE);
        SWWDT_WriteCounter(SWWDT_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (SWWDT__QUAD == SWWDT_CONFIG) */

    #if (SWWDT__TIMER == SWWDT_CONFIG)
        SWWDT_CONTROL_REG = SWWDT_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SWWDT_TRIG_CONTROL1_REG  = SWWDT_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SWWDT_SetInterruptMode(SWWDT_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        SWWDT_WritePeriod(SWWDT_TC_PERIOD_VALUE );

        #if (SWWDT__COMPARE == SWWDT_TC_COMP_CAP_MODE)
            SWWDT_WriteCompare(SWWDT_TC_COMPARE_VALUE);

            #if (1u == SWWDT_TC_COMPARE_SWAP)
                SWWDT_SetCompareSwap(1u);
                SWWDT_WriteCompareBuf(SWWDT_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == SWWDT_TC_COMPARE_SWAP) */
        #endif  /* (SWWDT__COMPARE == SWWDT_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (SWWDT_CY_TCPWM_V2 && SWWDT_TIMER_UPDOWN_CNT_USED && !SWWDT_CY_TCPWM_4000)
            SWWDT_WriteCounter(1u);
        #elif(SWWDT__COUNT_DOWN == SWWDT_TC_COUNTER_MODE)
            SWWDT_WriteCounter(SWWDT_TC_PERIOD_VALUE);
        #else
            SWWDT_WriteCounter(0u);
        #endif /* (SWWDT_CY_TCPWM_V2 && SWWDT_TIMER_UPDOWN_CNT_USED && !SWWDT_CY_TCPWM_4000) */
    #endif  /* (SWWDT__TIMER == SWWDT_CONFIG) */

    #if (SWWDT__PWM_SEL == SWWDT_CONFIG)
        SWWDT_CONTROL_REG = SWWDT_CTRL_PWM_BASE_CONFIG;

        #if (SWWDT__PWM_PR == SWWDT_PWM_MODE)
            SWWDT_CONTROL_REG |= SWWDT_CTRL_PWM_RUN_MODE;
            SWWDT_WriteCounter(SWWDT_PWM_PR_INIT_VALUE);
        #else
            SWWDT_CONTROL_REG |= SWWDT_CTRL_PWM_ALIGN | SWWDT_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (SWWDT_CY_TCPWM_V2 && SWWDT_PWM_UPDOWN_CNT_USED && !SWWDT_CY_TCPWM_4000)
                SWWDT_WriteCounter(1u);
            #elif (SWWDT__RIGHT == SWWDT_PWM_ALIGN)
                SWWDT_WriteCounter(SWWDT_PWM_PERIOD_VALUE);
            #else 
                SWWDT_WriteCounter(0u);
            #endif  /* (SWWDT_CY_TCPWM_V2 && SWWDT_PWM_UPDOWN_CNT_USED && !SWWDT_CY_TCPWM_4000) */
        #endif  /* (SWWDT__PWM_PR == SWWDT_PWM_MODE) */

        #if (SWWDT__PWM_DT == SWWDT_PWM_MODE)
            SWWDT_CONTROL_REG |= SWWDT_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (SWWDT__PWM_DT == SWWDT_PWM_MODE) */

        #if (SWWDT__PWM == SWWDT_PWM_MODE)
            SWWDT_CONTROL_REG |= SWWDT_CTRL_PWM_PRESCALER;
        #endif  /* (SWWDT__PWM == SWWDT_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        SWWDT_TRIG_CONTROL1_REG  = SWWDT_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SWWDT_SetInterruptMode(SWWDT_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (SWWDT__PWM_PR == SWWDT_PWM_MODE)
            SWWDT_TRIG_CONTROL2_REG =
                    (SWWDT_CC_MATCH_NO_CHANGE    |
                    SWWDT_OVERLOW_NO_CHANGE      |
                    SWWDT_UNDERFLOW_NO_CHANGE);
        #else
            #if (SWWDT__LEFT == SWWDT_PWM_ALIGN)
                SWWDT_TRIG_CONTROL2_REG = SWWDT_PWM_MODE_LEFT;
            #endif  /* ( SWWDT_PWM_LEFT == SWWDT_PWM_ALIGN) */

            #if (SWWDT__RIGHT == SWWDT_PWM_ALIGN)
                SWWDT_TRIG_CONTROL2_REG = SWWDT_PWM_MODE_RIGHT;
            #endif  /* ( SWWDT_PWM_RIGHT == SWWDT_PWM_ALIGN) */

            #if (SWWDT__CENTER == SWWDT_PWM_ALIGN)
                SWWDT_TRIG_CONTROL2_REG = SWWDT_PWM_MODE_CENTER;
            #endif  /* ( SWWDT_PWM_CENTER == SWWDT_PWM_ALIGN) */

            #if (SWWDT__ASYMMETRIC == SWWDT_PWM_ALIGN)
                SWWDT_TRIG_CONTROL2_REG = SWWDT_PWM_MODE_ASYM;
            #endif  /* (SWWDT__ASYMMETRIC == SWWDT_PWM_ALIGN) */
        #endif  /* (SWWDT__PWM_PR == SWWDT_PWM_MODE) */

        /* Set other values from customizer */
        SWWDT_WritePeriod(SWWDT_PWM_PERIOD_VALUE );
        SWWDT_WriteCompare(SWWDT_PWM_COMPARE_VALUE);

        #if (1u == SWWDT_PWM_COMPARE_SWAP)
            SWWDT_SetCompareSwap(1u);
            SWWDT_WriteCompareBuf(SWWDT_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == SWWDT_PWM_COMPARE_SWAP) */

        #if (1u == SWWDT_PWM_PERIOD_SWAP)
            SWWDT_SetPeriodSwap(1u);
            SWWDT_WritePeriodBuf(SWWDT_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == SWWDT_PWM_PERIOD_SWAP) */
    #endif  /* (SWWDT__PWM_SEL == SWWDT_CONFIG) */
    
}


/*******************************************************************************
* Function Name: SWWDT_Enable
********************************************************************************
*
* Summary:
*  Enables the SWWDT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    SWWDT_BLOCK_CONTROL_REG |= SWWDT_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (SWWDT__PWM_SEL == SWWDT_CONFIG)
        #if (0u == SWWDT_PWM_START_SIGNAL_PRESENT)
            SWWDT_TriggerCommand(SWWDT_MASK, SWWDT_CMD_START);
        #endif /* (0u == SWWDT_PWM_START_SIGNAL_PRESENT) */
    #endif /* (SWWDT__PWM_SEL == SWWDT_CONFIG) */

    #if (SWWDT__TIMER == SWWDT_CONFIG)
        #if (0u == SWWDT_TC_START_SIGNAL_PRESENT)
            SWWDT_TriggerCommand(SWWDT_MASK, SWWDT_CMD_START);
        #endif /* (0u == SWWDT_TC_START_SIGNAL_PRESENT) */
    #endif /* (SWWDT__TIMER == SWWDT_CONFIG) */
    
    #if (SWWDT__QUAD == SWWDT_CONFIG)
        #if (0u != SWWDT_QUAD_AUTO_START)
            SWWDT_TriggerCommand(SWWDT_MASK, SWWDT_CMD_RELOAD);
        #endif /* (0u != SWWDT_QUAD_AUTO_START) */
    #endif  /* (SWWDT__QUAD == SWWDT_CONFIG) */
}


/*******************************************************************************
* Function Name: SWWDT_Start
********************************************************************************
*
* Summary:
*  Initializes the SWWDT with default customizer
*  values when called the first time and enables the SWWDT.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  SWWDT_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time SWWDT_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the SWWDT_Start() routine.
*
*******************************************************************************/
void SWWDT_Start(void)
{
    if (0u == SWWDT_initVar)
    {
        SWWDT_Init();
        SWWDT_initVar = 1u;
    }

    SWWDT_Enable();
}


/*******************************************************************************
* Function Name: SWWDT_Stop
********************************************************************************
*
* Summary:
*  Disables the SWWDT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_BLOCK_CONTROL_REG &= (uint32)~SWWDT_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the SWWDT. This function is used when
*  configured as a generic SWWDT and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the SWWDT to operate in
*   Values:
*   - SWWDT_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - SWWDT_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - SWWDT_MODE_QUAD - Quadrature decoder
*         - SWWDT_MODE_PWM - PWM
*         - SWWDT_MODE_PWM_DT - PWM with dead time
*         - SWWDT_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_MODE_MASK;
    SWWDT_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - SWWDT_MODE_X1 - Counts on phi 1 rising
*         - SWWDT_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - SWWDT_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_QUAD_MODE_MASK;
    SWWDT_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - SWWDT_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - SWWDT_PRESCALE_DIVBY2    - Divide by 2
*         - SWWDT_PRESCALE_DIVBY4    - Divide by 4
*         - SWWDT_PRESCALE_DIVBY8    - Divide by 8
*         - SWWDT_PRESCALE_DIVBY16   - Divide by 16
*         - SWWDT_PRESCALE_DIVBY32   - Divide by 32
*         - SWWDT_PRESCALE_DIVBY64   - Divide by 64
*         - SWWDT_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_PRESCALER_MASK;
    SWWDT_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the SWWDT runs
*  continuously or stops when terminal count is reached.  By default the
*  SWWDT operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_ONESHOT_MASK;
    SWWDT_CONTROL_REG |= ((uint32)((oneShotEnable & SWWDT_1BIT_MASK) <<
                                                               SWWDT_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetPWMMode(uint32 modeMask)
{
    SWWDT_TRIG_CONTROL2_REG = (modeMask & SWWDT_6BIT_MASK);
}



/*******************************************************************************
* Function Name: SWWDT_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_PWM_SYNC_KILL_MASK;
    SWWDT_CONTROL_REG |= ((uint32)((syncKillEnable & SWWDT_1BIT_MASK)  <<
                                               SWWDT_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_PWM_STOP_KILL_MASK;
    SWWDT_CONTROL_REG |= ((uint32)((stopOnKillEnable & SWWDT_1BIT_MASK)  <<
                                                         SWWDT_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_PRESCALER_MASK;
    SWWDT_CONTROL_REG |= ((uint32)((deadTime & SWWDT_8BIT_MASK) <<
                                                          SWWDT_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - SWWDT_INVERT_LINE   - Inverts the line output
*         - SWWDT_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_INV_OUT_MASK;
    SWWDT_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: SWWDT_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_WriteCounter(uint32 count)
{
    SWWDT_COUNTER_REG = (count & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 SWWDT_ReadCounter(void)
{
    return (SWWDT_COUNTER_REG & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - SWWDT_COUNT_UP       - Counts up
*     - SWWDT_COUNT_DOWN     - Counts down
*     - SWWDT_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - SWWDT_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_UPDOWN_MASK;
    SWWDT_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_WritePeriod(uint32 period)
{
    SWWDT_PERIOD_REG = (period & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 SWWDT_ReadPeriod(void)
{
    return (SWWDT_PERIOD_REG & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_RELOAD_CC_MASK;
    SWWDT_CONTROL_REG |= (swapEnable & SWWDT_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_WritePeriodBuf(uint32 periodBuf)
{
    SWWDT_PERIOD_BUF_REG = (periodBuf & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 SWWDT_ReadPeriodBuf(void)
{
    return (SWWDT_PERIOD_BUF_REG & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_CONTROL_REG &= (uint32)~SWWDT_RELOAD_PERIOD_MASK;
    SWWDT_CONTROL_REG |= ((uint32)((swapEnable & SWWDT_1BIT_MASK) <<
                                                            SWWDT_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void SWWDT_WriteCompare(uint32 compare)
{
    #if (SWWDT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SWWDT_CY_TCPWM_4000) */

    #if (SWWDT_CY_TCPWM_4000)
        currentMode = ((SWWDT_CONTROL_REG & SWWDT_UPDOWN_MASK) >> SWWDT_UPDOWN_SHIFT);

        if (((uint32)SWWDT__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)SWWDT__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (SWWDT_CY_TCPWM_4000) */
    
    SWWDT_COMP_CAP_REG = (compare & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 SWWDT_ReadCompare(void)
{
    #if (SWWDT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SWWDT_CY_TCPWM_4000) */

    #if (SWWDT_CY_TCPWM_4000)
        currentMode = ((SWWDT_CONTROL_REG & SWWDT_UPDOWN_MASK) >> SWWDT_UPDOWN_SHIFT);
        
        regVal = SWWDT_COMP_CAP_REG;
        
        if (((uint32)SWWDT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SWWDT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SWWDT_16BIT_MASK);
    #else
        return (SWWDT_COMP_CAP_REG & SWWDT_16BIT_MASK);
    #endif /* (SWWDT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SWWDT_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void SWWDT_WriteCompareBuf(uint32 compareBuf)
{
    #if (SWWDT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SWWDT_CY_TCPWM_4000) */

    #if (SWWDT_CY_TCPWM_4000)
        currentMode = ((SWWDT_CONTROL_REG & SWWDT_UPDOWN_MASK) >> SWWDT_UPDOWN_SHIFT);

        if (((uint32)SWWDT__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)SWWDT__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (SWWDT_CY_TCPWM_4000) */
    
    SWWDT_COMP_CAP_BUF_REG = (compareBuf & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 SWWDT_ReadCompareBuf(void)
{
    #if (SWWDT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SWWDT_CY_TCPWM_4000) */

    #if (SWWDT_CY_TCPWM_4000)
        currentMode = ((SWWDT_CONTROL_REG & SWWDT_UPDOWN_MASK) >> SWWDT_UPDOWN_SHIFT);

        regVal = SWWDT_COMP_CAP_BUF_REG;
        
        if (((uint32)SWWDT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SWWDT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SWWDT_16BIT_MASK);
    #else
        return (SWWDT_COMP_CAP_BUF_REG & SWWDT_16BIT_MASK);
    #endif /* (SWWDT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SWWDT_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 SWWDT_ReadCapture(void)
{
    return (SWWDT_COMP_CAP_REG & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 SWWDT_ReadCaptureBuf(void)
{
    return (SWWDT_COMP_CAP_BUF_REG & SWWDT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SWWDT_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SWWDT_TRIG_LEVEL     - Level
*     - SWWDT_TRIG_RISING    - Rising edge
*     - SWWDT_TRIG_FALLING   - Falling edge
*     - SWWDT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_TRIG_CONTROL1_REG &= (uint32)~SWWDT_CAPTURE_MASK;
    SWWDT_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SWWDT_TRIG_LEVEL     - Level
*     - SWWDT_TRIG_RISING    - Rising edge
*     - SWWDT_TRIG_FALLING   - Falling edge
*     - SWWDT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_TRIG_CONTROL1_REG &= (uint32)~SWWDT_RELOAD_MASK;
    SWWDT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SWWDT_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SWWDT_TRIG_LEVEL     - Level
*     - SWWDT_TRIG_RISING    - Rising edge
*     - SWWDT_TRIG_FALLING   - Falling edge
*     - SWWDT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_TRIG_CONTROL1_REG &= (uint32)~SWWDT_START_MASK;
    SWWDT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SWWDT_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SWWDT_TRIG_LEVEL     - Level
*     - SWWDT_TRIG_RISING    - Rising edge
*     - SWWDT_TRIG_FALLING   - Falling edge
*     - SWWDT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_TRIG_CONTROL1_REG &= (uint32)~SWWDT_STOP_MASK;
    SWWDT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SWWDT_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SWWDT_TRIG_LEVEL     - Level
*     - SWWDT_TRIG_RISING    - Rising edge
*     - SWWDT_TRIG_FALLING   - Falling edge
*     - SWWDT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_TRIG_CONTROL1_REG &= (uint32)~SWWDT_COUNT_MASK;
    SWWDT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SWWDT_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - SWWDT_CMD_CAPTURE    - Trigger Capture/Switch command
*     - SWWDT_CMD_RELOAD     - Trigger Reload/Index command
*     - SWWDT_CMD_STOP       - Trigger Stop/Kill command
*     - SWWDT_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SWWDT_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SWWDT_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the SWWDT.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - SWWDT_STATUS_DOWN    - Set if counting down
*     - SWWDT_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 SWWDT_ReadStatus(void)
{
    return ((SWWDT_STATUS_REG >> SWWDT_RUNNING_STATUS_SHIFT) |
            (SWWDT_STATUS_REG & SWWDT_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: SWWDT_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - SWWDT_INTR_MASK_TC       - Terminal count mask
*     - SWWDT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetInterruptMode(uint32 interruptMask)
{
    SWWDT_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: SWWDT_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - SWWDT_INTR_MASK_TC       - Terminal count mask
*     - SWWDT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SWWDT_GetInterruptSourceMasked(void)
{
    return (SWWDT_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: SWWDT_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - SWWDT_INTR_MASK_TC       - Terminal count mask
*     - SWWDT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SWWDT_GetInterruptSource(void)
{
    return (SWWDT_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: SWWDT_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - SWWDT_INTR_MASK_TC       - Terminal count mask
*     - SWWDT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_ClearInterrupt(uint32 interruptMask)
{
    SWWDT_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: SWWDT_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - SWWDT_INTR_MASK_TC       - Terminal count mask
*     - SWWDT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SWWDT_SetInterrupt(uint32 interruptMask)
{
    SWWDT_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
