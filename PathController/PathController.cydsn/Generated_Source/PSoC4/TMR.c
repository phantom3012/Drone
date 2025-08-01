/*******************************************************************************
* File Name: TMR.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the TMR
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

#include "TMR.h"

uint8 TMR_initVar = 0u;


/*******************************************************************************
* Function Name: TMR_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default TMR configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TMR_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (TMR__QUAD == TMR_CONFIG)
        TMR_CONTROL_REG = TMR_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TMR_TRIG_CONTROL1_REG  = TMR_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        TMR_SetInterruptMode(TMR_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        TMR_SetCounterMode(TMR_COUNT_DOWN);
        TMR_WritePeriod(TMR_QUAD_PERIOD_INIT_VALUE);
        TMR_WriteCounter(TMR_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (TMR__QUAD == TMR_CONFIG) */

    #if (TMR__TIMER == TMR_CONFIG)
        TMR_CONTROL_REG = TMR_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TMR_TRIG_CONTROL1_REG  = TMR_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TMR_SetInterruptMode(TMR_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        TMR_WritePeriod(TMR_TC_PERIOD_VALUE );

        #if (TMR__COMPARE == TMR_TC_COMP_CAP_MODE)
            TMR_WriteCompare(TMR_TC_COMPARE_VALUE);

            #if (1u == TMR_TC_COMPARE_SWAP)
                TMR_SetCompareSwap(1u);
                TMR_WriteCompareBuf(TMR_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == TMR_TC_COMPARE_SWAP) */
        #endif  /* (TMR__COMPARE == TMR_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (TMR_CY_TCPWM_V2 && TMR_TIMER_UPDOWN_CNT_USED && !TMR_CY_TCPWM_4000)
            TMR_WriteCounter(1u);
        #elif(TMR__COUNT_DOWN == TMR_TC_COUNTER_MODE)
            TMR_WriteCounter(TMR_TC_PERIOD_VALUE);
        #else
            TMR_WriteCounter(0u);
        #endif /* (TMR_CY_TCPWM_V2 && TMR_TIMER_UPDOWN_CNT_USED && !TMR_CY_TCPWM_4000) */
    #endif  /* (TMR__TIMER == TMR_CONFIG) */

    #if (TMR__PWM_SEL == TMR_CONFIG)
        TMR_CONTROL_REG = TMR_CTRL_PWM_BASE_CONFIG;

        #if (TMR__PWM_PR == TMR_PWM_MODE)
            TMR_CONTROL_REG |= TMR_CTRL_PWM_RUN_MODE;
            TMR_WriteCounter(TMR_PWM_PR_INIT_VALUE);
        #else
            TMR_CONTROL_REG |= TMR_CTRL_PWM_ALIGN | TMR_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (TMR_CY_TCPWM_V2 && TMR_PWM_UPDOWN_CNT_USED && !TMR_CY_TCPWM_4000)
                TMR_WriteCounter(1u);
            #elif (TMR__RIGHT == TMR_PWM_ALIGN)
                TMR_WriteCounter(TMR_PWM_PERIOD_VALUE);
            #else 
                TMR_WriteCounter(0u);
            #endif  /* (TMR_CY_TCPWM_V2 && TMR_PWM_UPDOWN_CNT_USED && !TMR_CY_TCPWM_4000) */
        #endif  /* (TMR__PWM_PR == TMR_PWM_MODE) */

        #if (TMR__PWM_DT == TMR_PWM_MODE)
            TMR_CONTROL_REG |= TMR_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (TMR__PWM_DT == TMR_PWM_MODE) */

        #if (TMR__PWM == TMR_PWM_MODE)
            TMR_CONTROL_REG |= TMR_CTRL_PWM_PRESCALER;
        #endif  /* (TMR__PWM == TMR_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        TMR_TRIG_CONTROL1_REG  = TMR_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TMR_SetInterruptMode(TMR_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (TMR__PWM_PR == TMR_PWM_MODE)
            TMR_TRIG_CONTROL2_REG =
                    (TMR_CC_MATCH_NO_CHANGE    |
                    TMR_OVERLOW_NO_CHANGE      |
                    TMR_UNDERFLOW_NO_CHANGE);
        #else
            #if (TMR__LEFT == TMR_PWM_ALIGN)
                TMR_TRIG_CONTROL2_REG = TMR_PWM_MODE_LEFT;
            #endif  /* ( TMR_PWM_LEFT == TMR_PWM_ALIGN) */

            #if (TMR__RIGHT == TMR_PWM_ALIGN)
                TMR_TRIG_CONTROL2_REG = TMR_PWM_MODE_RIGHT;
            #endif  /* ( TMR_PWM_RIGHT == TMR_PWM_ALIGN) */

            #if (TMR__CENTER == TMR_PWM_ALIGN)
                TMR_TRIG_CONTROL2_REG = TMR_PWM_MODE_CENTER;
            #endif  /* ( TMR_PWM_CENTER == TMR_PWM_ALIGN) */

            #if (TMR__ASYMMETRIC == TMR_PWM_ALIGN)
                TMR_TRIG_CONTROL2_REG = TMR_PWM_MODE_ASYM;
            #endif  /* (TMR__ASYMMETRIC == TMR_PWM_ALIGN) */
        #endif  /* (TMR__PWM_PR == TMR_PWM_MODE) */

        /* Set other values from customizer */
        TMR_WritePeriod(TMR_PWM_PERIOD_VALUE );
        TMR_WriteCompare(TMR_PWM_COMPARE_VALUE);

        #if (1u == TMR_PWM_COMPARE_SWAP)
            TMR_SetCompareSwap(1u);
            TMR_WriteCompareBuf(TMR_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == TMR_PWM_COMPARE_SWAP) */

        #if (1u == TMR_PWM_PERIOD_SWAP)
            TMR_SetPeriodSwap(1u);
            TMR_WritePeriodBuf(TMR_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == TMR_PWM_PERIOD_SWAP) */
    #endif  /* (TMR__PWM_SEL == TMR_CONFIG) */
    
}


