/*******************************************************************************
* File Name: Precounter.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the Precounter
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

#if !defined(CY_TCPWM_Precounter_H)
#define CY_TCPWM_Precounter_H


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
} Precounter_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Precounter_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Precounter_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Precounter_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Precounter_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define Precounter_QUAD_ENCODING_MODES            (0lu)
#define Precounter_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define Precounter_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Precounter_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Precounter_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Precounter_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Precounter_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Precounter_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Precounter_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Precounter_TC_RUN_MODE                    (0lu)
#define Precounter_TC_COUNTER_MODE                (0lu)
#define Precounter_TC_COMP_CAP_MODE               (2lu)
#define Precounter_TC_PRESCALER                   (2lu)

/* Signal modes */
#define Precounter_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Precounter_TC_COUNT_SIGNAL_MODE           (3lu)
#define Precounter_TC_START_SIGNAL_MODE           (0lu)
#define Precounter_TC_STOP_SIGNAL_MODE            (0lu)
#define Precounter_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Precounter_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Precounter_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Precounter_TC_START_SIGNAL_PRESENT        (0lu)
#define Precounter_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Precounter_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Precounter_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define Precounter_PWM_KILL_EVENT                 (0lu)
#define Precounter_PWM_STOP_EVENT                 (0lu)
#define Precounter_PWM_MODE                       (4lu)
#define Precounter_PWM_OUT_N_INVERT               (0lu)
#define Precounter_PWM_OUT_INVERT                 (0lu)
#define Precounter_PWM_ALIGN                      (0lu)
#define Precounter_PWM_RUN_MODE                   (0lu)
#define Precounter_PWM_DEAD_TIME_CYCLE            (0lu)
#define Precounter_PWM_PRESCALER                  (5lu)

/* Signal modes */
#define Precounter_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Precounter_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Precounter_PWM_START_SIGNAL_MODE          (0lu)
#define Precounter_PWM_STOP_SIGNAL_MODE           (0lu)
#define Precounter_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Precounter_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Precounter_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Precounter_PWM_START_SIGNAL_PRESENT       (0lu)
#define Precounter_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Precounter_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Precounter_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Precounter_TC_PERIOD_VALUE                (65535lu)
#define Precounter_TC_COMPARE_VALUE               (65535lu)
#define Precounter_TC_COMPARE_BUF_VALUE           (65535lu)
#define Precounter_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Precounter_PWM_PERIOD_VALUE               (65535lu)
#define Precounter_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Precounter_PWM_PERIOD_SWAP                (0lu)
#define Precounter_PWM_COMPARE_VALUE              (30000lu)
#define Precounter_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Precounter_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Precounter__LEFT 0
#define Precounter__RIGHT 1
#define Precounter__CENTER 2
#define Precounter__ASYMMETRIC 3

#define Precounter__X1 0
#define Precounter__X2 1
#define Precounter__X4 2

#define Precounter__PWM 4
#define Precounter__PWM_DT 5
#define Precounter__PWM_PR 6

#define Precounter__INVERSE 1
#define Precounter__DIRECT 0

#define Precounter__CAPTURE 2
#define Precounter__COMPARE 0

#define Precounter__TRIG_LEVEL 3
#define Precounter__TRIG_RISING 0
#define Precounter__TRIG_FALLING 1
#define Precounter__TRIG_BOTH 2

#define Precounter__INTR_MASK_TC 1
#define Precounter__INTR_MASK_CC_MATCH 2
#define Precounter__INTR_MASK_NONE 0
#define Precounter__INTR_MASK_TC_CC 3

#define Precounter__UNCONFIG 8
#define Precounter__TIMER 1
#define Precounter__QUAD 3
#define Precounter__PWM_SEL 7

#define Precounter__COUNT_UP 0
#define Precounter__COUNT_DOWN 1
#define Precounter__COUNT_UPDOWN0 2
#define Precounter__COUNT_UPDOWN1 3


