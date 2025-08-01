/*******************************************************************************
* File Name: A2D.h
* Version 2.50
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Sequencing Successive Approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ADC_SAR_SEQ_A2D_H)
#define CY_ADC_SAR_SEQ_A2D_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint32 dftRegVal;
} A2D_BACKUP_STRUCT;


/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Clock Source setting constants */
#define A2D__EXTERNAL 0
#define A2D__INTERNAL 1

/*  Sample Mode setting constants */
#define A2D__FREERUNNING 0
#define A2D__HARDWARESOC 1

/*  Reference type setting constants */
#define A2D__VDDA_2 0
#define A2D__VDDA 1
#define A2D__INTERNAL1024 2
#define A2D__INTERNAL1024BYPASSED 3
#define A2D__INTERNALVREF 4
#define A2D__INTERNALVREFBYPASSED 5
#define A2D__VDDA_2BYPASSED 6
#define A2D__EXTERNALVREF 7

/* Input buffer gain setting constants */
#define A2D__DISABLED 0
#define A2D__ONE 1
#define A2D__TWO 2
#define A2D__FOUR 3
#define A2D__EIGHT 4
#define A2D__SIXTEEN 5

/* Negative input setting sonstants in single ended mode */
#define A2D__VSS 0
#define A2D__VREF 1
#define A2D__OTHER 2

/* Compare mode setting constants:
*    Mode0 - Disable
*    Mode1 - Result < Low_Limit
*    Mode2 - Low_Limit <= Result < High_Limit
*    Mode3 - High_Limit <= Result
*    Mode4 - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define A2D__MODE0 0
#define A2D__MODE1 1
#define A2D__MODE2 2
#define A2D__MODE3 3

#define A2D__RES8 0
#define A2D__RES10 1

#define A2D__RIGHT 0
#define A2D__LEFT 1

#define A2D__FSIGNED 1
#define A2D__FUNSIGNED 0

#define A2D__ACCUMULATE 0
#define A2D__FIXEDRESOLUTION 1



/***************************************
*   Conditional Compilation Parameters
****************************************/ 

#define A2D_CY_SAR_IP_VER0               	(0u)
#define A2D_CY_SAR_IP_VER1               	(1u)

#if (CY_PSOC4_4100 || CY_PSOC4_4200)
    #define A2D_CY_SAR_IP_VER              (A2D_CY_SAR_IP_VER0)
#else /* Other devices */
    #define A2D_CY_SAR_IP_VER              (A2D_CY_SAR_IP_VER1)
#endif  /* (CY_PSOC4_4100 || CY_PSOC4_4200) */


/***************************************
*    Initial Parameter Constants
***************************************/
#define A2D_DEFAULT_SAMPLE_MODE_SEL        (0u)
#define A2D_DEFAULT_VREF_SEL               (1u)
#define A2D_DEFAULT_NEG_INPUT_SEL          (0u)
#define A2D_DEFAULT_ALT_RESOLUTION_SEL     (0u)
#define A2D_DEFAULT_JUSTIFICATION_SEL      (0u)
#define A2D_DEFAULT_DIFF_RESULT_FORMAT_SEL (0u)
#define A2D_DEFAULT_SE_RESULT_FORMAT_SEL   (1u)
#define A2D_DEFAULT_CLOCK_SOURCE           (1u)
#define A2D_DEFAULT_VREF_MV_VALUE          (3300)
#define A2D_DEFAULT_BUFFER_GAIN            (0u)
#define A2D_DEFAULT_AVG_SAMPLES_NUM        (6u)
#define A2D_DEFAULT_AVG_SAMPLES_DIV        (6u < 4u) ? (int16)(0x100u >> (7u - 6u)) : (int16)(0x100u >> 4u)
#define A2D_DEFAULT_AVG_MODE               (1u)
#define A2D_MAX_RESOLUTION                 (12u)
#define A2D_DEFAULT_LOW_LIMIT              (2048u)
#define A2D_DEFAULT_HIGH_LIMIT             (2047u)
#define A2D_DEFAULT_COMPARE_MODE           (0u)
#define A2D_DEFAULT_ACLKS_NUM              (4u)
#define A2D_DEFAULT_BCLKS_NUM              (4u)
#define A2D_DEFAULT_CCLKS_NUM              (4u)
#define A2D_DEFAULT_DCLKS_NUM              (4u)
#define A2D_TOTAL_CHANNELS_NUM             (4u)
#define A2D_SEQUENCED_CHANNELS_NUM         (4u)
#define A2D_DEFAULT_EN_CHANNELS            (15u)
#define A2D_NOMINAL_CLOCK_FREQ             (1000000)
#define A2D_INJ_CHANNEL_ENABLED            (0u)
#define A2D_IRQ_REMOVE                     (0u)

/* Determines whether the configuration contains external negative input. */
#define A2D_SINGLE_PRESENT                 (0u)
#define A2D_CHANNELS_MODE                  (0u)
#define A2D_MAX_CHANNELS_EN_MASK           (0xffffu >> (16u - A2D_SEQUENCED_CHANNELS_NUM))


