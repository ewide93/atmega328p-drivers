////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: main.c
//
// Purpose: Main entry-point of application. Executes hardware setup routines before entering
//          infinite loop.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Include directives
// 
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "delay.h"
#include "typedef.h"

volatile BOOL BlinkEnabled = FALSE;

ISR (INT0_vect)
{
    PORTD &= ~(1 << PORTD3);
    BlinkEnabled = !BlinkEnabled;

    return;
}


int main(void)
{
    DDRD |= (1 << PORTD3);
    PORTD |= (1 << 2);

    EICRA = (1 << ISC01) | (1 << ISC00);
    EIMSK = (1 << INT0);
    asm("SEI");

    
    while (1)
    {
        if (BlinkEnabled)
        {
            PORTD |= (1 << PORTD3);
            BlockingDelay_ms(500);
            PORTD &= ~(1 << PORTD3);
            BlockingDelay_ms(250);
        }
    }

    return 0;
}