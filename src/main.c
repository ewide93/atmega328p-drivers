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
        if (Digital_ReadPin(Pin5))
        {
            Digital_SetPin(Pin3);
            Digital_ClrPin(Pin4);
        }
        else
        {
            Digital_SetPin(Pin4);
            Digital_ClrPin(Pin3);
        }
    }
    return 0;
}


//==================================================================================================
// Static function definitions.
//==================================================================================================
static inline void Setup(void)
{
    Digital_PinInit(Pin3, IO_PORT_D, IO_MODE_OUTPUT, 3);
    Digital_PinInit(Pin4, IO_PORT_D, IO_MODE_OUTPUT, 4);
    Digital_PinInit(Pin5, IO_PORT_D, IO_MODE_INPUT, 5);
}