/* Prescaler */
#define Precounter_PRESCALE_DIVBY1                ((uint32)(0u << Precounter_PRESCALER_SHIFT))
#define Precounter_PRESCALE_DIVBY2                ((uint32)(1u << Precounter_PRESCALER_SHIFT))
#define Precounter_PRESCALE_DIVBY4                ((uint32)(2u << Precounter_PRESCALER_SHIFT))
#define Precounter_PRESCALE_DIVBY8                ((uint32)(3u << Precounter_PRESCALER_SHIFT))
#define Precounter_PRESCALE_DIVBY16               ((uint32)(4u << Precounter_PRESCALER_SHIFT))
#define Precounter_PRESCALE_DIVBY32               ((uint32)(5u << Precounter_PRESCALER_SHIFT))
#define Precounter_PRESCALE_DIVBY64               ((uint32)(6u << Precounter_PRESCALER_SHIFT))
#define Precounter_PRESCALE_DIVBY128              ((uint32)(7u << Precounter_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Precounter_MODE_TIMER_COMPARE             ((uint32)(Precounter__COMPARE         <<  \
                                                                  Precounter_MODE_SHIFT))
#define Precounter_MODE_TIMER_CAPTURE             ((uint32)(Precounter__CAPTURE         <<  \
                                                                  Precounter_MODE_SHIFT))
#define Precounter_MODE_QUAD                      ((uint32)(Precounter__QUAD            <<  \
                                                                  Precounter_MODE_SHIFT))
#define Precounter_MODE_PWM                       ((uint32)(Precounter__PWM             <<  \
                                                                  Precounter_MODE_SHIFT))
#define Precounter_MODE_PWM_DT                    ((uint32)(Precounter__PWM_DT          <<  \
                                                                  Precounter_MODE_SHIFT))
#define Precounter_MODE_PWM_PR                    ((uint32)(Precounter__PWM_PR          <<  \
                                                                  Precounter_MODE_SHIFT))

/* Quad Modes */
#define Precounter_MODE_X1                        ((uint32)(Precounter__X1              <<  \
                                                                  Precounter_QUAD_MODE_SHIFT))
#define Precounter_MODE_X2                        ((uint32)(Precounter__X2              <<  \
                                                                  Precounter_QUAD_MODE_SHIFT))
#define Precounter_MODE_X4                        ((uint32)(Precounter__X4              <<  \
                                                                  Precounter_QUAD_MODE_SHIFT))

/* Counter modes */
#define Precounter_COUNT_UP                       ((uint32)(Precounter__COUNT_UP        <<  \
                                                                  Precounter_UPDOWN_SHIFT))
#define Precounter_COUNT_DOWN                     ((uint32)(Precounter__COUNT_DOWN      <<  \
                                                                  Precounter_UPDOWN_SHIFT))
#define Precounter_COUNT_UPDOWN0                  ((uint32)(Precounter__COUNT_UPDOWN0   <<  \
                                                                  Precounter_UPDOWN_SHIFT))
#define Precounter_COUNT_UPDOWN1                  ((uint32)(Precounter__COUNT_UPDOWN1   <<  \
                                                                  Precounter_UPDOWN_SHIFT))

/* PWM output invert */
#define Precounter_INVERT_LINE                    ((uint32)(Precounter__INVERSE         <<  \
                                                                  Precounter_INV_OUT_SHIFT))
#define Precounter_INVERT_LINE_N                  ((uint32)(Precounter__INVERSE         <<  \
                                                                  Precounter_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Precounter_TRIG_RISING                    ((uint32)Precounter__TRIG_RISING)
#define Precounter_TRIG_FALLING                   ((uint32)Precounter__TRIG_FALLING)
#define Precounter_TRIG_BOTH                      ((uint32)Precounter__TRIG_BOTH)
#define Precounter_TRIG_LEVEL                     ((uint32)Precounter__TRIG_LEVEL)