/***************************************
*        Function Prototypes
***************************************/

void A2D_Start(void);
void A2D_Stop(void);
void A2D_Init(void);
void A2D_Enable(void);
void A2D_StartConvert(void);
void A2D_StopConvert(void);
uint32 A2D_IsEndConversion(uint32 retMode);
int16 A2D_GetResult16(uint32 chan);
void A2D_SetChanMask(uint32 mask);
void A2D_SetLowLimit(uint32 lowLimit);
void A2D_SetHighLimit(uint32 highLimit);
void A2D_SetLimitMask(uint32 mask);
void A2D_SetSatMask(uint32 mask);
void A2D_SetOffset(uint32 chan, int16 offset);
void A2D_SetGain(uint32 chan, int32 adcGain);
#if(A2D_INJ_CHANNEL_ENABLED)
    void A2D_EnableInjection(void);
#endif /* A2D_INJ_CHANNEL_ENABLED */
#if(A2D_DEFAULT_JUSTIFICATION_SEL == A2D__RIGHT)
    int16 A2D_CountsTo_mVolts(uint32 chan, int16 adcCounts);
    int32 A2D_CountsTo_uVolts(uint32 chan, int16 adcCounts);
    float32 A2D_CountsTo_Volts(uint32 chan, int16 adcCounts);
#endif /* End A2D_DEFAULT_JUSTIFICATION_SEL == A2D__RIGHT */
void A2D_Sleep(void);
void A2D_Wakeup(void);
void A2D_SaveConfig(void);
void A2D_RestoreConfig(void);

CY_ISR_PROTO( A2D_ISR );


/**************************************
*           API Constants
**************************************/
/* Constants for Sleep mode states */
#define A2D_DISABLED                   (0x00u)
#define A2D_ENABLED                    (0x01u)
#define A2D_STARTED                    (0x02u)
#define A2D_BOOSTPUMP_ENABLED          (0x04u)

/*   Constants for IsEndConversion() "retMode" parameter  */
#define A2D_RETURN_STATUS              (0x01u)
#define A2D_WAIT_FOR_RESULT            (0x02u)
#define A2D_RETURN_STATUS_INJ          (0x04u)
#define A2D_WAIT_FOR_RESULT_INJ        (0x08u)

#define A2D_MAX_FREQUENCY              (18000000)       /*18Mhz*/

#define A2D_RESOLUTION_12              (12u)
#define A2D_RESOLUTION_10              (10u)
#define A2D_RESOLUTION_8               (8u)

#define A2D_10US_DELAY                 (10u)

#define A2D_10V_COUNTS                 (10.0F)
#define A2D_10MV_COUNTS                (10000)
#define A2D_10UV_COUNTS                (10000000L)


/***************************************
* Global variables external identifier
***************************************/

extern uint8 A2D_initVar;
extern volatile int16 A2D_offset[A2D_TOTAL_CHANNELS_NUM];
extern volatile int32 A2D_countsPer10Volt[A2D_TOTAL_CHANNELS_NUM];


/***************************************
*              Registers
***************************************/

#define A2D_SAR_CTRL_REG                (*(reg32 *) A2D_cy_psoc4_sar__SAR_CTRL )
#define A2D_SAR_CTRL_PTR                ( (reg32 *) A2D_cy_psoc4_sar__SAR_CTRL )

#define A2D_SAR_SAMPLE_CTRL_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_SAMPLE_CTRL )
#define A2D_SAR_SAMPLE_CTRL_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_SAMPLE_CTRL )

#define A2D_SAR_SAMPLE_TIME01_REG       (*(reg32 *) A2D_cy_psoc4_sar__SAR_SAMPLE_TIME01 )
#define A2D_SAR_SAMPLE_TIME01_PTR       ( (reg32 *) A2D_cy_psoc4_sar__SAR_SAMPLE_TIME01 )

#define A2D_SAR_SAMPLE_TIME23_REG       (*(reg32 *) A2D_cy_psoc4_sar__SAR_SAMPLE_TIME23 )
#define A2D_SAR_SAMPLE_TIME23_PTR       ( (reg32 *) A2D_cy_psoc4_sar__SAR_SAMPLE_TIME23 )

#define A2D_SAR_RANGE_THRES_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_THRES )
#define A2D_SAR_RANGE_THRES_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_THRES )

#define A2D_SAR_RANGE_COND_REG          (*(reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_COND )
#define A2D_SAR_RANGE_COND_PTR          ( (reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_COND )

#define A2D_SAR_CHAN_EN_REG             (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_EN )
#define A2D_SAR_CHAN_EN_PTR             ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_EN )

#define A2D_SAR_START_CTRL_REG          (*(reg32 *) A2D_cy_psoc4_sar__SAR_START_CTRL )
#define A2D_SAR_START_CTRL_PTR          ( (reg32 *) A2D_cy_psoc4_sar__SAR_START_CTRL )

