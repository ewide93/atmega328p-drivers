//==================================================================================================
//
// File name: adc.c
//
// Purpose:
//
//==================================================================================================


//==================================================================================================
// Include directives
//==================================================================================================
#include "adc.h"

//==================================================================================================
// Local preprocessor definitions
//==================================================================================================
#define ADMUX_VREF_SHIFT    (6U)
#define ADMUX_VREF_MASK     (0x3FU)


//==================================================================================================
// Local variables
//==================================================================================================


//==================================================================================================
// Local function prototypes
//==================================================================================================
static inline void ADC_StartConversion(void);
static inline void ADC_SetVoltageReference(const U8 Reference);
static inline void ADC_SelectChannel(const U8 Channel);
static inline void ADC_AutoTriggerEnable(void);
static inline void ADC_AutoTriggerDisable(void);
static inline void ADC_SetAutoTriggerSource(const U8 Source);
static inline void ADC_SetPrescaler(const U8 Prescaler);


//==================================================================================================
// External variable definitions
//==================================================================================================


//==================================================================================================
// Local function definitions
//==================================================================================================
static inline void ADC_StartConversion(void)
{
    ADCSRA |= (1 << ADSC);
}

static inline void ADC_SetVoltageReference(const U8 Reference)
{
    ADMUX &= 0x3F;
    ADMUX |= (Reference << ADMUX_VREF_SHIFT);
}

static inline void ADC_SelectChannel(const U8 Channel)
{
    ADMUX &= ~(1 << 0x07);
    ADMUX |= (Channel & 0x07);
}

static inline void ADC_AutoTriggerEnable(void)
{
    ADCSRA |= (1 << ADATE);
}

static inline void ADC_AutoTriggerDisable(void)
{
    ADCSRA &= ~(1 << ADATE);
}

static inline void ADC_SetAutoTriggerSource(const U8 Source)
{
    ADCSRB &= 0xF8;
    ADCSRB |= Source;
}

static inline void ADC_SetPrescaler(const U8 Prescaler)
{
    ADCSRA &= 0xF8;
    ADCSRA |= Prescaler;
}


//==================================================================================================
// External function definitions
//==================================================================================================
void ADC_Init(const ADC_CfgType* Config)
{
    ADC_SetVoltageReference(Config->Reference);
    ADC_SetAutoTriggerSource(Config->TriggerSource);
    ADC_SetPrescaler(Config->Prescaler);
}



