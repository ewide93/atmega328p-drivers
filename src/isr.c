//==================================================================================================
//
// File: isr.c
//
// Purpose: Functions for initialization of and enabling/disabling of interrupts.
//          Also contains ISR:s for the various interrupts of the system.
//
//==================================================================================================


//==================================================================================================
// Include directives.
//==================================================================================================
#include "isr.h"
#include <avr/interrupt.h>


//==================================================================================================
// Local preprocessor macros.
//==================================================================================================
#define INTERRUPT_VECTOR_TABLE_LENGTH 25

#define EICRA_INT0_CLR (EICRA &= ~((1 << ISC01) | (1 << ISC00)))
#define EICRA_INT1_CLR (EICRA &= ~((1 << ISC11) | (1 << ISC10)))


//==================================================================================================
// Static function prototypes.
//==================================================================================================
static void ISR_NullHandler(void);


//==================================================================================================
// Local variables.
//==================================================================================================
static VoidFunctionPtr InterruptHandlers[INTERRUPT_VECTOR_TABLE_LENGTH] =
{
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler,
    ISR_NullHandler
};


//==================================================================================================
// Static function definitions.
//==================================================================================================
static void ISR_NullHandler(void)
{
    return;
}


//==================================================================================================
// Function definitions.
//==================================================================================================
void ISR_GlobalInterruptEnable(void)
{
    asm("SEI");
}


void ISR_GlobalInterruptDisable(void)
{
    asm("CLI");
}


void ISR_ExternalInterruptEnable(ExtIntEnum Interrupt)
{
    if      (Interrupt == EXT_INT_0) { EIMSK |= (1 << INT0); }
    else if (Interrupt == EXT_INT_1) { EIMSK |= (1 << INT1); }
    else                             { }
}


void ISR_ExternalInterruptDisable(ExtIntEnum Interrupt)
{
    if      (Interrupt == EXT_INT_0) { EIMSK &= ~(1 << INT0); }
    else if (Interrupt == EXT_INT_1) { EIMSK &= ~(1 << INT1); }
    else                             { }
}


void ISR_ExternalInterruptInit(ExtIntEnum Interrupt, ExtIntSenseEnum SenseControl)
{
    switch (SenseControl)
    {
        case EXT_INT_SC_LOW:
        {
            if      (Interrupt == EXT_INT_0) { EICRA_INT0_CLR; }
            else if (Interrupt == EXT_INT_1) { EICRA_INT1_CLR; }
            else                             { }
            break;
        }
        case EXT_INT_SC_ANY:
        {
            if      (Interrupt == EXT_INT_0) { EICRA_INT0_CLR; EICRA |= (1 << ISC00); }
            else if (Interrupt == EXT_INT_1) { EICRA_INT1_CLR; EICRA |= (1 << ISC10); }
            else                             { }
            break;
        }
        case EXT_INT_SC_FALLING:
        {
            if      (Interrupt == EXT_INT_0) { EICRA_INT0_CLR; EICRA |= (1 << ISC01); }
            else if (Interrupt == EXT_INT_1) { EICRA_INT1_CLR; EICRA |= (1 << ISC11); }
            else                             { }
            break;
        }
        case EXT_INT_SC_RISING:
        {
            if      (Interrupt == EXT_INT_0) { EICRA_INT0_CLR; EICRA |= ((1 << ISC01) | (1 << ISC00)); }
            else if (Interrupt == EXT_INT_1) { EICRA_INT1_CLR; EICRA |= ((1 << ISC11) | (1 << ISC10)); }
            else                             { }
            break;
        }
        default:
        {
            break;
        }
    }
}


void ISR_AddInterruptHandler(VoidFunctionPtr Function, InterruptVectorEnum InterruptVector)
{
    InterruptHandlers[InterruptVector] = Function;
}


void ISR_TimerInterruptEnable(TimerType* TimerHandle, const uint8_t Interrupt)
{
    *(TimerHandle->IntMaskReg) |= (1 << Interrupt);
}


void ISR_TimerInterruptDisable(TimerType* TimerHandle, const uint8_t Interrupt)
{
    *(TimerHandle->IntMaskReg) &= ~(1 << Interrupt);
}

void ISR_TimerInterruptToggle(TimerType* TimerHandle, const uint8_t Interrupt)
{
    *(TimerHandle->IntMaskReg) ^= (1 << Interrupt);
}

//==================================================================================================
// Interrupt service routines.
//==================================================================================================

ISR(INT0_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_EXT_INT0]();
    return;
}

ISR(INT1_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_EXT_INT1]();
    return;
}

ISR(PCINT0_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_PC_INT0]();
    return;
}

ISR(PCINT1_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_PC_INT1]();
    return;
}

ISR(PCINT2_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_PC_INT2]();
    return;
}

ISR(WDT_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_WDT]();
    return;
}

ISR(TIMER2_COMPA_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM2_COMPA]();
    return;
}

ISR(TIMER2_COMPB_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM2_COMPB]();
    return;
}

ISR(TIMER2_OVF_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM2_OVF]();
    return;
}

ISR(TIMER1_CAPT_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM1_CAPT]();
    return;
}

ISR(TIMER1_COMPA_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM1_COMPA]();
    return;
}

ISR(TIMER1_COMPB_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM1_COMPB]();
    return;
}

ISR(TIMER1_OVF_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM1_OVF]();
    return;
}

ISR(TIMER0_COMPA_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM0_COMPA]();
    return;
}

ISR(TIMER0_COMPB_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM0_COMPB]();
    return;
}

ISR(TIMER0_OVF_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TIM0_OVF]();
    return;
}

ISR(SPI_STC_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_SPI_STC]();
    return;
}

ISR(USART_RX_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_USART_RX]();
    return;
}

ISR(USART_UDRE_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_USART_DRE]();
    return;
}

ISR(USART_TX_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_USART_TX]();
    return;
}

ISR(ADC_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_ADC]();
    return;
}

ISR(EE_READY_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_EE_RDY]();
    return;
}

ISR(ANALOG_COMP_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_ACOMP]();
    return;
}

ISR(TWI_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_TWI]();
    return;
}

ISR(SPM_READY_vect)
{
    InterruptHandlers[INTERRUPT_VECTOR_SPM_RDY]();
    return;
}