#define A2D_SAR_DFT_CTRL_REG            (*(reg32 *) A2D_cy_psoc4_sar__SAR_DFT_CTRL )
#define A2D_SAR_DFT_CTRL_PTR            ( (reg32 *) A2D_cy_psoc4_sar__SAR_DFT_CTRL )

#define A2D_SAR_CHAN_CONFIG_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_CONFIG00 )
#define A2D_SAR_CHAN_CONFIG_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_CONFIG00 )
#define A2D_SAR_CHAN_CONFIG_IND         A2D_cy_psoc4_sar__SAR_CHAN_CONFIG00

#define A2D_SAR_CHAN_WORK_REG           (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_WORK00 )
#define A2D_SAR_CHAN_WORK_PTR           ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_WORK00 )

#define A2D_SAR_CHAN_RESULT_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define A2D_SAR_CHAN_RESULT_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define A2D_SAR_CHAN_RESULT_IND         A2D_cy_psoc4_sar__SAR_CHAN_RESULT00

#define A2D_SAR_CHAN0_RESULT_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define A2D_SAR_CHAN0_RESULT_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT00 )

#define A2D_SAR_CHAN1_RESULT_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT01 )
#define A2D_SAR_CHAN1_RESULT_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT01 )

#define A2D_SAR_CHAN2_RESULT_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT02 )
#define A2D_SAR_CHAN2_RESULT_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT02 )

#define A2D_SAR_CHAN3_RESULT_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT03 )
#define A2D_SAR_CHAN3_RESULT_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT03 )

#define A2D_SAR_CHAN4_RESULT_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT04 )
#define A2D_SAR_CHAN4_RESULT_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT04 )

#define A2D_SAR_CHAN5_RESULT_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT05 )
#define A2D_SAR_CHAN5_RESULT_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT05 )

#define A2D_SAR_CHAN6_RESULT_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT06 )
#define A2D_SAR_CHAN6_RESULT_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT06 )

#define A2D_SAR_CHAN7_RESULT_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT07 )
#define A2D_SAR_CHAN7_RESULT_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT07 )

#if(A2D_CY_SAR_IP_VER != A2D_CY_SAR_IP_VER0)
    #define A2D_SAR_CHAN8_RESULT_REG     (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT08 )
    #define A2D_SAR_CHAN8_RESULT_PTR     ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT08 )

    #define A2D_SAR_CHAN9_RESULT_REG     (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT09 )
    #define A2D_SAR_CHAN9_RESULT_PTR     ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT09 )

    #define A2D_SAR_CHAN10_RESULT_REG    (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT10 )
    #define A2D_SAR_CHAN10_RESULT_PTR    ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT10 )

    #define A2D_SAR_CHAN11_RESULT_REG    (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT11 )
    #define A2D_SAR_CHAN11_RESULT_PTR    ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT11 )

    #define A2D_SAR_CHAN12_RESULT_REG    (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT12 )
    #define A2D_SAR_CHAN12_RESULT_PTR    ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT12 )

    #define A2D_SAR_CHAN13_RESULT_REG    (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT13 )
    #define A2D_SAR_CHAN13_RESULT_PTR    ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT13 )

    #define A2D_SAR_CHAN14_RESULT_REG    (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT14 )
    #define A2D_SAR_CHAN14_RESULT_PTR    ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT14 )

    #define A2D_SAR_CHAN15_RESULT_REG    (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT15 )
    #define A2D_SAR_CHAN15_RESULT_PTR    ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT15 )
#endif /* (A2D_CY_SAR_IP_VER != A2D_CY_SAR_IP_VER0) */

#define A2D_SAR_CHAN_WORK_VALID_REG     (*(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_WORK_VALID)
#define A2D_SAR_CHAN_WORK_VALID_PTR     ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_WORK_VALID)

#define A2D_SAR_CHAN_RESULT_VALID_REG  ( *(reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT_VALID )
#define A2D_SAR_CHAN_RESULT_VALID_PTR  ( (reg32 *) A2D_cy_psoc4_sar__SAR_CHAN_RESULT_VALID )

#define A2D_SAR_STATUS_REG              (*(reg32 *) A2D_cy_psoc4_sar__SAR_STATUS )
#define A2D_SAR_STATUS_PTR              ( (reg32 *) A2D_cy_psoc4_sar__SAR_STATUS )

#define A2D_SAR_AVG_START_REG           (*(reg32 *) A2D_cy_psoc4_sar__SAR_AVG_STAT )
#define A2D_SAR_AVG_START_PTR           ( (reg32 *) A2D_cy_psoc4_sar__SAR_AVG_STAT )

#define A2D_SAR_INTR_REG                (*(reg32 *) A2D_cy_psoc4_sar__SAR_INTR )
#define A2D_SAR_INTR_PTR                ( (reg32 *) A2D_cy_psoc4_sar__SAR_INTR )

#define A2D_SAR_INTR_SET_REG            (*(reg32 *) A2D_cy_psoc4_sar__SAR_INTR_SET )
#define A2D_SAR_INTR_SET_PTR            ( (reg32 *) A2D_cy_psoc4_sar__SAR_INTR_SET )