/* Interrupt mask */
#define Precounter_INTR_MASK_TC                   ((uint32)Precounter__INTR_MASK_TC)
#define Precounter_INTR_MASK_CC_MATCH             ((uint32)Precounter__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Precounter_CC_MATCH_SET                   (0x00u)
#define Precounter_CC_MATCH_CLEAR                 (0x01u)
#define Precounter_CC_MATCH_INVERT                (0x02u)
#define Precounter_CC_MATCH_NO_CHANGE             (0x03u)
#define Precounter_OVERLOW_SET                    (0x00u)
#define Precounter_OVERLOW_CLEAR                  (0x04u)
#define Precounter_OVERLOW_INVERT                 (0x08u)
#define Precounter_OVERLOW_NO_CHANGE              (0x0Cu)
#define Precounter_UNDERFLOW_SET                  (0x00u)
#define Precounter_UNDERFLOW_CLEAR                (0x10u)
#define Precounter_UNDERFLOW_INVERT               (0x20u)
#define Precounter_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Precounter_PWM_MODE_LEFT                  (Precounter_CC_MATCH_CLEAR        |   \
                                                         Precounter_OVERLOW_SET           |   \
                                                         Precounter_UNDERFLOW_NO_CHANGE)
#define Precounter_PWM_MODE_RIGHT                 (Precounter_CC_MATCH_SET          |   \
                                                         Precounter_OVERLOW_NO_CHANGE     |   \
                                                         Precounter_UNDERFLOW_CLEAR)
#define Precounter_PWM_MODE_ASYM                  (Precounter_CC_MATCH_INVERT       |   \
                                                         Precounter_OVERLOW_SET           |   \
                                                         Precounter_UNDERFLOW_CLEAR)

#if (Precounter_CY_TCPWM_V2)
    #if(Precounter_CY_TCPWM_4000)
        #define Precounter_PWM_MODE_CENTER                (Precounter_CC_MATCH_INVERT       |   \
                                                                 Precounter_OVERLOW_NO_CHANGE     |   \
                                                                 Precounter_UNDERFLOW_CLEAR)
    #else
        #define Precounter_PWM_MODE_CENTER                (Precounter_CC_MATCH_INVERT       |   \
                                                                 Precounter_OVERLOW_SET           |   \
                                                                 Precounter_UNDERFLOW_CLEAR)
    #endif /* (Precounter_CY_TCPWM_4000) */
#else
    #define Precounter_PWM_MODE_CENTER                (Precounter_CC_MATCH_INVERT       |   \
                                                             Precounter_OVERLOW_NO_CHANGE     |   \
                                                             Precounter_UNDERFLOW_CLEAR)
#endif /* (Precounter_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Precounter_CMD_CAPTURE                    (0u)
#define Precounter_CMD_RELOAD                     (8u)
#define Precounter_CMD_STOP                       (16u)
#define Precounter_CMD_START                      (24u)

/* Status */
#define Precounter_STATUS_DOWN                    (1u)
#define Precounter_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Precounter_Init(void);
void   Precounter_Enable(void);
void   Precounter_Start(void);
void   Precounter_Stop(void);

void   Precounter_SetMode(uint32 mode);
void   Precounter_SetCounterMode(uint32 counterMode);
void   Precounter_SetPWMMode(uint32 modeMask);
void   Precounter_SetQDMode(uint32 qdMode);

void   Precounter_SetPrescaler(uint32 prescaler);
void   Precounter_TriggerCommand(uint32 mask, uint32 command);
void   Precounter_SetOneShot(uint32 oneShotEnable);
uint32 Precounter_ReadStatus(void);

void   Precounter_SetPWMSyncKill(uint32 syncKillEnable);
void   Precounter_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Precounter_SetPWMDeadTime(uint32 deadTime);
void   Precounter_SetPWMInvert(uint32 mask);

void   Precounter_SetInterruptMode(uint32 interruptMask);
uint32 Precounter_GetInterruptSourceMasked(void);
uint32 Precounter_GetInterruptSource(void);
void   Precounter_ClearInterrupt(uint32 interruptMask);
void   Precounter_SetInterrupt(uint32 interruptMask);

