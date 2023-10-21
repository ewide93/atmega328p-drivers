/********************************************************************************
* main.c: 
********************************************************************************/

/* Include directives */
#include "main.h"
#include "delay.h"

ISR (INT0_vect)
{
    PORTD ^= (1 << 3);

    return;
}

int main(void)
{
    DDRD |= (1 << PORTD3);
    // unsigned int x = MY_DEFINE;
    // PORTD |= (1 << 2);

    // EICRA = (1 << ISC01) | (1 << ISC00);
    // EIMSK = (1 << INT0);
    // asm("SEI");

    
    while (true)
    {
        PORTD |= (1 << PORTD3);
        BlockingDelay_ms(ON_TIME_MS);
        PORTD &= ~(1 << PORTD3);
        BlockingDelay_ms(OFF_TIME_MS);
    }

    return 0;
}