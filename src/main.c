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
#include "isr.h"


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
    Digital_SetPin(Pin3);

    while (1)
    {

    }
    return 0;
}


//==================================================================================================
// Static function definitions.
//==================================================================================================
static inline void Setup(void)
{
    Digital_PinInit(Pin2, IO_PORT_D, IO_MODE_INPUT, 2);
    Digital_PinInit(Pin3, IO_PORT_D, IO_MODE_OUTPUT, 3);
    Digital_PinInit(Pin4, IO_PORT_D, IO_MODE_OUTPUT, 4);

    ISR_ExternalInterruptInit(EXT_INT_0, EXT_INT_SC_RISING);
    ISR_ExternalInterruptEnable(EXT_INT_0);
    ISR_GlobalInterruptEnable();
}