void   Precounter_WriteCounter(uint32 count);
uint32 Precounter_ReadCounter(void);

uint32 Precounter_ReadCapture(void);
uint32 Precounter_ReadCaptureBuf(void);

void   Precounter_WritePeriod(uint32 period);
uint32 Precounter_ReadPeriod(void);
void   Precounter_WritePeriodBuf(uint32 periodBuf);
uint32 Precounter_ReadPeriodBuf(void);

void   Precounter_WriteCompare(uint32 compare);
uint32 Precounter_ReadCompare(void);
void   Precounter_WriteCompareBuf(uint32 compareBuf);
uint32 Precounter_ReadCompareBuf(void);

void   Precounter_SetPeriodSwap(uint32 swapEnable);
void   Precounter_SetCompareSwap(uint32 swapEnable);

void   Precounter_SetCaptureMode(uint32 triggerMode);
void   Precounter_SetReloadMode(uint32 triggerMode);
void   Precounter_SetStartMode(uint32 triggerMode);
void   Precounter_SetStopMode(uint32 triggerMode);
void   Precounter_SetCountMode(uint32 triggerMode);

void   Precounter_SaveConfig(void);
void   Precounter_RestoreConfig(void);
void   Precounter_Sleep(void);
void   Precounter_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Precounter_BLOCK_CONTROL_REG              (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Precounter_BLOCK_CONTROL_PTR              ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Precounter_COMMAND_REG                    (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Precounter_COMMAND_PTR                    ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Precounter_INTRRUPT_CAUSE_REG             (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Precounter_INTRRUPT_CAUSE_PTR             ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Precounter_CONTROL_REG                    (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__CTRL )
#define Precounter_CONTROL_PTR                    ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__CTRL )
#define Precounter_STATUS_REG                     (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__STATUS )
#define Precounter_STATUS_PTR                     ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__STATUS )
#define Precounter_COUNTER_REG                    (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__COUNTER )
#define Precounter_COUNTER_PTR                    ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__COUNTER )
#define Precounter_COMP_CAP_REG                   (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__CC )
#define Precounter_COMP_CAP_PTR                   ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__CC )
#define Precounter_COMP_CAP_BUF_REG               (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__CC_BUFF )
#define Precounter_COMP_CAP_BUF_PTR               ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__CC_BUFF )
#define Precounter_PERIOD_REG                     (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__PERIOD )
#define Precounter_PERIOD_PTR                     ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__PERIOD )
#define Precounter_PERIOD_BUF_REG                 (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Precounter_PERIOD_BUF_PTR                 ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Precounter_TRIG_CONTROL0_REG              (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Precounter_TRIG_CONTROL0_PTR              ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Precounter_TRIG_CONTROL1_REG              (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Precounter_TRIG_CONTROL1_PTR              ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Precounter_TRIG_CONTROL2_REG              (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Precounter_TRIG_CONTROL2_PTR              ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Precounter_INTERRUPT_REQ_REG              (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__INTR )
#define Precounter_INTERRUPT_REQ_PTR              ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__INTR )
#define Precounter_INTERRUPT_SET_REG              (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__INTR_SET )
#define Precounter_INTERRUPT_SET_PTR              ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__INTR_SET )
#define Precounter_INTERRUPT_MASK_REG             (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__INTR_MASK )
#define Precounter_INTERRUPT_MASK_PTR             ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__INTR_MASK )
#define Precounter_INTERRUPT_MASKED_REG           (*(reg32 *) Precounter_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Precounter_INTERRUPT_MASKED_PTR           ( (reg32 *) Precounter_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Precounter_MASK                           ((uint32)Precounter_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Precounter_RELOAD_CC_SHIFT                (0u)
#define Precounter_RELOAD_PERIOD_SHIFT            (1u)
#define Precounter_PWM_SYNC_KILL_SHIFT            (2u)
#define Precounter_PWM_STOP_KILL_SHIFT            (3u)
#define Precounter_PRESCALER_SHIFT                (8u)
#define Precounter_UPDOWN_SHIFT                   (16u)
#define Precounter_ONESHOT_SHIFT                  (18u)
#define Precounter_QUAD_MODE_SHIFT                (20u)
#define Precounter_INV_OUT_SHIFT                  (20u)
#define Precounter_INV_COMPL_OUT_SHIFT            (21u)
#define Precounter_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Precounter_RELOAD_CC_MASK                 ((uint32)(Precounter_1BIT_MASK        <<  \
                                                                            Precounter_RELOAD_CC_SHIFT))
#define Precounter_RELOAD_PERIOD_MASK             ((uint32)(Precounter_1BIT_MASK        <<  \
                                                                            Precounter_RELOAD_PERIOD_SHIFT))