#define A2D_SAR_INTR_MASK_REG           (*(reg32 *) A2D_cy_psoc4_sar__SAR_INTR_MASK )
#define A2D_SAR_INTR_MASK_PTR           ( (reg32 *) A2D_cy_psoc4_sar__SAR_INTR_MASK )

#define A2D_SAR_INTR_MASKED_REG         (*(reg32 *) A2D_cy_psoc4_sar__SAR_INTR_MASKED )
#define A2D_SAR_INTR_MASKED_PTR         ( (reg32 *) A2D_cy_psoc4_sar__SAR_INTR_MASKED )

#define A2D_SAR_SATURATE_INTR_REG       (*(reg32 *) A2D_cy_psoc4_sar__SAR_SATURATE_INTR )
#define A2D_SAR_SATURATE_INTR_PTR       ( (reg32 *) A2D_cy_psoc4_sar__SAR_SATURATE_INTR )

#define A2D_SAR_SATURATE_INTR_SET_REG   (*(reg32 *) A2D_cy_psoc4_sar__SAR_SATURATE_INTR_SET )
#define A2D_SAR_SATURATE_INTR_SET_PTR   ( (reg32 *) A2D_cy_psoc4_sar__SAR_SATURATE_INTR_SET )

#define A2D_SAR_SATURATE_INTR_MASK_REG (*(reg32 *) A2D_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )
#define A2D_SAR_SATURATE_INTR_MASK_PTR ( (reg32 *) A2D_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )

#define A2D_SAR_SATURATE_INTR_MASKED_REG \
                                                 (*(reg32 *) A2D_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )
#define A2D_SAR_SATURATE_INTR_MASKED_PTR \
                                                 ( (reg32 *) A2D_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )

#define A2D_SAR_RANGE_INTR_REG          (*(reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_INTR )
#define A2D_SAR_RANGE_INTR_PTR          ( (reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_INTR )

#define A2D_SAR_RANGE_INTR_SET_REG      (*(reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_INTR_SET )
#define A2D_SAR_RANGE_INTR_SET_PTR      ( (reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_INTR_SET )

#define A2D_SAR_RANGE_INTR_MASK_REG     (*(reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_INTR_MASK )
#define A2D_SAR_RANGE_INTR_MASK_PTR     ( (reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_INTR_MASK )

#define A2D_SAR_RANGE_INTR_MASKED_REG   (*(reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )
#define A2D_SAR_RANGE_INTR_MASKED_PTR   ( (reg32 *) A2D_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )

#define A2D_SAR_INTR_CAUSE_REG          (*(reg32 *) A2D_cy_psoc4_sar__SAR_INTR_CAUSE )
#define A2D_SAR_INTR_CAUSE_PTR          ( (reg32 *) A2D_cy_psoc4_sar__SAR_INTR_CAUSE )

#if(A2D_INJ_CHANNEL_ENABLED)
    #define A2D_SAR_INJ_CHAN_CONFIG_REG \
                                                 (*(reg32 *) A2D_cy_psoc4_sarmux_8__SAR_INJ_CHAN_CONFIG )
    #define A2D_SAR_INJ_CHAN_CONFIG_PTR    \
                                                 ( (reg32 *) A2D_cy_psoc4_sarmux_8__SAR_INJ_CHAN_CONFIG )

    #define A2D_SAR_INJ_RESULT_REG    (*(reg32 *) A2D_cy_psoc4_sarmux_8__SAR_INJ_RESULT )
    #define A2D_SAR_INJ_RESULT_PTR    ( (reg32 *) A2D_cy_psoc4_sarmux_8__SAR_INJ_RESULT )
#endif /* A2D_INJ_CHANNEL_ENABLED */
    
#define A2D_MUX_SWITCH0_REG           (*(reg32 *)  A2D_cy_psoc4_sar__SAR_MUX_SWITCH0 )
#define A2D_MUX_SWITCH0_PTR           ( (reg32 *)  A2D_cy_psoc4_sar__SAR_MUX_SWITCH0 )

#define A2D_MUX_SWITCH_HW_CTRL_REG    (*(reg32 *)  A2D_cy_psoc4_sar__SAR_MUX_SWITCH_HW_CTRL )
#define A2D_MUX_SWITCH_HW_CTRL_PTR    ( (reg32 *)  A2D_cy_psoc4_sar__SAR_MUX_SWITCH_HW_CTRL )

#define A2D_PUMP_CTRL_REG             (*(reg32 *)  A2D_cy_psoc4_sar__SAR_PUMP_CTRL )
#define A2D_PUMP_CTRL_PTR             ( (reg32 *)  A2D_cy_psoc4_sar__SAR_PUMP_CTRL )

#define A2D_ANA_TRIM_REG              (*(reg32 *)  A2D_cy_psoc4_sar__SAR_ANA_TRIM )
#define A2D_ANA_TRIM_PTR              ( (reg32 *)  A2D_cy_psoc4_sar__SAR_ANA_TRIM )

#define A2D_WOUNDING_REG              (*(reg32 *)  A2D_cy_psoc4_sar__SAR_WOUNDING )
#define A2D_WOUNDING_PTR              ( (reg32 *)  A2D_cy_psoc4_sar__SAR_WOUNDING )


