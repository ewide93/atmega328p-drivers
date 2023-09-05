/********************************************************************************
* main.c: 
********************************************************************************/

/* Include directives */
#include "main.h"

// #define PORTB *((volatile uint8_t*) 0x25)
// #define DDRB  *((volatile uint8_t*) 0x24)
// #define PINB  *((volatile uint8_t*) 0x23)

ISR (INT0_vect)
{
    PORTB ^= (1 << 5);

    return;
}


int main(void)
{
    DDRB |= (1 << 5);
    // PORTD |= (1 << 2);

    EICRA = (1 << ISC01) | (1 << ISC00);
    EIMSK = (1 << INT0);
    asm("SEI");

    
    while (true)
    {

    }

    return 0;
}