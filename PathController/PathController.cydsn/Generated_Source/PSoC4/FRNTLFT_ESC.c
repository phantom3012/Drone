/*******************************************************************************
* File Name: FRNTLFT_ESC.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the FRNTLFT_ESC
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

#include "FRNTLFT_ESC.h"

uint8 FRNTLFT_ESC_initVar = 0u;


/*******************************************************************************
* Function Name: FRNTLFT_ESC_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default FRNTLFT_ESC configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (FRNTLFT_ESC__QUAD == FRNTLFT_ESC_CONFIG)
        FRNTLFT_ESC_CONTROL_REG = FRNTLFT_ESC_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        FRNTLFT_ESC_TRIG_CONTROL1_REG  = FRNTLFT_ESC_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        FRNTLFT_ESC_SetInterruptMode(FRNTLFT_ESC_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        FRNTLFT_ESC_SetCounterMode(FRNTLFT_ESC_COUNT_DOWN);
        FRNTLFT_ESC_WritePeriod(FRNTLFT_ESC_QUAD_PERIOD_INIT_VALUE);
        FRNTLFT_ESC_WriteCounter(FRNTLFT_ESC_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (FRNTLFT_ESC__QUAD == FRNTLFT_ESC_CONFIG) */

    #if (FRNTLFT_ESC__TIMER == FRNTLFT_ESC_CONFIG)
        FRNTLFT_ESC_CONTROL_REG = FRNTLFT_ESC_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        FRNTLFT_ESC_TRIG_CONTROL1_REG  = FRNTLFT_ESC_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        FRNTLFT_ESC_SetInterruptMode(FRNTLFT_ESC_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        FRNTLFT_ESC_WritePeriod(FRNTLFT_ESC_TC_PERIOD_VALUE );

        #if (FRNTLFT_ESC__COMPARE == FRNTLFT_ESC_TC_COMP_CAP_MODE)
            FRNTLFT_ESC_WriteCompare(FRNTLFT_ESC_TC_COMPARE_VALUE);

            #if (1u == FRNTLFT_ESC_TC_COMPARE_SWAP)
                FRNTLFT_ESC_SetCompareSwap(1u);
                FRNTLFT_ESC_WriteCompareBuf(FRNTLFT_ESC_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == FRNTLFT_ESC_TC_COMPARE_SWAP) */
        #endif  /* (FRNTLFT_ESC__COMPARE == FRNTLFT_ESC_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (FRNTLFT_ESC_CY_TCPWM_V2 && FRNTLFT_ESC_TIMER_UPDOWN_CNT_USED && !FRNTLFT_ESC_CY_TCPWM_4000)
            FRNTLFT_ESC_WriteCounter(1u);
        #elif(FRNTLFT_ESC__COUNT_DOWN == FRNTLFT_ESC_TC_COUNTER_MODE)
            FRNTLFT_ESC_WriteCounter(FRNTLFT_ESC_TC_PERIOD_VALUE);
        #else
            FRNTLFT_ESC_WriteCounter(0u);
        #endif /* (FRNTLFT_ESC_CY_TCPWM_V2 && FRNTLFT_ESC_TIMER_UPDOWN_CNT_USED && !FRNTLFT_ESC_CY_TCPWM_4000) */
    #endif  /* (FRNTLFT_ESC__TIMER == FRNTLFT_ESC_CONFIG) */

    #if (FRNTLFT_ESC__PWM_SEL == FRNTLFT_ESC_CONFIG)
        FRNTLFT_ESC_CONTROL_REG = FRNTLFT_ESC_CTRL_PWM_BASE_CONFIG;

        #if (FRNTLFT_ESC__PWM_PR == FRNTLFT_ESC_PWM_MODE)
            FRNTLFT_ESC_CONTROL_REG |= FRNTLFT_ESC_CTRL_PWM_RUN_MODE;
            FRNTLFT_ESC_WriteCounter(FRNTLFT_ESC_PWM_PR_INIT_VALUE);
        #else
            FRNTLFT_ESC_CONTROL_REG |= FRNTLFT_ESC_CTRL_PWM_ALIGN | FRNTLFT_ESC_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (FRNTLFT_ESC_CY_TCPWM_V2 && FRNTLFT_ESC_PWM_UPDOWN_CNT_USED && !FRNTLFT_ESC_CY_TCPWM_4000)
                FRNTLFT_ESC_WriteCounter(1u);
            #elif (FRNTLFT_ESC__RIGHT == FRNTLFT_ESC_PWM_ALIGN)
                FRNTLFT_ESC_WriteCounter(FRNTLFT_ESC_PWM_PERIOD_VALUE);
            #else 
                FRNTLFT_ESC_WriteCounter(0u);
            #endif  /* (FRNTLFT_ESC_CY_TCPWM_V2 && FRNTLFT_ESC_PWM_UPDOWN_CNT_USED && !FRNTLFT_ESC_CY_TCPWM_4000) */
        #endif  /* (FRNTLFT_ESC__PWM_PR == FRNTLFT_ESC_PWM_MODE) */

        #if (FRNTLFT_ESC__PWM_DT == FRNTLFT_ESC_PWM_MODE)
            FRNTLFT_ESC_CONTROL_REG |= FRNTLFT_ESC_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (FRNTLFT_ESC__PWM_DT == FRNTLFT_ESC_PWM_MODE) */

        #if (FRNTLFT_ESC__PWM == FRNTLFT_ESC_PWM_MODE)
            FRNTLFT_ESC_CONTROL_REG |= FRNTLFT_ESC_CTRL_PWM_PRESCALER;
        #endif  /* (FRNTLFT_ESC__PWM == FRNTLFT_ESC_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        FRNTLFT_ESC_TRIG_CONTROL1_REG  = FRNTLFT_ESC_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        FRNTLFT_ESC_SetInterruptMode(FRNTLFT_ESC_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (FRNTLFT_ESC__PWM_PR == FRNTLFT_ESC_PWM_MODE)
            FRNTLFT_ESC_TRIG_CONTROL2_REG =
                    (FRNTLFT_ESC_CC_MATCH_NO_CHANGE    |
                    FRNTLFT_ESC_OVERLOW_NO_CHANGE      |
                    FRNTLFT_ESC_UNDERFLOW_NO_CHANGE);
        #else
            #if (FRNTLFT_ESC__LEFT == FRNTLFT_ESC_PWM_ALIGN)
                FRNTLFT_ESC_TRIG_CONTROL2_REG = FRNTLFT_ESC_PWM_MODE_LEFT;
            #endif  /* ( FRNTLFT_ESC_PWM_LEFT == FRNTLFT_ESC_PWM_ALIGN) */

            #if (FRNTLFT_ESC__RIGHT == FRNTLFT_ESC_PWM_ALIGN)
                FRNTLFT_ESC_TRIG_CONTROL2_REG = FRNTLFT_ESC_PWM_MODE_RIGHT;
            #endif  /* ( FRNTLFT_ESC_PWM_RIGHT == FRNTLFT_ESC_PWM_ALIGN) */

            #if (FRNTLFT_ESC__CENTER == FRNTLFT_ESC_PWM_ALIGN)
                FRNTLFT_ESC_TRIG_CONTROL2_REG = FRNTLFT_ESC_PWM_MODE_CENTER;
            #endif  /* ( FRNTLFT_ESC_PWM_CENTER == FRNTLFT_ESC_PWM_ALIGN) */

            #if (FRNTLFT_ESC__ASYMMETRIC == FRNTLFT_ESC_PWM_ALIGN)
                FRNTLFT_ESC_TRIG_CONTROL2_REG = FRNTLFT_ESC_PWM_MODE_ASYM;
            #endif  /* (FRNTLFT_ESC__ASYMMETRIC == FRNTLFT_ESC_PWM_ALIGN) */
        #endif  /* (FRNTLFT_ESC__PWM_PR == FRNTLFT_ESC_PWM_MODE) */

        /* Set other values from customizer */
        FRNTLFT_ESC_WritePeriod(FRNTLFT_ESC_PWM_PERIOD_VALUE );
        FRNTLFT_ESC_WriteCompare(FRNTLFT_ESC_PWM_COMPARE_VALUE);

        #if (1u == FRNTLFT_ESC_PWM_COMPARE_SWAP)
            FRNTLFT_ESC_SetCompareSwap(1u);
            FRNTLFT_ESC_WriteCompareBuf(FRNTLFT_ESC_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == FRNTLFT_ESC_PWM_COMPARE_SWAP) */

        #if (1u == FRNTLFT_ESC_PWM_PERIOD_SWAP)
            FRNTLFT_ESC_SetPeriodSwap(1u);
            FRNTLFT_ESC_WritePeriodBuf(FRNTLFT_ESC_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == FRNTLFT_ESC_PWM_PERIOD_SWAP) */
    #endif  /* (FRNTLFT_ESC__PWM_SEL == FRNTLFT_ESC_CONFIG) */
    
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_Enable
********************************************************************************
*
* Summary:
*  Enables the FRNTLFT_ESC.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    FRNTLFT_ESC_BLOCK_CONTROL_REG |= FRNTLFT_ESC_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (FRNTLFT_ESC__PWM_SEL == FRNTLFT_ESC_CONFIG)
        #if (0u == FRNTLFT_ESC_PWM_START_SIGNAL_PRESENT)
            FRNTLFT_ESC_TriggerCommand(FRNTLFT_ESC_MASK, FRNTLFT_ESC_CMD_START);
        #endif /* (0u == FRNTLFT_ESC_PWM_START_SIGNAL_PRESENT) */
    #endif /* (FRNTLFT_ESC__PWM_SEL == FRNTLFT_ESC_CONFIG) */

    #if (FRNTLFT_ESC__TIMER == FRNTLFT_ESC_CONFIG)
        #if (0u == FRNTLFT_ESC_TC_START_SIGNAL_PRESENT)
            FRNTLFT_ESC_TriggerCommand(FRNTLFT_ESC_MASK, FRNTLFT_ESC_CMD_START);
        #endif /* (0u == FRNTLFT_ESC_TC_START_SIGNAL_PRESENT) */
    #endif /* (FRNTLFT_ESC__TIMER == FRNTLFT_ESC_CONFIG) */
    
    #if (FRNTLFT_ESC__QUAD == FRNTLFT_ESC_CONFIG)
        #if (0u != FRNTLFT_ESC_QUAD_AUTO_START)
            FRNTLFT_ESC_TriggerCommand(FRNTLFT_ESC_MASK, FRNTLFT_ESC_CMD_RELOAD);
        #endif /* (0u != FRNTLFT_ESC_QUAD_AUTO_START) */
    #endif  /* (FRNTLFT_ESC__QUAD == FRNTLFT_ESC_CONFIG) */
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_Start
********************************************************************************
*
* Summary:
*  Initializes the FRNTLFT_ESC with default customizer
*  values when called the first time and enables the FRNTLFT_ESC.
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
*  FRNTLFT_ESC_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time FRNTLFT_ESC_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the FRNTLFT_ESC_Start() routine.
*
*******************************************************************************/
void FRNTLFT_ESC_Start(void)
{
    if (0u == FRNTLFT_ESC_initVar)
    {
        FRNTLFT_ESC_Init();
        FRNTLFT_ESC_initVar = 1u;
    }

    FRNTLFT_ESC_Enable();
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_Stop
********************************************************************************
*
* Summary:
*  Disables the FRNTLFT_ESC.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_BLOCK_CONTROL_REG &= (uint32)~FRNTLFT_ESC_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the FRNTLFT_ESC. This function is used when
*  configured as a generic FRNTLFT_ESC and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the FRNTLFT_ESC to operate in
*   Values:
*   - FRNTLFT_ESC_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - FRNTLFT_ESC_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - FRNTLFT_ESC_MODE_QUAD - Quadrature decoder
*         - FRNTLFT_ESC_MODE_PWM - PWM
*         - FRNTLFT_ESC_MODE_PWM_DT - PWM with dead time
*         - FRNTLFT_ESC_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_MODE_MASK;
    FRNTLFT_ESC_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - FRNTLFT_ESC_MODE_X1 - Counts on phi 1 rising
*         - FRNTLFT_ESC_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - FRNTLFT_ESC_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_QUAD_MODE_MASK;
    FRNTLFT_ESC_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - FRNTLFT_ESC_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - FRNTLFT_ESC_PRESCALE_DIVBY2    - Divide by 2
*         - FRNTLFT_ESC_PRESCALE_DIVBY4    - Divide by 4
*         - FRNTLFT_ESC_PRESCALE_DIVBY8    - Divide by 8
*         - FRNTLFT_ESC_PRESCALE_DIVBY16   - Divide by 16
*         - FRNTLFT_ESC_PRESCALE_DIVBY32   - Divide by 32
*         - FRNTLFT_ESC_PRESCALE_DIVBY64   - Divide by 64
*         - FRNTLFT_ESC_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_PRESCALER_MASK;
    FRNTLFT_ESC_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the FRNTLFT_ESC runs
*  continuously or stops when terminal count is reached.  By default the
*  FRNTLFT_ESC operates in the continuous mode.
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
void FRNTLFT_ESC_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_ONESHOT_MASK;
    FRNTLFT_ESC_CONTROL_REG |= ((uint32)((oneShotEnable & FRNTLFT_ESC_1BIT_MASK) <<
                                                               FRNTLFT_ESC_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetPWMMode
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
void FRNTLFT_ESC_SetPWMMode(uint32 modeMask)
{
    FRNTLFT_ESC_TRIG_CONTROL2_REG = (modeMask & FRNTLFT_ESC_6BIT_MASK);
}



/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetPWMSyncKill
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
void FRNTLFT_ESC_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_PWM_SYNC_KILL_MASK;
    FRNTLFT_ESC_CONTROL_REG |= ((uint32)((syncKillEnable & FRNTLFT_ESC_1BIT_MASK)  <<
                                               FRNTLFT_ESC_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetPWMStopOnKill
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
void FRNTLFT_ESC_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_PWM_STOP_KILL_MASK;
    FRNTLFT_ESC_CONTROL_REG |= ((uint32)((stopOnKillEnable & FRNTLFT_ESC_1BIT_MASK)  <<
                                                         FRNTLFT_ESC_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetPWMDeadTime
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
void FRNTLFT_ESC_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_PRESCALER_MASK;
    FRNTLFT_ESC_CONTROL_REG |= ((uint32)((deadTime & FRNTLFT_ESC_8BIT_MASK) <<
                                                          FRNTLFT_ESC_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetPWMInvert
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
*         - FRNTLFT_ESC_INVERT_LINE   - Inverts the line output
*         - FRNTLFT_ESC_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_INV_OUT_MASK;
    FRNTLFT_ESC_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: FRNTLFT_ESC_WriteCounter
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
void FRNTLFT_ESC_WriteCounter(uint32 count)
{
    FRNTLFT_ESC_COUNTER_REG = (count & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_ReadCounter
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
uint32 FRNTLFT_ESC_ReadCounter(void)
{
    return (FRNTLFT_ESC_COUNTER_REG & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - FRNTLFT_ESC_COUNT_UP       - Counts up
*     - FRNTLFT_ESC_COUNT_DOWN     - Counts down
*     - FRNTLFT_ESC_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - FRNTLFT_ESC_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_UPDOWN_MASK;
    FRNTLFT_ESC_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_WritePeriod
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
void FRNTLFT_ESC_WritePeriod(uint32 period)
{
    FRNTLFT_ESC_PERIOD_REG = (period & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_ReadPeriod
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
uint32 FRNTLFT_ESC_ReadPeriod(void)
{
    return (FRNTLFT_ESC_PERIOD_REG & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetCompareSwap
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
void FRNTLFT_ESC_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_RELOAD_CC_MASK;
    FRNTLFT_ESC_CONTROL_REG |= (swapEnable & FRNTLFT_ESC_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_WritePeriodBuf
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
void FRNTLFT_ESC_WritePeriodBuf(uint32 periodBuf)
{
    FRNTLFT_ESC_PERIOD_BUF_REG = (periodBuf & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_ReadPeriodBuf
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
uint32 FRNTLFT_ESC_ReadPeriodBuf(void)
{
    return (FRNTLFT_ESC_PERIOD_BUF_REG & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetPeriodSwap
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
void FRNTLFT_ESC_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_CONTROL_REG &= (uint32)~FRNTLFT_ESC_RELOAD_PERIOD_MASK;
    FRNTLFT_ESC_CONTROL_REG |= ((uint32)((swapEnable & FRNTLFT_ESC_1BIT_MASK) <<
                                                            FRNTLFT_ESC_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_WriteCompare
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
void FRNTLFT_ESC_WriteCompare(uint32 compare)
{
    #if (FRNTLFT_ESC_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (FRNTLFT_ESC_CY_TCPWM_4000) */

    #if (FRNTLFT_ESC_CY_TCPWM_4000)
        currentMode = ((FRNTLFT_ESC_CONTROL_REG & FRNTLFT_ESC_UPDOWN_MASK) >> FRNTLFT_ESC_UPDOWN_SHIFT);

        if (((uint32)FRNTLFT_ESC__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)FRNTLFT_ESC__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (FRNTLFT_ESC_CY_TCPWM_4000) */
    
    FRNTLFT_ESC_COMP_CAP_REG = (compare & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_ReadCompare
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
uint32 FRNTLFT_ESC_ReadCompare(void)
{
    #if (FRNTLFT_ESC_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (FRNTLFT_ESC_CY_TCPWM_4000) */

    #if (FRNTLFT_ESC_CY_TCPWM_4000)
        currentMode = ((FRNTLFT_ESC_CONTROL_REG & FRNTLFT_ESC_UPDOWN_MASK) >> FRNTLFT_ESC_UPDOWN_SHIFT);
        
        regVal = FRNTLFT_ESC_COMP_CAP_REG;
        
        if (((uint32)FRNTLFT_ESC__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)FRNTLFT_ESC__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & FRNTLFT_ESC_16BIT_MASK);
    #else
        return (FRNTLFT_ESC_COMP_CAP_REG & FRNTLFT_ESC_16BIT_MASK);
    #endif /* (FRNTLFT_ESC_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_WriteCompareBuf
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
void FRNTLFT_ESC_WriteCompareBuf(uint32 compareBuf)
{
    #if (FRNTLFT_ESC_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (FRNTLFT_ESC_CY_TCPWM_4000) */

    #if (FRNTLFT_ESC_CY_TCPWM_4000)
        currentMode = ((FRNTLFT_ESC_CONTROL_REG & FRNTLFT_ESC_UPDOWN_MASK) >> FRNTLFT_ESC_UPDOWN_SHIFT);

        if (((uint32)FRNTLFT_ESC__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)FRNTLFT_ESC__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (FRNTLFT_ESC_CY_TCPWM_4000) */
    
    FRNTLFT_ESC_COMP_CAP_BUF_REG = (compareBuf & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_ReadCompareBuf
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
uint32 FRNTLFT_ESC_ReadCompareBuf(void)
{
    #if (FRNTLFT_ESC_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (FRNTLFT_ESC_CY_TCPWM_4000) */

    #if (FRNTLFT_ESC_CY_TCPWM_4000)
        currentMode = ((FRNTLFT_ESC_CONTROL_REG & FRNTLFT_ESC_UPDOWN_MASK) >> FRNTLFT_ESC_UPDOWN_SHIFT);

        regVal = FRNTLFT_ESC_COMP_CAP_BUF_REG;
        
        if (((uint32)FRNTLFT_ESC__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)FRNTLFT_ESC__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & FRNTLFT_ESC_16BIT_MASK);
    #else
        return (FRNTLFT_ESC_COMP_CAP_BUF_REG & FRNTLFT_ESC_16BIT_MASK);
    #endif /* (FRNTLFT_ESC_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_ReadCapture
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
uint32 FRNTLFT_ESC_ReadCapture(void)
{
    return (FRNTLFT_ESC_COMP_CAP_REG & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_ReadCaptureBuf
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
uint32 FRNTLFT_ESC_ReadCaptureBuf(void)
{
    return (FRNTLFT_ESC_COMP_CAP_BUF_REG & FRNTLFT_ESC_16BIT_MASK);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetCaptureMode
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
*     - FRNTLFT_ESC_TRIG_LEVEL     - Level
*     - FRNTLFT_ESC_TRIG_RISING    - Rising edge
*     - FRNTLFT_ESC_TRIG_FALLING   - Falling edge
*     - FRNTLFT_ESC_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_TRIG_CONTROL1_REG &= (uint32)~FRNTLFT_ESC_CAPTURE_MASK;
    FRNTLFT_ESC_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - FRNTLFT_ESC_TRIG_LEVEL     - Level
*     - FRNTLFT_ESC_TRIG_RISING    - Rising edge
*     - FRNTLFT_ESC_TRIG_FALLING   - Falling edge
*     - FRNTLFT_ESC_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_TRIG_CONTROL1_REG &= (uint32)~FRNTLFT_ESC_RELOAD_MASK;
    FRNTLFT_ESC_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << FRNTLFT_ESC_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - FRNTLFT_ESC_TRIG_LEVEL     - Level
*     - FRNTLFT_ESC_TRIG_RISING    - Rising edge
*     - FRNTLFT_ESC_TRIG_FALLING   - Falling edge
*     - FRNTLFT_ESC_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_TRIG_CONTROL1_REG &= (uint32)~FRNTLFT_ESC_START_MASK;
    FRNTLFT_ESC_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << FRNTLFT_ESC_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - FRNTLFT_ESC_TRIG_LEVEL     - Level
*     - FRNTLFT_ESC_TRIG_RISING    - Rising edge
*     - FRNTLFT_ESC_TRIG_FALLING   - Falling edge
*     - FRNTLFT_ESC_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_TRIG_CONTROL1_REG &= (uint32)~FRNTLFT_ESC_STOP_MASK;
    FRNTLFT_ESC_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << FRNTLFT_ESC_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - FRNTLFT_ESC_TRIG_LEVEL     - Level
*     - FRNTLFT_ESC_TRIG_RISING    - Rising edge
*     - FRNTLFT_ESC_TRIG_FALLING   - Falling edge
*     - FRNTLFT_ESC_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_TRIG_CONTROL1_REG &= (uint32)~FRNTLFT_ESC_COUNT_MASK;
    FRNTLFT_ESC_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << FRNTLFT_ESC_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_TriggerCommand
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
*     - FRNTLFT_ESC_CMD_CAPTURE    - Trigger Capture/Switch command
*     - FRNTLFT_ESC_CMD_RELOAD     - Trigger Reload/Index command
*     - FRNTLFT_ESC_CMD_STOP       - Trigger Stop/Kill command
*     - FRNTLFT_ESC_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    FRNTLFT_ESC_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the FRNTLFT_ESC.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - FRNTLFT_ESC_STATUS_DOWN    - Set if counting down
*     - FRNTLFT_ESC_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 FRNTLFT_ESC_ReadStatus(void)
{
    return ((FRNTLFT_ESC_STATUS_REG >> FRNTLFT_ESC_RUNNING_STATUS_SHIFT) |
            (FRNTLFT_ESC_STATUS_REG & FRNTLFT_ESC_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - FRNTLFT_ESC_INTR_MASK_TC       - Terminal count mask
*     - FRNTLFT_ESC_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetInterruptMode(uint32 interruptMask)
{
    FRNTLFT_ESC_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_GetInterruptSourceMasked
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
*     - FRNTLFT_ESC_INTR_MASK_TC       - Terminal count mask
*     - FRNTLFT_ESC_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 FRNTLFT_ESC_GetInterruptSourceMasked(void)
{
    return (FRNTLFT_ESC_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_GetInterruptSource
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
*     - FRNTLFT_ESC_INTR_MASK_TC       - Terminal count mask
*     - FRNTLFT_ESC_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 FRNTLFT_ESC_GetInterruptSource(void)
{
    return (FRNTLFT_ESC_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - FRNTLFT_ESC_INTR_MASK_TC       - Terminal count mask
*     - FRNTLFT_ESC_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_ClearInterrupt(uint32 interruptMask)
{
    FRNTLFT_ESC_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: FRNTLFT_ESC_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - FRNTLFT_ESC_INTR_MASK_TC       - Terminal count mask
*     - FRNTLFT_ESC_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void FRNTLFT_ESC_SetInterrupt(uint32 interruptMask)
{
    FRNTLFT_ESC_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