/**************************************
*       Register Constants
**************************************/
#define A2D_INTC_NUMBER                (A2D_IRQ__INTC_NUMBER)
#define A2D_INTC_PRIOR_NUMBER          (A2D_IRQ__INTC_PRIOR_NUM)

/* defines for CTRL register */
#define A2D_VREF_INTERNAL1024          (0x00000040Lu)
#define A2D_VREF_EXTERNAL              (0x00000050Lu)
#define A2D_VREF_VDDA_2                (0x00000060Lu)
#define A2D_VREF_VDDA                  (0x00000070Lu)
#define A2D_VREF_INTERNAL1024BYPASSED  (0x000000C0Lu)
#define A2D_VREF_VDDA_2BYPASSED        (0x000000E0Lu)
#define A2D_VREF_INTERNALVREF          (0x00000040Lu)
#define A2D_VREF_INTERNALVREFBYPASSED  (0x000000C0Lu)

#define A2D_NEG_VSSA_KELVIN            (0x00000000Lu)
#define A2D_NEG_VSSA                   (0x00000200Lu)
#define A2D_NEG_VREF                   (0x00000E00Lu)
#if(A2D_TOTAL_CHANNELS_NUM > 1u)
    #define A2D_NEG_OTHER              (uint16)((uint16)A2D_cy_psoc4_sarmux_8__VNEG0 << 9u)
#else
    #define A2D_NEG_OTHER              (0)
#endif /* A2D_TOTAL_CHANNELS_NUM > 1u */

#define A2D_SAR_HW_CTRL_NEGVREF        (0x00002000Lu)

#define A2D_BOOSTPUMP_EN               (0x00100000Lu)

#define A2D_NORMAL_PWR                 (0x00000000Lu)
#define A2D_HALF_PWR                   (0x01000000Lu)
#define A2D_MORE_PWR                   (0x02000000Lu)
#define A2D_QUARTER_PWR                (0x03000000Lu)
#define A2D_DEEPSLEEP_ON               (0x08000000Lu)

#define A2D_DSI_SYNC_CONFIG            (0x10000000Lu)
#define A2D_DSI_MODE                   (0x20000000Lu)
#define A2D_SWITCH_DISABLE             (0x40000000Lu)
#define A2D_ENABLE                     (0x80000000Lu)

/* defines for STATUS register */
#define A2D_STATUS_BUSY                (0x80000000Lu)

/* defines for SAMPLE_CTRL register */
#define A2D_ALT_RESOLUTION_10BIT       (0x00000001Lu)
#define A2D_ALT_RESOLUTION_8BIT        (0x00000000Lu)

#define A2D_DATA_ALIGN_LEFT            (0x00000002Lu)
#define A2D_DATA_ALIGN_RIGHT           (0x00000000Lu)

#define A2D_SE_SIGNED_RESULT           (0x00000004Lu)
#define A2D_SE_UNSIGNED_RESULT         (0x00000000Lu)

#define A2D_DIFF_SIGNED_RESULT         (0x00000008Lu)
#define A2D_DIFF_UNSIGNED_RESULT       (0x00000000Lu)

#define A2D_AVG_CNT_OFFSET             (4u)
#define A2D_AVG_CNT_MASK               (0x00000070Lu)
#define A2D_AVG_SHIFT                  (0x00000080Lu)

#define A2D_CONTINUOUS_EN              (0x00010000Lu)
#define A2D_DSI_TRIGGER_EN             (0x00020000Lu)
#define A2D_DSI_TRIGGER_LEVEL          (0x00040000Lu)
#define A2D_DSI_SYNC_TRIGGER           (0x00080000Lu)
#define A2D_EOS_DSI_OUT_EN             (0x80000000Lu)

/* defines for SAMPLE_TIME01 / SAMPLE_TIME23 registers */
#define A2D_SAMPLE_TIME13_OFFSET       (16u)
#define A2D_SAMPLE_TIME02_MASK         (0x000003FFLu)
#define A2D_SAMPLE_TIME13_MASK         (0x03FF0000Lu)

/* defines for RANGE_THRES registers */
#define A2D_RANGE_HIGH_OFFSET          (16u)
#define A2D_RANGE_HIGH_MASK            (0xFFFF0000Lu)
#define A2D_RANGE_LOW_MASK             (0x0000FFFFLu)

/* defines for RANGE_COND register */
/* Compare mode setting constants:
*    BELOW   - Result < Low_Limit
*    INSIDE  - Low_Limit <= Result < High_Limit
*    ABOVE   - High_Limit <= Result
*    OUTSIDE - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define A2D_CMP_MODE_BELOW             (0x00000000Lu)
#define A2D_CMP_MODE_INSIDE            (0x40000000Lu)
#define A2D_CMP_MODE_ABOVE             (0x80000000Lu)
#define A2D_CMP_MODE_OUTSIDE           (0xC0000000Lu)
#define A2D_CMP_OFFSET                 (30u)

/* defines for _START_CTRL register */
#define A2D_FW_TRIGGER                 (0x00000001Lu)

