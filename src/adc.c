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

#define ADC_DUMMY_CHANNEL               (0xDDU)

//==================================================================================================
// Structures and enumerations
//==================================================================================================
typedef struct
{
    U8 ChannelNum;
    BOOL Enabled;
    U16 LastSample;     /* NOTE: Replace with ring buffer? */
} ADC_ChannelType;

typedef enum
{
    AUTO_SAMPLING_STATUS_IDLE,
    AUTO_SAMPLING_STATUS_RUNNING,
    AUTO_SAMPLING_STATUS_DONE
} ADC_AutoSamplingStatusEnum;

typedef struct
{
    U8 ActiveChannel;
    U8 FirstChannel;
    U8 LastChannel;
    U8 NofChannels;
    U8 Status;
} ADC_AutoSamplingConfigType;

//==================================================================================================
// Local variables
//==================================================================================================
static ADC_ChannelType ADC_Channels[ADC_NOF_CHANNELS] =
{
    { .ChannelNum = ADC_CHANNEL_0, .Enabled = FALSE, .LastSample = 0 },
    { .ChannelNum = ADC_CHANNEL_1, .Enabled = FALSE, .LastSample = 0 },
    { .ChannelNum = ADC_CHANNEL_2, .Enabled = FALSE, .LastSample = 0 },
    { .ChannelNum = ADC_CHANNEL_3, .Enabled = FALSE, .LastSample = 0 },
    { .ChannelNum = ADC_CHANNEL_4, .Enabled = FALSE, .LastSample = 0 },
    { .ChannelNum = ADC_CHANNEL_5, .Enabled = FALSE, .LastSample = 0 },
    { .ChannelNum = ADC_CHANNEL_6, .Enabled = FALSE, .LastSample = 0 },
    { .ChannelNum = ADC_CHANNEL_7, .Enabled = FALSE, .LastSample = 0 }
};

static ADC_AutoSamplingConfigType AutoSamplingConfig =
{
    .ActiveChannel = ADC_CHANNEL_0,
    .FirstChannel = ADC_CHANNEL_0,
    .LastChannel = ADC_CHANNEL_0,
    .NofChannels = 0,
    .Status = AUTO_SAMPLING_STATUS_IDLE
};

//==================================================================================================
// Local function prototypes
//==================================================================================================
static inline void ADC_SelectChannel(const U8 Channel);
static inline void ADC_StartConversion(void);
static inline void ADC_SetVoltageReference(const U8 Reference);
static inline void ADC_AutoTriggerEnable(void);
static inline void ADC_AutoTriggerDisable(void);
static inline void ADC_SetAutoTriggerSource(const U8 Source);
static inline void ADC_SetPrescaler(const U8 Prescaler);
static inline void ADC_Read(const U8 Channel);
static void ADC_ConversionCompleteInterruptHandler(void);

//==================================================================================================
// Local function definitions
//==================================================================================================
static inline void ADC_SelectChannel(const U8 Channel)
{
    ADMUX &= ADMUX_CLEAR_CHANNEL_MASK;
    ADMUX |= (Channel & ADMUX_SET_CHANNEL_MASK);
}

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

static inline void ADC_Read(const U8 Channel)
{
    ADC_SelectChannel(Channel);
    ADC_StartConversion();
}

static void ADC_ConversionCompleteInterruptHandler(void)
{
    const U8 CurrentChannel = AutoSamplingConfig.ActiveChannel;
    U8 i = CurrentChannel + 1;
    U8 NextChannel = ADC_DUMMY_CHANNEL;
    const U16 AD_Val = ADC;

    ADC_Channels[CurrentChannel].LastSample = AD_Val;

    if (i == ADC_NOF_CHANNELS)
    {
        AutoSamplingConfig.Status = AUTO_SAMPLING_STATUS_DONE;
    }
    else
    {
        for (U8 i = CurrentChannel + 1; i < ADC_NOF_CHANNELS; i++)
        {
            if (ADC_Channels[i].Enabled)
            {
                NextChannel = i;
                break;
            }
            else { }

        }

        if (NextChannel == ADC_DUMMY_CHANNEL)
        {
            AutoSamplingConfig.Status = AUTO_SAMPLING_STATUS_DONE;
        }
        else
        {
            AutoSamplingConfig.ActiveChannel = NextChannel;
            ADC_Read(NextChannel);
        }

    }
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
    ADC_SelectChannel(Channel);
    ADC_StartConversion();
    while (!ReadBit(ADCSRA, ADIF)) { };
    AD_Val = ADC;

    return AD_Val;
}

void ADC_ConfigureAutoSampling(const U8 Channel)
{
    if (AutoSamplingConfig.Status != AUTO_SAMPLING_STATUS_IDLE) return;

    if (AutoSamplingConfig.NofChannels == 0)
    {
        AutoSamplingConfig.FirstChannel = Channel;
        AutoSamplingConfig.LastChannel = Channel;
        AutoSamplingConfig.ActiveChannel = Channel;
    }
    else
    {
        if (Channel < AutoSamplingConfig.FirstChannel)
        {
            AutoSamplingConfig.FirstChannel = Channel;
            AutoSamplingConfig.ActiveChannel = Channel;
        }
        else { }

        if (Channel > AutoSamplingConfig.LastChannel)
        {
            AutoSamplingConfig.LastChannel = Channel;
        }
        else { }
    }

    ADC_Channels[Channel].Enabled = TRUE;
    AutoSamplingConfig.NofChannels++;
}

void ADC_StartAutoSampling(void)
{
    if (AutoSamplingConfig.Status == AUTO_SAMPLING_STATUS_IDLE)
    {
        ISR_AddInterruptHandler(ADC_ConversionCompleteInterruptHandler, INTERRUPT_VECTOR_ADC);
    }
    AutoSamplingConfig.Status = AUTO_SAMPLING_STATUS_RUNNING;
    ADC_Read(ADC_Channels[AutoSamplingConfig.FirstChannel].ChannelNum);
}

void ADC_StopAutoSampling(void)
{

}

U16 ADC_GetLastSample(const U8 Channel)
{
    return ADC_Channels[Channel].LastSample;
}
