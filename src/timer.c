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
#define TIMER0_ADDRESS (Timer0Type*)(0x44)
#define TIMER0_ID      (0)
#define TIMER1_ADDRESS (Timer1Type*)(0x80)
#define TIMER1_ID      (1)
#define TIMER2_ADDRESS (Timer2Type*)(0xB0)
#define TIMER2_ID      (2)


//==================================================================================================
// Local variables
//==================================================================================================


//==================================================================================================
// Local function prototypes
//==================================================================================================
static void Timer_Timer0Init(Timer0Type* Timer, enum TIMER_MODE Mode);
static void Timer_Timer1Init(Timer1Type* Timer, enum TIMER_MODE Mode);
static void Timer_Timer2Init(Timer2Type* Timer, enum TIMER_MODE Mode);


//==================================================================================================
// External variable definitions
//==================================================================================================
static TimerType Timer0_Local = {
    .Timer = TIMER0_ADDRESS,
    .TimerID = TIMER0_ID,
    .IntMaskReg = (volatile uint8_t*)(0x6E),
};
TimerType* Timer0Handle = &Timer0_Local;

static TimerType Timer1_Local = {
    .Timer = TIMER1_ADDRESS,
    .TimerID = TIMER1_ID,
    .IntMaskReg = (volatile uint8_t*)(0x6F),
};
TimerType* Timer1Handle = &Timer1_Local;

static TimerType Timer2_Local = {
    .Timer = TIMER2_ADDRESS,
    .TimerID = TIMER2_ID,
    .IntMaskReg = (volatile uint8_t*)(0x70),
    };
TimerType* Timer2Handle = &Timer2_Local;


//==================================================================================================
// External function definitions
//==================================================================================================
void Timer_Init(TimerType* TimerHandle, enum TIMER_MODE Mode)
{
    switch (TimerHandle->TimerID)
    {
        case TIMER0_ID: { Timer_Timer0Init((Timer0Type*)TimerHandle->Timer, Mode); break; }
        case TIMER1_ID: { Timer_Timer1Init((Timer1Type*)TimerHandle->Timer, Mode); break; }
        case TIMER2_ID: { Timer_Timer2Init((Timer2Type*)TimerHandle->Timer, Mode); break; }
        default: { break; }
    }
}


//==================================================================================================
// Local function definitions
//==================================================================================================
static void Timer_Timer0Init(Timer0Type* Timer, enum TIMER_MODE Mode)
{
    Timer->CntReg = Mode;
    Timer->CtrlRegA |= (1 << WGM01);
    Timer->CtrlRegB |= (1 << CS02);
    Timer->OutCompRegA = 125;
    Timer->OutCompRegB = 125;
}

static void Timer_Timer1Init(Timer1Type* Timer, enum TIMER_MODE Mode)
{
    Timer->CntReg = Mode;
}

static void Timer_Timer2Init(Timer2Type* Timer, enum TIMER_MODE Mode)
{
    Timer->CntReg = Mode;
}