/*******************************************************************************
* Function Name: TMR_Enable
********************************************************************************
*
* Summary:
*  Enables the TMR.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TMR_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    TMR_BLOCK_CONTROL_REG |= TMR_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (TMR__PWM_SEL == TMR_CONFIG)
        #if (0u == TMR_PWM_START_SIGNAL_PRESENT)
            TMR_TriggerCommand(TMR_MASK, TMR_CMD_START);
        #endif /* (0u == TMR_PWM_START_SIGNAL_PRESENT) */
    #endif /* (TMR__PWM_SEL == TMR_CONFIG) */

    #if (TMR__TIMER == TMR_CONFIG)
        #if (0u == TMR_TC_START_SIGNAL_PRESENT)
            TMR_TriggerCommand(TMR_MASK, TMR_CMD_START);
        #endif /* (0u == TMR_TC_START_SIGNAL_PRESENT) */
    #endif /* (TMR__TIMER == TMR_CONFIG) */
    
    #if (TMR__QUAD == TMR_CONFIG)
        #if (0u != TMR_QUAD_AUTO_START)
            TMR_TriggerCommand(TMR_MASK, TMR_CMD_RELOAD);
        #endif /* (0u != TMR_QUAD_AUTO_START) */
    #endif  /* (TMR__QUAD == TMR_CONFIG) */
}


/*******************************************************************************
* Function Name: TMR_Start
********************************************************************************
*
* Summary:
*  Initializes the TMR with default customizer
*  values when called the first time and enables the TMR.
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
*  TMR_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time TMR_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the TMR_Start() routine.
*
*******************************************************************************/
void TMR_Start(void)
{
    if (0u == TMR_initVar)
    {
        TMR_Init();
        TMR_initVar = 1u;
    }

    TMR_Enable();
}


