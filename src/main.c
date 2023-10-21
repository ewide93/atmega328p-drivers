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
#include "global.h"

static inline void Setup(void)
{
    Digital_PinInit(&Pin3, IO_PORT_D, OUTPUT, 3);
    Digital_PinInit(&Pin4, IO_PORT_D, OUTPUT, 4);
}

int main(void)
{    
    Setup();

    while (1)
    {
        Digital_SetPin(&Pin3);
        // Digital_SetPin(&Pin4);
        BlockingDelay_ms(500);
        Digital_ClrPin(&Pin3);
        // Digital_ClrPin(&Pin4);
        BlockingDelay_ms(250);

        // Digital_SetPin(&Pin3);
        Digital_SetPin(&Pin4);
        BlockingDelay_ms(500);
        // Digital_ClrPin(&Pin3);
        Digital_ClrPin(&Pin4);
        BlockingDelay_ms(250);
    }
    return 0;
}