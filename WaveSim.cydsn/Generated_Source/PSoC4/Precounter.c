/*******************************************************************************
* File Name: Precounter.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the Precounter
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

#include "Precounter.h"

uint8 Precounter_initVar = 0u;


/*******************************************************************************
* Function Name: Precounter_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Precounter configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Precounter__QUAD == Precounter_CONFIG)
        Precounter_CONTROL_REG = Precounter_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Precounter_TRIG_CONTROL1_REG  = Precounter_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Precounter_SetInterruptMode(Precounter_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Precounter_SetCounterMode(Precounter_COUNT_DOWN);
        Precounter_WritePeriod(Precounter_QUAD_PERIOD_INIT_VALUE);
        Precounter_WriteCounter(Precounter_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Precounter__QUAD == Precounter_CONFIG) */

    #if (Precounter__TIMER == Precounter_CONFIG)
        Precounter_CONTROL_REG = Precounter_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Precounter_TRIG_CONTROL1_REG  = Precounter_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Precounter_SetInterruptMode(Precounter_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Precounter_WritePeriod(Precounter_TC_PERIOD_VALUE );

        #if (Precounter__COMPARE == Precounter_TC_COMP_CAP_MODE)
            Precounter_WriteCompare(Precounter_TC_COMPARE_VALUE);

            #if (1u == Precounter_TC_COMPARE_SWAP)
                Precounter_SetCompareSwap(1u);
                Precounter_WriteCompareBuf(Precounter_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Precounter_TC_COMPARE_SWAP) */
        #endif  /* (Precounter__COMPARE == Precounter_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Precounter_CY_TCPWM_V2 && Precounter_TIMER_UPDOWN_CNT_USED && !Precounter_CY_TCPWM_4000)
            Precounter_WriteCounter(1u);
        #elif(Precounter__COUNT_DOWN == Precounter_TC_COUNTER_MODE)
            Precounter_WriteCounter(Precounter_TC_PERIOD_VALUE);
        #else
            Precounter_WriteCounter(0u);
        #endif /* (Precounter_CY_TCPWM_V2 && Precounter_TIMER_UPDOWN_CNT_USED && !Precounter_CY_TCPWM_4000) */
    #endif  /* (Precounter__TIMER == Precounter_CONFIG) */

    #if (Precounter__PWM_SEL == Precounter_CONFIG)
        Precounter_CONTROL_REG = Precounter_CTRL_PWM_BASE_CONFIG;

        #if (Precounter__PWM_PR == Precounter_PWM_MODE)
            Precounter_CONTROL_REG |= Precounter_CTRL_PWM_RUN_MODE;
            Precounter_WriteCounter(Precounter_PWM_PR_INIT_VALUE);
        #else
            Precounter_CONTROL_REG |= Precounter_CTRL_PWM_ALIGN | Precounter_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Precounter_CY_TCPWM_V2 && Precounter_PWM_UPDOWN_CNT_USED && !Precounter_CY_TCPWM_4000)
                Precounter_WriteCounter(1u);
            #elif (Precounter__RIGHT == Precounter_PWM_ALIGN)
                Precounter_WriteCounter(Precounter_PWM_PERIOD_VALUE);
            #else 
                Precounter_WriteCounter(0u);
            #endif  /* (Precounter_CY_TCPWM_V2 && Precounter_PWM_UPDOWN_CNT_USED && !Precounter_CY_TCPWM_4000) */
        #endif  /* (Precounter__PWM_PR == Precounter_PWM_MODE) */

        #if (Precounter__PWM_DT == Precounter_PWM_MODE)
            Precounter_CONTROL_REG |= Precounter_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Precounter__PWM_DT == Precounter_PWM_MODE) */

        #if (Precounter__PWM == Precounter_PWM_MODE)
            Precounter_CONTROL_REG |= Precounter_CTRL_PWM_PRESCALER;
        #endif  /* (Precounter__PWM == Precounter_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Precounter_TRIG_CONTROL1_REG  = Precounter_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Precounter_SetInterruptMode(Precounter_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Precounter__PWM_PR == Precounter_PWM_MODE)
            Precounter_TRIG_CONTROL2_REG =
                    (Precounter_CC_MATCH_NO_CHANGE    |
                    Precounter_OVERLOW_NO_CHANGE      |
                    Precounter_UNDERFLOW_NO_CHANGE);
        #else
            #if (Precounter__LEFT == Precounter_PWM_ALIGN)
                Precounter_TRIG_CONTROL2_REG = Precounter_PWM_MODE_LEFT;
            #endif  /* ( Precounter_PWM_LEFT == Precounter_PWM_ALIGN) */

            #if (Precounter__RIGHT == Precounter_PWM_ALIGN)
                Precounter_TRIG_CONTROL2_REG = Precounter_PWM_MODE_RIGHT;
            #endif  /* ( Precounter_PWM_RIGHT == Precounter_PWM_ALIGN) */

            #if (Precounter__CENTER == Precounter_PWM_ALIGN)
                Precounter_TRIG_CONTROL2_REG = Precounter_PWM_MODE_CENTER;
            #endif  /* ( Precounter_PWM_CENTER == Precounter_PWM_ALIGN) */

            #if (Precounter__ASYMMETRIC == Precounter_PWM_ALIGN)
                Precounter_TRIG_CONTROL2_REG = Precounter_PWM_MODE_ASYM;
            #endif  /* (Precounter__ASYMMETRIC == Precounter_PWM_ALIGN) */
        #endif  /* (Precounter__PWM_PR == Precounter_PWM_MODE) */

        /* Set other values from customizer */
        Precounter_WritePeriod(Precounter_PWM_PERIOD_VALUE );
        Precounter_WriteCompare(Precounter_PWM_COMPARE_VALUE);

        #if (1u == Precounter_PWM_COMPARE_SWAP)
            Precounter_SetCompareSwap(1u);
            Precounter_WriteCompareBuf(Precounter_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Precounter_PWM_COMPARE_SWAP) */

        #if (1u == Precounter_PWM_PERIOD_SWAP)
            Precounter_SetPeriodSwap(1u);
            Precounter_WritePeriodBuf(Precounter_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Precounter_PWM_PERIOD_SWAP) */
    #endif  /* (Precounter__PWM_SEL == Precounter_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Precounter_Enable
