#include "delay.h"

void BlockingDelay_ms(unsigned int Delay_ms)
{
    for (unsigned int i = 0; i < Delay_ms; i++)
    {
        _delay_ms(1);
    }
    return;
}
