//==================================================================================================
//
// File name: adc.h
//
// Purpose:
//
//==================================================================================================
#ifndef _ADC_H_
#define _ADC_H_


//==================================================================================================
// Include directives
//==================================================================================================
#include "types.h"
#include "hw_cfg.h"
#include "register_macros.h"
#include "fifo.h"
#include "isr.h"

//==================================================================================================
// Preprocessor definitions
//==================================================================================================
#define ADC_NOF_CHANNELS                    (8U)

#define ADC_PRESCALER_2                     (0x01U)
#define ADC_PRESCALER_4                     (0x02U)
#define ADC_PRESCALER_8                     (0x03U)
#define ADC_PRESCALER_16                    (0x04U)
#define ADC_PRESCALER_32                    (0x05U)
#define ADC_PRESCALER_64                    (0x06U)
#define ADC_PRESCALER_128                   (0x07U)

#define ADC_REF_EXTERNAL                    (0x00U)
#define ADC_REF_VCC                         (0x01U)
#define ADC_REF_INTERNAL                    (0x04U)

#define ADC_AUTO_TRIGGER_SOURCE_NONE        (0x00U)
#define ADC_AUTO_TRIGGER_SOURCE_ACOMP       (0x01U)
#define ADC_AUTO_TRIGGER_SOURCE_EXT_INT0    (0x02U)
#define ADC_AUTO_TRIGGER_SOURCE_TIM0_COMPA  (0x03U)
#define ADC_AUTO_TRIGGER_SOURCE_TIM0_OVF    (0x04U)
#define ADC_AUTO_TRIGGER_SOURCE_TIM1_COMPB  (0x05U)
#define ADC_AUTO_TRIGGER_SOURCE_TIM1_OVF    (0x06U)
#define ADC_AUTO_TRIGGER_SOURCE_TIM1_CAPT   (0x07U)

//==================================================================================================
// Structures and enumerations
//==================================================================================================
typedef enum
{
    ADC_CHANNEL_0 = 0U,
    ADC_CHANNEL_1 = 1U,
    ADC_CHANNEL_2 = 2U,
    ADC_CHANNEL_3 = 3U,
    ADC_CHANNEL_4 = 4U,
    ADC_CHANNEL_5 = 5U,
    ADC_CHANNEL_6 = 6U,
    ADC_CHANNEL_7 = 7U
} ADC_ChannelNumberEnum;

//==================================================================================================
// External variable declarations
//==================================================================================================

//==================================================================================================
// Inline function definitions
//==================================================================================================
static inline void ADC_Enable(void)
{
    ADCSRA |= (1 << ADEN);
}
static inline void ADC_Disable(void)
{
    ADCSRA &= ~(1 << ADEN);
}

//==================================================================================================
// Function prototypes
//==================================================================================================
void ADC_Init(const U8 Reference, const U8 Prescaler);
U16 ADC_BlockingRead(const U8 Channel);
void ADC_ConfigureAutoSampling(const U8 Channel);
void ADC_StartAutoSampling(void);
// void ADC_StopAutoSampling(void);
U16 ADC_GetLastSample(const U8 Channel);

#endif // _ADC_H_