/* defines for DFT_CTRL register */
#define A2D_DLY_INC                    (0x00000001Lu)
#define A2D_HIZ                        (0x00000002Lu)
#define A2D_DFT_INC_MASK               (0x000F0000Lu)
#define A2D_DFT_OUTC_MASK              (0x00700000Lu)
#define A2D_SEL_CSEL_DFT_MASK          (0x0F000000Lu)

/* configuration for clock speed > 9 Mhz based on
* characterization results
*/
#define A2D_SEL_CSEL_DFT_CHAR          (0x03000000Lu)
#define A2D_EN_CSEL_DFT                (0x10000000Lu)
#define A2D_DCEN                       (0x20000000Lu)
#define A2D_ADFT_OVERRIDE              (0x80000000Lu)

/* defines for CHAN_CONFIG / DIE_CHAN_CONFIG register
*  and channelsConfig parameter
*/
#define A2D_SARMUX_VIRT_SELECT         (0x00000070Lu)
#define A2D_DIFFERENTIAL_EN            (0x00000100Lu)
#define A2D_ALT_RESOLUTION_ON          (0x00000200Lu)
#define A2D_AVERAGING_EN               (0x00000400Lu)

#define A2D_SAMPLE_TIME_SEL_SHIFT      (12u)
#define A2D_SAMPLE_TIME_SEL_MASK       (0x00003000Lu)

#define A2D_CHANNEL_CONFIG_MASK        (0x00003700Lu)

/* for CHAN_CONFIG only */
#define A2D_DSI_OUT_EN                 (0x80000000Lu)

/* for INJ_CHAN_CONFIG only */
#define A2D_INJ_TAILGATING             (0x40000000Lu)
#define A2D_INJ_CHAN_EN                (0x80000000Lu)

/* defines for CHAN_WORK register */
#define A2D_SAR_WRK_MAX_12BIT          (0x00001000Lu)
#define A2D_SAR_WRK_MAX_10BIT          (0x00000400Lu)
#define A2D_SAR_WRK_MAX_8BIT           (0x00000100Lu)

/* defines for CHAN_RESULT register */
#define A2D_RESULT_MASK                (0x0000FFFFLu)
#define A2D_SATURATE_INTR_MIR          (0x20000000Lu)
#define A2D_RANGE_INTR_MIR             (0x40000000Lu)
#define A2D_CHAN_RESULT_VALID_MIR      (0x80000000Lu)

/* defines for INTR_MASK register */
#define A2D_EOS_MASK                   (0x00000001Lu)
#define A2D_OVERFLOW_MASK              (0x00000002Lu)
#define A2D_FW_COLLISION_MASK          (0x00000004Lu)
#define A2D_DSI_COLLISION_MASK         (0x00000008Lu)
#define A2D_INJ_EOC_MASK               (0x00000010Lu)
#define A2D_INJ_SATURATE_MASK          (0x00000020Lu)
#define A2D_INJ_RANGE_MASK             (0x00000040Lu)
#define A2D_INJ_COLLISION_MASK         (0x00000080Lu)

/* defines for INJ_RESULT register */
#define A2D_INJ_COLLISION_INTR_MIR     (0x10000000Lu)
#define A2D_INJ_SATURATE_INTR_MIR      (0x20000000Lu)
#define A2D_INJ_RANGE_INTR_MIR         (0x40000000Lu)
#define A2D_INJ_EOC_INTR_MIR           (0x80000000Lu)

/* defines for MUX_SWITCH0 register */
#define A2D_MUX_FW_VSSA_VMINUS         (0x00010000Lu)

/* defines for PUMP_CTRL register */
#define A2D_PUMP_CTRL_ENABLED          (0x80000000Lu)

/* additional defines for channelsConfig parameter */
#define A2D_IS_SATURATE_EN_MASK        (0x00000001Lu)
#define A2D_IS_RANGE_CTRL_EN_MASK      (0x00000002Lu)

/* defines for WOUNDING register */
#define A2D_WOUNDING_12BIT             (0x00000000Lu)
#define A2D_WOUNDING_10BIT             (0x00000001Lu)
#define A2D_WOUNDING_8BIT              (0x00000002Lu)

/* Trim value based on characterization */
#define A2D_TRIM_COEF                  (2u)

#if(A2D_MAX_RESOLUTION == A2D_RESOLUTION_10)
    #define A2D_ALT_WOUNDING           A2D_WOUNDING_10BIT
#else
    #define A2D_ALT_WOUNDING           A2D_WOUNDING_8BIT
#endif /* A2D_MAX_RESOLUTION == A2D_RESOLUTION_10 */

#if(A2D_DEFAULT_VREF_SEL == A2D__VDDA_2)
    #define A2D_DEFAULT_VREF_SOURCE    A2D_VREF_VDDA_2
#elif(A2D_DEFAULT_VREF_SEL == A2D__VDDA)
    #define A2D_DEFAULT_VREF_SOURCE    A2D_VREF_VDDA
