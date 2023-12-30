//==================================================================================================
//
// File name: timer.c
//
// Purpose:
//
//==================================================================================================


//==================================================================================================
// Include directives
//==================================================================================================
#include "timer.h"


//==================================================================================================
// Local preprocessor definitions
//==================================================================================================
#define TIMER0_ADDRESS         ((Timer0Type*)0x44U)
#define TIMER0_ID              (0)
#define TIMER0_INT_MASK_REG    ((volatile uint8_t*)0x6EU)

#define TIMER1_ADDRESS         ((Timer1Type*)0x80U)
#define TIMER1_ID              (1)
#define TIMER1_INT_MASK_REG    ((volatile uint8_t*)0x6FU)

#define TIMER2_ADDRESS         ((Timer2Type*)0xB0U)
#define TIMER2_ID              (2)
#define TIMER2_INT_MASK_REG    ((volatile uint8_t*)0x70U)

#define OC0A_OUTPUT_ENABLE     (DDRD |= (1 << 6))
#define OC0B_OUTPUT_ENABLE     (DDRD |= (1 << 5))
//==================================================================================================
// Local variables
//==================================================================================================


//==================================================================================================
// Local function prototypes
//==================================================================================================
static void Timer_Timer0Init(Timer0Type* Timer, Timer0CfgType* TimerCfg);
static void Timer_Timer1Init(Timer1Type* Timer, void* TimerCfg);
static void Timer_Timer2Init(Timer2Type* Timer, void* TimerCfg);


//==================================================================================================
// External variable definitions
//==================================================================================================
static TimerType Timer0_Local = {
    .Timer = TIMER0_ADDRESS,
    .TimerID = TIMER0_ID,
    .IntMaskReg = TIMER0_INT_MASK_REG,
};
TimerType* Timer0Handle = &Timer0_Local;

static TimerType Timer1_Local = {
    .Timer = TIMER1_ADDRESS,
    .TimerID = TIMER1_ID,
    .IntMaskReg = TIMER1_INT_MASK_REG,
};
TimerType* Timer1Handle = &Timer1_Local;

static TimerType Timer2_Local = {
    .Timer = TIMER2_ADDRESS,
    .TimerID = TIMER2_ID,
    .IntMaskReg = TIMER2_INT_MASK_REG,
    };
TimerType* Timer2Handle = &Timer2_Local;


//==================================================================================================
// External function definitions
//==================================================================================================
void Timer_Init(TimerType* TimerHandle, void* TimerCfg)
{
    switch (TimerHandle->TimerID)
    {
        case TIMER0_ID: { Timer_Timer0Init((Timer0Type*)TimerHandle->Timer, (Timer0CfgType*)TimerCfg); break; }
        case TIMER1_ID: { Timer_Timer1Init((Timer1Type*)TimerHandle->Timer, TimerCfg); break; }
        case TIMER2_ID: { Timer_Timer2Init((Timer2Type*)TimerHandle->Timer, TimerCfg); break; }
        default: { break; }
    }
}


//==================================================================================================
// Local function definitions
//==================================================================================================
static void Timer_Timer0Init(Timer0Type* Timer, Timer0CfgType* TimerCfg)
{
    Timer->CtrlRegA |= ( (TimerCfg->WaveGenMode & 0x03) | (TimerCfg->OutModeA << 6) | (TimerCfg->OutModeB << 4) );
    Timer->CtrlRegB |= ( (TimerCfg->Prescaler) | ((TimerCfg->WaveGenMode & 0x04) << 1) );
    Timer->OutCompRegA = TimerCfg->OutCompValA;
    Timer->OutCompRegB = TimerCfg->OutCompValB;
    if (TimerCfg->OutModeA > 0) OC0A_OUTPUT_ENABLE;
    if (TimerCfg->OutModeB > 0) OC0B_OUTPUT_ENABLE;
}

static void Timer_Timer1Init(Timer1Type* Timer, void* TimerCfg)
{
    Timer->OutCompRegA = ((Timer0CfgType*)TimerCfg)->OutCompValA;
}

static void Timer_Timer2Init(Timer2Type* Timer, void* TimerCfg)
{
    Timer->OutCompRegA = ((Timer0CfgType*)TimerCfg)->OutCompValA;
}