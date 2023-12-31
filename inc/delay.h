//==================================================================================================
//
// File: delay.h
//
// Purpose: Header-file containing prototypes for blocking delay functions.
//
//==================================================================================================
#ifndef _DELAY_H_
#define _DELAY_H_


//==================================================================================================
// Include directives.
//==================================================================================================
#include <util/delay.h>


//==================================================================================================
// Function prototypes.
//==================================================================================================
void BlockingDelay_ms(uint16_t Delay_ms);
void BlockingDelay_us(uint16_t Delay_us);


#endif // _DELAY_H_