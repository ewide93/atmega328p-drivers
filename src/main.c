/********************************************************************************
* main.c: 
********************************************************************************/

/* Include directives */
#include "main.h"
#include "delay.h"

volatile bool BlinkEnabled = false;

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

    
    while (true)
    {
        if (BlinkEnabled)
        {
            PORTD |= (1 << PORTD3);
            BlockingDelay_ms(ON_TIME_MS);
            PORTD &= ~(1 << PORTD3);
            BlockingDelay_ms(OFF_TIME_MS);
        }
    }

    return 0;
}