********************************************************************************
*
* Summary:
*  Enables the Precounter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Precounter_BLOCK_CONTROL_REG |= Precounter_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Precounter__PWM_SEL == Precounter_CONFIG)
        #if (0u == Precounter_PWM_START_SIGNAL_PRESENT)
            Precounter_TriggerCommand(Precounter_MASK, Precounter_CMD_START);
        #endif /* (0u == Precounter_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Precounter__PWM_SEL == Precounter_CONFIG) */

    #if (Precounter__TIMER == Precounter_CONFIG)
        #if (0u == Precounter_TC_START_SIGNAL_PRESENT)
            Precounter_TriggerCommand(Precounter_MASK, Precounter_CMD_START);
        #endif /* (0u == Precounter_TC_START_SIGNAL_PRESENT) */
    #endif /* (Precounter__TIMER == Precounter_CONFIG) */
    
    #if (Precounter__QUAD == Precounter_CONFIG)
        #if (0u != Precounter_QUAD_AUTO_START)
            Precounter_TriggerCommand(Precounter_MASK, Precounter_CMD_RELOAD);
        #endif /* (0u != Precounter_QUAD_AUTO_START) */
    #endif  /* (Precounter__QUAD == Precounter_CONFIG) */
}


/*******************************************************************************
* Function Name: Precounter_Start
********************************************************************************
*
* Summary:
*  Initializes the Precounter with default customizer
*  values when called the first time and enables the Precounter.
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
*  Precounter_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Precounter_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Precounter_Start() routine.
*
*******************************************************************************/
void Precounter_Start(void)
{
    if (0u == Precounter_initVar)
    {
        Precounter_Init();
        Precounter_initVar = 1u;
    }

    Precounter_Enable();
}