#elif(A2D_DEFAULT_VREF_SEL == A2D__INTERNAL1024)
    #define A2D_DEFAULT_VREF_SOURCE    A2D_VREF_INTERNAL1024
#elif(A2D_DEFAULT_VREF_SEL == A2D__INTERNAL1024BYPASSED)
    #define A2D_DEFAULT_VREF_SOURCE    A2D_VREF_INTERNAL1024BYPASSED
#elif(A2D_DEFAULT_VREF_SEL == A2D__INTERNALVREF)
    #define A2D_DEFAULT_VREF_SOURCE    A2D_VREF_INTERNALVREF
#elif(A2D_DEFAULT_VREF_SEL == A2D__INTERNALVREFBYPASSED)
    #define A2D_DEFAULT_VREF_SOURCE    A2D_VREF_INTERNALVREFBYPASSED
#elif(A2D_DEFAULT_VREF_SEL == A2D__VDDA_2BYPASSED)
    #define A2D_DEFAULT_VREF_SOURCE    A2D_VREF_VDDA_2BYPASSED
#else
    #define A2D_DEFAULT_VREF_SOURCE    A2D_VREF_EXTERNAL
#endif /* A2D_DEFAULT_VREF_SEL == A2D__VDDA_2 */

#if(A2D_DEFAULT_NEG_INPUT_SEL == A2D__VSS)
    /* Connect NEG input of SARADC to VSSA close to the SARADC for single channel mode */
    #if(A2D_TOTAL_CHANNELS_NUM == 1u)
        #define A2D_DEFAULT_SE_NEG_INPUT    A2D_NEG_VSSA
    #else
        #define A2D_DEFAULT_SE_NEG_INPUT    A2D_NEG_VSSA_KELVIN
    #endif /* (A2D_TOTAL_CHANNELS_NUM == 1u) */
    /* Do not connect VSSA to VMINUS when one channel in differential mode used */
    #if((A2D_TOTAL_CHANNELS_NUM == 1u) && (A2D_CHANNELS_MODE != 0u))
        #define A2D_DEFAULT_MUX_SWITCH0     0u
    #else    /* miltiple channels or one single channel */
        #define A2D_DEFAULT_MUX_SWITCH0     A2D_MUX_FW_VSSA_VMINUS
    #endif /* (A2D_TOTAL_CHANNELS_NUM == 1u) */
#elif(A2D_DEFAULT_NEG_INPUT_SEL == A2D__VREF)
    /* Do not connect VNEG to VREF when one channel in differential mode used */
    #if((A2D_TOTAL_CHANNELS_NUM == 1u) && (A2D_CHANNELS_MODE != 0u))
        #define A2D_DEFAULT_SE_NEG_INPUT    0u
    #else    /* miltiple channels or one single channel */
        #define A2D_DEFAULT_SE_NEG_INPUT    A2D_NEG_VREF
    #endif /* (A2D_TOTAL_CHANNELS_NUM == 1u) */
    #define A2D_DEFAULT_MUX_SWITCH0     0u
#elif (A2D_SINGLE_PRESENT != 0u)
    #define A2D_DEFAULT_SE_NEG_INPUT    A2D_NEG_OTHER
    #define A2D_DEFAULT_MUX_SWITCH0     0u
#else
    #define A2D_DEFAULT_SE_NEG_INPUT    0u
    #define A2D_DEFAULT_MUX_SWITCH0     0u
#endif /* A2D_DEFAULT_NEG_INPUT_SEL == A2D__VREF */

/* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
#if(A2D_TOTAL_CHANNELS_NUM == 1u)
    #define A2D_DEFAULT_HW_CTRL_NEGVREF 0u
#else
    #define A2D_DEFAULT_HW_CTRL_NEGVREF A2D_SAR_HW_CTRL_NEGVREF
#endif /* (A2D_TOTAL_CHANNELS_NUM == 1u) */


#if(A2D_DEFAULT_ALT_RESOLUTION_SEL == A2D__RES8)
    #define A2D_DEFAULT_ALT_RESOLUTION     (A2D_ALT_RESOLUTION_8BIT)
    #define A2D_DEFAULT_MAX_WRK_ALT        (A2D_SAR_WRK_MAX_8BIT)
#else
    #define A2D_DEFAULT_ALT_RESOLUTION     (A2D_ALT_RESOLUTION_10BIT)
    #define A2D_DEFAULT_MAX_WRK_ALT        (A2D_SAR_WRK_MAX_10BIT)
#endif /* End A2D_DEFAULT_ALT_RESOLUTION_SEL == A2D__RES8 */

#if(A2D_DEFAULT_JUSTIFICATION_SEL == A2D__RIGHT)
    #define A2D_DEFAULT_JUSTIFICATION  A2D_DATA_ALIGN_RIGHT
#else
    #define A2D_DEFAULT_JUSTIFICATION  A2D_DATA_ALIGN_LEFT
#endif /* A2D_DEFAULT_JUSTIFICATION_SEL == A2D__RIGHT */

