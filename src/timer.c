//==================================================================================================
//
// File name: timer.c
//
// Purpose: Timer module containing functionality common to all timer peripherals.
//
//==================================================================================================

//==================================================================================================
// Include directives
//==================================================================================================
#include "timer.h"

//==================================================================================================
// Local preprocessor definitions
//==================================================================================================

//==================================================================================================
// Local variables
//==================================================================================================

//==================================================================================================
// Local function prototypes
//==================================================================================================

//==================================================================================================
// External function definitions
//==================================================================================================
/*
 *  @brief Enable the specified interrupt for the given timer.
 *  @param Timer
 *      Timer peripheral instance.
 *  @param Interrupt
 *      Timer interrupt type.
 *  @returns
 */
void Timer_InterruptEnable(const TimerEnum Timer, const TimerInterruptEnum Interrupt)
{
    switch (Timer)
    {
        case TIMER0: { SetBit(TIMSK0, Interrupt); break; }
        case TIMER1: { SetBit(TIMSK1, Interrupt); break; }
        case TIMER2: { SetBit(TIMSK2, Interrupt); break; }
        default:     { break; }
    }
}

/*
 *  @brief Disable the specified interrupt for the given timer.
 *  @param Timer
 *      Timer peripheral instance.
 *  @param Interrupt
 *      Timer interrupt type.
 *  @returns
 */
void Timer_InterruptDisable(const TimerEnum Timer, const TimerInterruptEnum Interrupt)
{
    switch (Timer)
    {
        case TIMER0: { ClearBit(TIMSK0, Interrupt); break; }
        case TIMER1: { ClearBit(TIMSK1, Interrupt); break; }
        case TIMER2: { ClearBit(TIMSK2, Interrupt); break; }
        default:     { break; }
    }
}

//==================================================================================================
// Local function definitions
//==================================================================================================
