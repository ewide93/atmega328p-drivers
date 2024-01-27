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
#define ADMUX_VREF_SHIFT (6U)

//==================================================================================================
// Local variables
//==================================================================================================


//==================================================================================================
// Local function prototypes
//==================================================================================================


//==================================================================================================
// External variable definitions
//==================================================================================================


//==================================================================================================
// Local function definitions
//==================================================================================================


//==================================================================================================
// External function definitions
//==================================================================================================
void ADC_Enable(void)
{
    ADCSRA |= (1 << ADEN);
}

void ADC_Disable(void)
{
    ADCSRA &= ~(1 << ADEN);
}

void ADC_StartConversion(void)
{
    ADCSRA |= (1 << ADSC);
}

void ADC_SetVoltageReference(const U8 Reference)
{
    ADMUX &= 0x3F;
    ADMUX |= (Reference << ADMUX_VREF_SHIFT);
}

void ADC_InputChannelEnable(const U8 Channel)
{
    ADMUX |= (1 << Channel);
}

void ADC_InputChannelDisable(const U8 Channel)
{
    ADMUX &= ~(1 << Channel);
}

void ADC_AutoTriggerEnable(void)
{
    ADCSRA |= (1 << ADATE);
}

void ADC_AutoTriggerDisable(void)
{
    ADCSRA &= ~(1 << ADATE);
}

void ADC_SetAutoTriggerSource(const U8 Source)
{
    ADCSRB &= 0xF8;
    ADCSRB |= Source;
}

void ADC_SetPrescaler(const U8 Prescaler)
{
    ADCSRA &= 0xF8;
    ADCSRA |= Prescaler;
}

void ADC_Init(const ADC_CfgType* Config)
{
    ADC_SetVoltageReference(Config->Reference);
    ADC_SetAutoTriggerSource(Config->TriggerSource);
    ADC_SetPrescaler(Config->Prescaler);
}