#define Precounter_PWM_SYNC_KILL_MASK             ((uint32)(Precounter_1BIT_MASK        <<  \
                                                                            Precounter_PWM_SYNC_KILL_SHIFT))
#define Precounter_PWM_STOP_KILL_MASK             ((uint32)(Precounter_1BIT_MASK        <<  \
                                                                            Precounter_PWM_STOP_KILL_SHIFT))
#define Precounter_PRESCALER_MASK                 ((uint32)(Precounter_8BIT_MASK        <<  \
                                                                            Precounter_PRESCALER_SHIFT))
#define Precounter_UPDOWN_MASK                    ((uint32)(Precounter_2BIT_MASK        <<  \
                                                                            Precounter_UPDOWN_SHIFT))
#define Precounter_ONESHOT_MASK                   ((uint32)(Precounter_1BIT_MASK        <<  \
                                                                            Precounter_ONESHOT_SHIFT))
#define Precounter_QUAD_MODE_MASK                 ((uint32)(Precounter_3BIT_MASK        <<  \
                                                                            Precounter_QUAD_MODE_SHIFT))
#define Precounter_INV_OUT_MASK                   ((uint32)(Precounter_2BIT_MASK        <<  \
                                                                            Precounter_INV_OUT_SHIFT))
#define Precounter_MODE_MASK                      ((uint32)(Precounter_3BIT_MASK        <<  \
                                                                            Precounter_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Precounter_CAPTURE_SHIFT                  (0u)
#define Precounter_COUNT_SHIFT                    (2u)
#define Precounter_RELOAD_SHIFT                   (4u)
#define Precounter_STOP_SHIFT                     (6u)
#define Precounter_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Precounter_CAPTURE_MASK                   ((uint32)(Precounter_2BIT_MASK        <<  \
                                                                  Precounter_CAPTURE_SHIFT))
#define Precounter_COUNT_MASK                     ((uint32)(Precounter_2BIT_MASK        <<  \
                                                                  Precounter_COUNT_SHIFT))
#define Precounter_RELOAD_MASK                    ((uint32)(Precounter_2BIT_MASK        <<  \
                                                                  Precounter_RELOAD_SHIFT))
#define Precounter_STOP_MASK                      ((uint32)(Precounter_2BIT_MASK        <<  \
                                                                  Precounter_STOP_SHIFT))
#define Precounter_START_MASK                     ((uint32)(Precounter_2BIT_MASK        <<  \
                                                                  Precounter_START_SHIFT))

/* MASK */
#define Precounter_1BIT_MASK                      ((uint32)0x01u)
#define Precounter_2BIT_MASK                      ((uint32)0x03u)
#define Precounter_3BIT_MASK                      ((uint32)0x07u)
#define Precounter_6BIT_MASK                      ((uint32)0x3Fu)
#define Precounter_8BIT_MASK                      ((uint32)0xFFu)
#define Precounter_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Precounter_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Precounter_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Precounter_QUAD_ENCODING_MODES     << Precounter_QUAD_MODE_SHIFT))       |\
         ((uint32)(Precounter_CONFIG                  << Precounter_MODE_SHIFT)))