#if(A2D_DEFAULT_DIFF_RESULT_FORMAT_SEL == A2D__FSIGNED)
    #define A2D_DEFAULT_DIFF_RESULT_FORMAT A2D_DIFF_SIGNED_RESULT
#else
    #define A2D_DEFAULT_DIFF_RESULT_FORMAT A2D_DIFF_UNSIGNED_RESULT
#endif /* A2D_DEFAULT_DIFF_RESULT_FORMAT_SEL == A2D__FSIGNED */

#if(A2D_DEFAULT_SE_RESULT_FORMAT_SEL == A2D__FSIGNED)
    #define A2D_DEFAULT_SE_RESULT_FORMAT A2D_SE_SIGNED_RESULT
#else
    #define A2D_DEFAULT_SE_RESULT_FORMAT A2D_SE_UNSIGNED_RESULT
#endif /* A2D_DEFAULT_SE_RESULT_FORMAT_SEL == A2D__FSIGNED */

#if(A2D_DEFAULT_SAMPLE_MODE_SEL == A2D__FREERUNNING)
    #define A2D_DSI_TRIGGER        0u
#else /* Firmware trigger */
    #define A2D_DSI_TRIGGER        (A2D_DSI_TRIGGER_EN | A2D_DSI_SYNC_TRIGGER)
#endif /* End A2D_DEFAULT_SAMPLE_MODE == A2D__FREERUNNING */

#if(A2D_INJ_CHANNEL_ENABLED)
    #define A2D_SAR_INTR_MASK      (A2D_EOS_MASK | A2D_INJ_EOC_MASK)
#else
    #define A2D_SAR_INTR_MASK      (A2D_EOS_MASK)
#endif /* A2D_INJ_CHANNEL_ENABLED*/

#if(A2D_DEFAULT_AVG_MODE == A2D__FIXEDRESOLUTION)
    #define A2D_AVG_SHIFT_MODE     A2D_AVG_SHIFT
#else
    #define A2D_AVG_SHIFT_MODE     0u
#endif /* End A2D_DEFAULT_AVG_MODE */

#define A2D_COMPARE_MODE           (uint32)((uint32)(A2D_DEFAULT_COMPARE_MODE) \
                                                << A2D_CMP_OFFSET)

#if(A2D_TOTAL_CHANNELS_NUM > 1u)
    #define A2D_DEFAULT_SWITCH_CONF    0u
#else /* Disable SAR sequencer from enabling routing switches in single channel mode */
    #define A2D_DEFAULT_SWITCH_CONF    A2D_SWITCH_DISABLE
#endif /* End A2D_TOTAL_CHANNELS_NUM > 1 */

#define A2D_DEFAULT_POWER \
       ((A2D_NOMINAL_CLOCK_FREQ > (A2D_MAX_FREQUENCY / 4)) ? A2D_NORMAL_PWR : \
       ((A2D_NOMINAL_CLOCK_FREQ > (A2D_MAX_FREQUENCY / 8)) ? A2D_HALF_PWR : \
                                                                                       A2D_QUARTER_PWR))

#define A2D_DEFAULT_CTRL_REG_CFG       (A2D_DEFAULT_VREF_SOURCE \
                                                   | A2D_DEFAULT_SE_NEG_INPUT \
                                                   | A2D_DEFAULT_HW_CTRL_NEGVREF \
                                                   | A2D_DEFAULT_POWER \
                                                   | A2D_DSI_SYNC_CONFIG \
                                                   | A2D_DEFAULT_SWITCH_CONF)

#define A2D_DEFAULT_SAMPLE_CTRL_REG_CFG (A2D_DEFAULT_DIFF_RESULT_FORMAT \
                                                    | A2D_DEFAULT_SE_RESULT_FORMAT \
                                                    | A2D_DEFAULT_JUSTIFICATION \
                                                    | A2D_DEFAULT_ALT_RESOLUTION \
                                           | (uint8)(A2D_DEFAULT_AVG_SAMPLES_NUM \
                                                   << A2D_AVG_CNT_OFFSET) \
                                                    | A2D_AVG_SHIFT_MODE \
                                                    | A2D_DSI_TRIGGER \
                                                    | A2D_EOS_DSI_OUT_EN)

#define A2D_DEFAULT_RANGE_THRES_REG_CFG (A2D_DEFAULT_LOW_LIMIT \
            | (uint32)((uint32)A2D_DEFAULT_HIGH_LIMIT << A2D_RANGE_HIGH_OFFSET))

#define A2D_DEFAULT_SAMPLE_TIME01_REG_CFG (A2D_DEFAULT_ACLKS_NUM \
            | (uint32)((uint32)A2D_DEFAULT_BCLKS_NUM << A2D_SAMPLE_TIME13_OFFSET))

#define A2D_DEFAULT_SAMPLE_TIME23_REG_CFG (A2D_DEFAULT_CCLKS_NUM \
            | (uint32)((uint32)A2D_DEFAULT_DCLKS_NUM << A2D_SAMPLE_TIME13_OFFSET))


#endif /* End CY_ADC_SAR_SEQ_A2D_H */


/* [] END OF FILE */