/*******************************************************************************
* Function Name: TMR_Stop
********************************************************************************
*
* Summary:
*  Disables the TMR.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TMR_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_BLOCK_CONTROL_REG &= (uint32)~TMR_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the TMR. This function is used when
*  configured as a generic TMR and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the TMR to operate in
*   Values:
*   - TMR_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - TMR_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - TMR_MODE_QUAD - Quadrature decoder
*         - TMR_MODE_PWM - PWM
*         - TMR_MODE_PWM_DT - PWM with dead time
*         - TMR_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_MODE_MASK;
    TMR_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - TMR_MODE_X1 - Counts on phi 1 rising
*         - TMR_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - TMR_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_QUAD_MODE_MASK;
    TMR_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - TMR_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - TMR_PRESCALE_DIVBY2    - Divide by 2
*         - TMR_PRESCALE_DIVBY4    - Divide by 4
*         - TMR_PRESCALE_DIVBY8    - Divide by 8
*         - TMR_PRESCALE_DIVBY16   - Divide by 16
*         - TMR_PRESCALE_DIVBY32   - Divide by 32
*         - TMR_PRESCALE_DIVBY64   - Divide by 64
*         - TMR_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_PRESCALER_MASK;
    TMR_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the TMR runs
*  continuously or stops when terminal count is reached.  By default the
*  TMR operates in the continuous mode.
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
void TMR_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_ONESHOT_MASK;
    TMR_CONTROL_REG |= ((uint32)((oneShotEnable & TMR_1BIT_MASK) <<
                                                               TMR_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetPWMMode
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
void TMR_SetPWMMode(uint32 modeMask)
{
    TMR_TRIG_CONTROL2_REG = (modeMask & TMR_6BIT_MASK);
}



/*******************************************************************************
* Function Name: TMR_SetPWMSyncKill
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
void TMR_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_PWM_SYNC_KILL_MASK;
    TMR_CONTROL_REG |= ((uint32)((syncKillEnable & TMR_1BIT_MASK)  <<
                                               TMR_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetPWMStopOnKill
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
void TMR_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_PWM_STOP_KILL_MASK;
    TMR_CONTROL_REG |= ((uint32)((stopOnKillEnable & TMR_1BIT_MASK)  <<
                                                         TMR_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetPWMDeadTime
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
void TMR_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_PRESCALER_MASK;
    TMR_CONTROL_REG |= ((uint32)((deadTime & TMR_8BIT_MASK) <<
                                                          TMR_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetPWMInvert
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
*         - TMR_INVERT_LINE   - Inverts the line output
*         - TMR_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_INV_OUT_MASK;
    TMR_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: TMR_WriteCounter
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
void TMR_WriteCounter(uint32 count)
{
    TMR_COUNTER_REG = (count & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_ReadCounter
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
uint32 TMR_ReadCounter(void)
{
    return (TMR_COUNTER_REG & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - TMR_COUNT_UP       - Counts up
*     - TMR_COUNT_DOWN     - Counts down
*     - TMR_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - TMR_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_UPDOWN_MASK;
    TMR_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_WritePeriod
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
void TMR_WritePeriod(uint32 period)
{
    TMR_PERIOD_REG = (period & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_ReadPeriod
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
uint32 TMR_ReadPeriod(void)
{
    return (TMR_PERIOD_REG & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_SetCompareSwap
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
void TMR_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_RELOAD_CC_MASK;
    TMR_CONTROL_REG |= (swapEnable & TMR_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_WritePeriodBuf
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
void TMR_WritePeriodBuf(uint32 periodBuf)
{
    TMR_PERIOD_BUF_REG = (periodBuf & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_ReadPeriodBuf
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
uint32 TMR_ReadPeriodBuf(void)
{
    return (TMR_PERIOD_BUF_REG & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_SetPeriodSwap
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
void TMR_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_CONTROL_REG &= (uint32)~TMR_RELOAD_PERIOD_MASK;
    TMR_CONTROL_REG |= ((uint32)((swapEnable & TMR_1BIT_MASK) <<
                                                            TMR_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_WriteCompare
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
void TMR_WriteCompare(uint32 compare)
{
    #if (TMR_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TMR_CY_TCPWM_4000) */

    #if (TMR_CY_TCPWM_4000)
        currentMode = ((TMR_CONTROL_REG & TMR_UPDOWN_MASK) >> TMR_UPDOWN_SHIFT);

        if (((uint32)TMR__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)TMR__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (TMR_CY_TCPWM_4000) */
    
    TMR_COMP_CAP_REG = (compare & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_ReadCompare
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
uint32 TMR_ReadCompare(void)
{
    #if (TMR_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TMR_CY_TCPWM_4000) */

    #if (TMR_CY_TCPWM_4000)
        currentMode = ((TMR_CONTROL_REG & TMR_UPDOWN_MASK) >> TMR_UPDOWN_SHIFT);
        
        regVal = TMR_COMP_CAP_REG;
        
        if (((uint32)TMR__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TMR__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TMR_16BIT_MASK);
    #else
        return (TMR_COMP_CAP_REG & TMR_16BIT_MASK);
    #endif /* (TMR_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TMR_WriteCompareBuf
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
void TMR_WriteCompareBuf(uint32 compareBuf)
{
    #if (TMR_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TMR_CY_TCPWM_4000) */

    #if (TMR_CY_TCPWM_4000)
        currentMode = ((TMR_CONTROL_REG & TMR_UPDOWN_MASK) >> TMR_UPDOWN_SHIFT);

        if (((uint32)TMR__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)TMR__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (TMR_CY_TCPWM_4000) */
    
    TMR_COMP_CAP_BUF_REG = (compareBuf & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_ReadCompareBuf
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
uint32 TMR_ReadCompareBuf(void)
{
    #if (TMR_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TMR_CY_TCPWM_4000) */

    #if (TMR_CY_TCPWM_4000)
        currentMode = ((TMR_CONTROL_REG & TMR_UPDOWN_MASK) >> TMR_UPDOWN_SHIFT);

        regVal = TMR_COMP_CAP_BUF_REG;
        
        if (((uint32)TMR__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TMR__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TMR_16BIT_MASK);
    #else
        return (TMR_COMP_CAP_BUF_REG & TMR_16BIT_MASK);
    #endif /* (TMR_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TMR_ReadCapture
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
uint32 TMR_ReadCapture(void)
{
    return (TMR_COMP_CAP_REG & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_ReadCaptureBuf
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
uint32 TMR_ReadCaptureBuf(void)
{
    return (TMR_COMP_CAP_BUF_REG & TMR_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TMR_SetCaptureMode
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
*     - TMR_TRIG_LEVEL     - Level
*     - TMR_TRIG_RISING    - Rising edge
*     - TMR_TRIG_FALLING   - Falling edge
*     - TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_TRIG_CONTROL1_REG &= (uint32)~TMR_CAPTURE_MASK;
    TMR_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TMR_TRIG_LEVEL     - Level
*     - TMR_TRIG_RISING    - Rising edge
*     - TMR_TRIG_FALLING   - Falling edge
*     - TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_TRIG_CONTROL1_REG &= (uint32)~TMR_RELOAD_MASK;
    TMR_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TMR_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TMR_TRIG_LEVEL     - Level
*     - TMR_TRIG_RISING    - Rising edge
*     - TMR_TRIG_FALLING   - Falling edge
*     - TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_TRIG_CONTROL1_REG &= (uint32)~TMR_START_MASK;
    TMR_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TMR_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TMR_TRIG_LEVEL     - Level
*     - TMR_TRIG_RISING    - Rising edge
*     - TMR_TRIG_FALLING   - Falling edge
*     - TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_TRIG_CONTROL1_REG &= (uint32)~TMR_STOP_MASK;
    TMR_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TMR_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TMR_TRIG_LEVEL     - Level
*     - TMR_TRIG_RISING    - Rising edge
*     - TMR_TRIG_FALLING   - Falling edge
*     - TMR_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_TRIG_CONTROL1_REG &= (uint32)~TMR_COUNT_MASK;
    TMR_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TMR_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_TriggerCommand
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
*     - TMR_CMD_CAPTURE    - Trigger Capture/Switch command
*     - TMR_CMD_RELOAD     - Trigger Reload/Index command
*     - TMR_CMD_STOP       - Trigger Stop/Kill command
*     - TMR_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void TMR_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TMR_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TMR_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the TMR.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - TMR_STATUS_DOWN    - Set if counting down
*     - TMR_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 TMR_ReadStatus(void)
{
    return ((TMR_STATUS_REG >> TMR_RUNNING_STATUS_SHIFT) |
            (TMR_STATUS_REG & TMR_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: TMR_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - TMR_INTR_MASK_TC       - Terminal count mask
*     - TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetInterruptMode(uint32 interruptMask)
{
    TMR_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: TMR_GetInterruptSourceMasked
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
*     - TMR_INTR_MASK_TC       - Terminal count mask
*     - TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TMR_GetInterruptSourceMasked(void)
{
    return (TMR_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: TMR_GetInterruptSource
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
*     - TMR_INTR_MASK_TC       - Terminal count mask
*     - TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TMR_GetInterruptSource(void)
{
    return (TMR_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: TMR_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - TMR_INTR_MASK_TC       - Terminal count mask
*     - TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TMR_ClearInterrupt(uint32 interruptMask)
{
    TMR_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: TMR_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - TMR_INTR_MASK_TC       - Terminal count mask
*     - TMR_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TMR_SetInterrupt(uint32 interruptMask)
{
    TMR_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