#define Precounter_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Precounter_PWM_STOP_EVENT          << Precounter_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Precounter_PWM_OUT_INVERT          << Precounter_INV_OUT_SHIFT))         |\
         ((uint32)(Precounter_PWM_OUT_N_INVERT        << Precounter_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Precounter_PWM_MODE                << Precounter_MODE_SHIFT)))

#define Precounter_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Precounter_PWM_RUN_MODE         << Precounter_ONESHOT_SHIFT))
            
#define Precounter_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Precounter_PWM_ALIGN            << Precounter_UPDOWN_SHIFT))

#define Precounter_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Precounter_PWM_KILL_EVENT      << Precounter_PWM_SYNC_KILL_SHIFT))

#define Precounter_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Precounter_PWM_DEAD_TIME_CYCLE  << Precounter_PRESCALER_SHIFT))

#define Precounter_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Precounter_PWM_PRESCALER        << Precounter_PRESCALER_SHIFT))

#define Precounter_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Precounter_TC_PRESCALER            << Precounter_PRESCALER_SHIFT))       |\
         ((uint32)(Precounter_TC_COUNTER_MODE         << Precounter_UPDOWN_SHIFT))          |\
         ((uint32)(Precounter_TC_RUN_MODE             << Precounter_ONESHOT_SHIFT))         |\
         ((uint32)(Precounter_TC_COMP_CAP_MODE        << Precounter_MODE_SHIFT)))
        
#define Precounter_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Precounter_QUAD_PHIA_SIGNAL_MODE   << Precounter_COUNT_SHIFT))           |\
         ((uint32)(Precounter_QUAD_INDEX_SIGNAL_MODE  << Precounter_RELOAD_SHIFT))          |\
         ((uint32)(Precounter_QUAD_STOP_SIGNAL_MODE   << Precounter_STOP_SHIFT))            |\
         ((uint32)(Precounter_QUAD_PHIB_SIGNAL_MODE   << Precounter_START_SHIFT)))

#define Precounter_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Precounter_PWM_SWITCH_SIGNAL_MODE  << Precounter_CAPTURE_SHIFT))         |\
         ((uint32)(Precounter_PWM_COUNT_SIGNAL_MODE   << Precounter_COUNT_SHIFT))           |\
         ((uint32)(Precounter_PWM_RELOAD_SIGNAL_MODE  << Precounter_RELOAD_SHIFT))          |\
         ((uint32)(Precounter_PWM_STOP_SIGNAL_MODE    << Precounter_STOP_SHIFT))            |\
         ((uint32)(Precounter_PWM_START_SIGNAL_MODE   << Precounter_START_SHIFT)))

#define Precounter_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Precounter_TC_CAPTURE_SIGNAL_MODE  << Precounter_CAPTURE_SHIFT))         |\
         ((uint32)(Precounter_TC_COUNT_SIGNAL_MODE    << Precounter_COUNT_SHIFT))           |\
         ((uint32)(Precounter_TC_RELOAD_SIGNAL_MODE   << Precounter_RELOAD_SHIFT))          |\
         ((uint32)(Precounter_TC_STOP_SIGNAL_MODE     << Precounter_STOP_SHIFT))            |\
         ((uint32)(Precounter_TC_START_SIGNAL_MODE    << Precounter_START_SHIFT)))
        
#define Precounter_TIMER_UPDOWN_CNT_USED                                                          \
                ((Precounter__COUNT_UPDOWN0 == Precounter_TC_COUNTER_MODE)                  ||\
                 (Precounter__COUNT_UPDOWN1 == Precounter_TC_COUNTER_MODE))

#define Precounter_PWM_UPDOWN_CNT_USED                                                            \
                ((Precounter__CENTER == Precounter_PWM_ALIGN)                               ||\
                 (Precounter__ASYMMETRIC == Precounter_PWM_ALIGN))               
        
#define Precounter_PWM_PR_INIT_VALUE              (1u)
#define Precounter_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Precounter_H */

/* [] END OF FILE */
