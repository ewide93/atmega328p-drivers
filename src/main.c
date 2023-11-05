//==================================================================================================
//
// File: main.c
//
// Purpose: Main entry-point of application. Executes hardware setup routines before entering
//          infinite loop.
//
//==================================================================================================


//==================================================================================================
// Include directives.
//==================================================================================================
#include "types.h"
#include "delay.h"
#include "digital.h"


//==================================================================================================
// Static function prototypes.
//==================================================================================================
static inline void Setup(void);


//==================================================================================================
// Main program entry-point.
//==================================================================================================
int main(void)
{    
    Setup();

    while (1)
    {
        Digital_SetPin(Pin3);
        BlockingDelay_ms(600);
        Digital_ClrPin(Pin3);
        BlockingDelay_ms(150);

        Digital_SetPin(Pin4);
        BlockingDelay_ms(600);
        Digital_ClrPin(Pin4);
        BlockingDelay_ms(150);
    }
    return 0;
}


//==================================================================================================
// Static function definitions.
//==================================================================================================
static inline void Setup(void)
{
    Digital_PinInit(Pin3, IO_PORT_D, OUTPUT, 3);
    Digital_PinInit(Pin4, IO_PORT_D, OUTPUT, 4);
}