/*******************************************************************************
* Function Name: Precounter_Stop
********************************************************************************
*
* Summary:
*  Disables the Precounter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_BLOCK_CONTROL_REG &= (uint32)~Precounter_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Precounter. This function is used when
*  configured as a generic Precounter and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Precounter to operate in
*   Values:
*   - Precounter_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Precounter_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Precounter_MODE_QUAD - Quadrature decoder
*         - Precounter_MODE_PWM - PWM
*         - Precounter_MODE_PWM_DT - PWM with dead time
*         - Precounter_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_MODE_MASK;
    Precounter_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Precounter_MODE_X1 - Counts on phi 1 rising
*         - Precounter_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Precounter_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_QUAD_MODE_MASK;
    Precounter_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Precounter_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Precounter_PRESCALE_DIVBY2    - Divide by 2
*         - Precounter_PRESCALE_DIVBY4    - Divide by 4
*         - Precounter_PRESCALE_DIVBY8    - Divide by 8
*         - Precounter_PRESCALE_DIVBY16   - Divide by 16
*         - Precounter_PRESCALE_DIVBY32   - Divide by 32
*         - Precounter_PRESCALE_DIVBY64   - Divide by 64
*         - Precounter_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_PRESCALER_MASK;
    Precounter_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Precounter runs
*  continuously or stops when terminal count is reached.  By default the
*  Precounter operates in the continuous mode.
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
void Precounter_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_ONESHOT_MASK;
    Precounter_CONTROL_REG |= ((uint32)((oneShotEnable & Precounter_1BIT_MASK) <<
                                                               Precounter_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetPWMMode
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
void Precounter_SetPWMMode(uint32 modeMask)
{
    Precounter_TRIG_CONTROL2_REG = (modeMask & Precounter_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Precounter_SetPWMSyncKill
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
void Precounter_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_PWM_SYNC_KILL_MASK;
    Precounter_CONTROL_REG |= ((uint32)((syncKillEnable & Precounter_1BIT_MASK)  <<
                                               Precounter_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetPWMStopOnKill
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
void Precounter_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_PWM_STOP_KILL_MASK;
    Precounter_CONTROL_REG |= ((uint32)((stopOnKillEnable & Precounter_1BIT_MASK)  <<
                                                         Precounter_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetPWMDeadTime
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
void Precounter_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_PRESCALER_MASK;
    Precounter_CONTROL_REG |= ((uint32)((deadTime & Precounter_8BIT_MASK) <<
                                                          Precounter_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetPWMInvert
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
*         - Precounter_INVERT_LINE   - Inverts the line output
*         - Precounter_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_INV_OUT_MASK;
    Precounter_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Precounter_WriteCounter
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
void Precounter_WriteCounter(uint32 count)
{
    Precounter_COUNTER_REG = (count & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_ReadCounter
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
uint32 Precounter_ReadCounter(void)
{
    return (Precounter_COUNTER_REG & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Precounter_COUNT_UP       - Counts up
*     - Precounter_COUNT_DOWN     - Counts down
*     - Precounter_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Precounter_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_UPDOWN_MASK;
    Precounter_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_WritePeriod
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
void Precounter_WritePeriod(uint32 period)
{
    Precounter_PERIOD_REG = (period & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_ReadPeriod
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
uint32 Precounter_ReadPeriod(void)
{
    return (Precounter_PERIOD_REG & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_SetCompareSwap
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
void Precounter_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_RELOAD_CC_MASK;
    Precounter_CONTROL_REG |= (swapEnable & Precounter_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_WritePeriodBuf
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
void Precounter_WritePeriodBuf(uint32 periodBuf)
{
    Precounter_PERIOD_BUF_REG = (periodBuf & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_ReadPeriodBuf
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
uint32 Precounter_ReadPeriodBuf(void)
{
    return (Precounter_PERIOD_BUF_REG & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_SetPeriodSwap
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
void Precounter_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_CONTROL_REG &= (uint32)~Precounter_RELOAD_PERIOD_MASK;
    Precounter_CONTROL_REG |= ((uint32)((swapEnable & Precounter_1BIT_MASK) <<
                                                            Precounter_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_WriteCompare
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
void Precounter_WriteCompare(uint32 compare)
{
    #if (Precounter_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Precounter_CY_TCPWM_4000) */

    #if (Precounter_CY_TCPWM_4000)
        currentMode = ((Precounter_CONTROL_REG & Precounter_UPDOWN_MASK) >> Precounter_UPDOWN_SHIFT);

        if (((uint32)Precounter__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Precounter__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Precounter_CY_TCPWM_4000) */
    
    Precounter_COMP_CAP_REG = (compare & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_ReadCompare
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
uint32 Precounter_ReadCompare(void)
{
    #if (Precounter_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Precounter_CY_TCPWM_4000) */

    #if (Precounter_CY_TCPWM_4000)
        currentMode = ((Precounter_CONTROL_REG & Precounter_UPDOWN_MASK) >> Precounter_UPDOWN_SHIFT);
        
        regVal = Precounter_COMP_CAP_REG;
        
        if (((uint32)Precounter__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Precounter__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Precounter_16BIT_MASK);
    #else
        return (Precounter_COMP_CAP_REG & Precounter_16BIT_MASK);
    #endif /* (Precounter_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Precounter_WriteCompareBuf
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
void Precounter_WriteCompareBuf(uint32 compareBuf)
{
    #if (Precounter_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Precounter_CY_TCPWM_4000) */

    #if (Precounter_CY_TCPWM_4000)
        currentMode = ((Precounter_CONTROL_REG & Precounter_UPDOWN_MASK) >> Precounter_UPDOWN_SHIFT);

        if (((uint32)Precounter__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Precounter__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Precounter_CY_TCPWM_4000) */
    
    Precounter_COMP_CAP_BUF_REG = (compareBuf & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_ReadCompareBuf
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
uint32 Precounter_ReadCompareBuf(void)
{
    #if (Precounter_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Precounter_CY_TCPWM_4000) */

    #if (Precounter_CY_TCPWM_4000)
        currentMode = ((Precounter_CONTROL_REG & Precounter_UPDOWN_MASK) >> Precounter_UPDOWN_SHIFT);

        regVal = Precounter_COMP_CAP_BUF_REG;
        
        if (((uint32)Precounter__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Precounter__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Precounter_16BIT_MASK);
    #else
        return (Precounter_COMP_CAP_BUF_REG & Precounter_16BIT_MASK);
    #endif /* (Precounter_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Precounter_ReadCapture
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
uint32 Precounter_ReadCapture(void)
{
    return (Precounter_COMP_CAP_REG & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_ReadCaptureBuf
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
uint32 Precounter_ReadCaptureBuf(void)
{
    return (Precounter_COMP_CAP_BUF_REG & Precounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Precounter_SetCaptureMode
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
*     - Precounter_TRIG_LEVEL     - Level
*     - Precounter_TRIG_RISING    - Rising edge
*     - Precounter_TRIG_FALLING   - Falling edge
*     - Precounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_TRIG_CONTROL1_REG &= (uint32)~Precounter_CAPTURE_MASK;
    Precounter_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Precounter_TRIG_LEVEL     - Level
*     - Precounter_TRIG_RISING    - Rising edge
*     - Precounter_TRIG_FALLING   - Falling edge
*     - Precounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_TRIG_CONTROL1_REG &= (uint32)~Precounter_RELOAD_MASK;
    Precounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Precounter_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Precounter_TRIG_LEVEL     - Level
*     - Precounter_TRIG_RISING    - Rising edge
*     - Precounter_TRIG_FALLING   - Falling edge
*     - Precounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_TRIG_CONTROL1_REG &= (uint32)~Precounter_START_MASK;
    Precounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Precounter_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Precounter_TRIG_LEVEL     - Level
*     - Precounter_TRIG_RISING    - Rising edge
*     - Precounter_TRIG_FALLING   - Falling edge
*     - Precounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_TRIG_CONTROL1_REG &= (uint32)~Precounter_STOP_MASK;
    Precounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Precounter_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Precounter_TRIG_LEVEL     - Level
*     - Precounter_TRIG_RISING    - Rising edge
*     - Precounter_TRIG_FALLING   - Falling edge
*     - Precounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_TRIG_CONTROL1_REG &= (uint32)~Precounter_COUNT_MASK;
    Precounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Precounter_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_TriggerCommand
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
*     - Precounter_CMD_CAPTURE    - Trigger Capture/Switch command
*     - Precounter_CMD_RELOAD     - Trigger Reload/Index command
*     - Precounter_CMD_STOP       - Trigger Stop/Kill command
*     - Precounter_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Precounter_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Precounter_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Precounter.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Precounter_STATUS_DOWN    - Set if counting down
*     - Precounter_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Precounter_ReadStatus(void)
{
    return ((Precounter_STATUS_REG >> Precounter_RUNNING_STATUS_SHIFT) |
            (Precounter_STATUS_REG & Precounter_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Precounter_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Precounter_INTR_MASK_TC       - Terminal count mask
*     - Precounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetInterruptMode(uint32 interruptMask)
{
    Precounter_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Precounter_GetInterruptSourceMasked
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
*     - Precounter_INTR_MASK_TC       - Terminal count mask
*     - Precounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Precounter_GetInterruptSourceMasked(void)
{
    return (Precounter_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Precounter_GetInterruptSource
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
*     - Precounter_INTR_MASK_TC       - Terminal count mask
*     - Precounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Precounter_GetInterruptSource(void)
{
    return (Precounter_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Precounter_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Precounter_INTR_MASK_TC       - Terminal count mask
*     - Precounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_ClearInterrupt(uint32 interruptMask)
{
    Precounter_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Precounter_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Precounter_INTR_MASK_TC       - Terminal count mask
*     - Precounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SetInterrupt(uint32 interruptMask)
{
    Precounter_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
