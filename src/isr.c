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
#include "digital.h"


//==================================================================================================
// Local preprocessor macros.
//==================================================================================================
#define EICRA_INT0_CLR (EICRA &= ~((1 << ISC01) | (1 << ISC00)))
#define EICRA_INT1_CLR (EICRA &= ~((1 << ISC11) | (1 << ISC10)))


//==================================================================================================
// Static function definitions.
//==================================================================================================
static void ISR_NullHandler(void)
{
    return;
}


//==================================================================================================
// Local variables.
//==================================================================================================
static VoidFunctionPtr InterruptHandlers[2] = { ISR_NullHandler, ISR_NullHandler};


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


void ISR_ExternalInterruptEnable(EXT_INT Interrupt)
{
    if      (Interrupt == EXT_INT_0) { EIMSK |= (1 << INT0); }
    else if (Interrupt == EXT_INT_1) { EIMSK |= (1 << INT1); }
    else                             { }
}


void ISR_ExternalInterruptDisable(EXT_INT Interrupt)
{
    if      (Interrupt == EXT_INT_0) { EIMSK &= ~(1 << INT0); }
    else if (Interrupt == EXT_INT_1) { EIMSK &= ~(1 << INT1); }
    else                             { }
}


void ISR_ExternalInterruptInit(EXT_INT Interrupt, EXT_INT_SC SenseControl)
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

void ISR_AddInterruptHandler(VoidFunctionPtr Function, uint8_t Interrupt)
{
    InterruptHandlers[Interrupt] = Function;
}

//==================================================================================================
// Interrupt service routines.
//==================================================================================================

// Interrupt service routine for external interrupt request 0.
ISR(INT0_vect)
{
    // Digital_TogglePin(Pin4);
    InterruptHandlers[EXT_INT0_VECTOR]();
    return;
}


// Interrupt service routine for external interrupt request 1.
ISR(INT1_vect)
{
    // Digital_TogglePin(Pin5);
    InterruptHandlers[EXT_INT1_VECTOR]();
    return;
}