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

//==================================================================================================
// Preprocessor definitions
//==================================================================================================
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

#define ADC_CHANNEL_0                       (0x00U)
#define ADC_CHANNEL_1                       (0x01U)
#define ADC_CHANNEL_2                       (0x02U)
#define ADC_CHANNEL_3                       (0x03U)
#define ADC_CHANNEL_4                       (0x04U)
#define ADC_CHANNEL_5                       (0x05U)
#define ADC_CHANNEL_6                       (0x06U)
#define ADC_CHANNEL_7                       (0x07U)

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
typedef struct ADC_CfgType
{
    U8 Reference;
    U8 TriggerSource;
    U8 Prescaler;
} ADC_CfgType;

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
void ADC_Init(const ADC_CfgType* Config); /* TODO: Rework this function! */
U16 ADC_BlockingRead(void);

#endif // _ADC_H_