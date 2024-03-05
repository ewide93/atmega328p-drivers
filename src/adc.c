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
#define ADMUX_VREF_SHIFT                (6U)
#define ADMUX_VREF_CLEAR_MASK           (0x3FU)
#define ADCSRA_PRESCALER_CLEAR_MASK     (0xF8U)
#define ADMUX_CLEAR_CHANNEL_MASK        (0xF8U)
#define ADMUX_SET_CHANNEL_MASK          (0x07U)

//==================================================================================================
// Structures and enumerations
//==================================================================================================
typedef enum
{
    ADC_CHANNEL_STATUS_INACTIVE,
    ADC_CHANNEL_STATUS_ACTIVE
} ADC_StatusEnum;

typedef struct
{
    U8 ChannelNum;
    U8 Status;
    FifoType SampleData;
} ADC_ChannelType;

//==================================================================================================
// Local variables
//==================================================================================================


//==================================================================================================
// Local function prototypes
//==================================================================================================
static inline void ADC_StartConversion(void);
static inline void ADC_SetVoltageReference(const U8 Reference);
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
    ADMUX &= ADMUX_VREF_CLEAR_MASK;
    ADMUX |= (Reference << ADMUX_VREF_SHIFT);
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
    ADCSRA &= ADCSRA_PRESCALER_CLEAR_MASK;
    ADCSRA |= Prescaler;
}


//==================================================================================================
// External function definitions
//==================================================================================================
void ADC_Init(const U8 Reference, const U8 Prescaler)
{
    ADC_SetVoltageReference(Reference);
    ADC_SetPrescaler(Prescaler);
    ADC_Enable();
}

U16 ADC_BlockingRead(const U8 Channel)
{
    U16 AD_Val = 0;
    ADMUX &= ADMUX_CLEAR_CHANNEL_MASK;
    ADMUX |= (Channel & ADMUX_SET_CHANNEL_MASK);
    ADC_StartConversion();
    while (!ReadBit(ADCSRA, ADIF)) { };
    AD_Val = ADC;
    
    return AD_Val;
}


