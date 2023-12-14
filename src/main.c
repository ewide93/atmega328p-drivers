//==================================================================================================
//
// File: main.c
//
// Purpose: Main entry-point of application. Executes hardware setup routines before entering
//          infinite loop.
//
//==================================================================================================


//==================================================================================================
// Include directives.
//==================================================================================================
#include "types.h"
#include "delay.h"
#include "digital.h"
#include "isr.h"
#include "timer.h"


//==================================================================================================
// Static function prototypes.
//==================================================================================================
static inline void Setup(void);
static void ExternalInterrupt0Handler(void);
static void ExternalInterrupt1Handler(void);
static void Timer0_CompareAHandler(void);
static void Timer0_CompareBHandler(void);


//==================================================================================================
// Main program entry-point.
//==================================================================================================
int main(void)
{
    Setup();

    while (true)
    {

    }
    return 0;
}


//==================================================================================================
// Static function definitions.
//==================================================================================================

static void ExternalInterrupt0Handler(void)
{
    TIMSK0 ^= (1 << OCIE0A);
}


static void ExternalInterrupt1Handler(void)
{
    TIMSK0 ^= (1 << OCIE0B);
}

static void Timer0_CompareAHandler(void)
{
    static uint16_t cnt = 0;
    if (cnt++ > 50)
    {
        Digital_TogglePin(Pin4);
        cnt = 0;
    }
}

static void Timer0_CompareBHandler(void)
{
    static uint16_t cnt = 0;
    if (cnt++ > 50)
    {
        Digital_TogglePin(Pin5);
        cnt = 0;
    }
}


static inline void Setup(void)
{
    Digital_PinInit(Pin2, IO_MODE_INPUT);
    Digital_PinInit(Pin3, IO_MODE_INPUT);
    Digital_PinInit(Pin4, IO_MODE_OUTPUT);
    Digital_PinInit(Pin5, IO_MODE_OUTPUT);

    ISR_ExternalInterruptInit(EXT_INT_0, EXT_INT_SC_FALLING);
    ISR_AddInterruptHandler(ExternalInterrupt0Handler, INTERRUPT_VECTOR_EXT_INT0);
    ISR_ExternalInterruptEnable(EXT_INT_0);

    ISR_ExternalInterruptInit(EXT_INT_1, EXT_INT_SC_FALLING);
    ISR_AddInterruptHandler(ExternalInterrupt1Handler, INTERRUPT_VECTOR_EXT_INT1);
    ISR_ExternalInterruptEnable(EXT_INT_1);

    TCCR0A |= (1 << WGM01);
    TCCR0B |= (1 << CS02);
    OCR0A = 125;
    OCR0B = 125;
    TIMSK0 |= ((1 << OCIE0A) | (1 << OCIE0B));
    ISR_AddInterruptHandler(Timer0_CompareAHandler, INTERRUPT_VECTOR_TIM0_COMPA);
    ISR_AddInterruptHandler(Timer0_CompareBHandler, INTERRUPT_VECTOR_TIM0_COMPB);

    ISR_GlobalInterruptEnable();
}