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
static void ExternalInterrupt0Handler(void);
static void ExternalInterrupt1Handler(void);


//==================================================================================================
// Main program entry-point.
//==================================================================================================
int main(void)
{    
    Setup();

    while (1)
    {

    }
    return 0;
}


//==================================================================================================
// Static function definitions.
//==================================================================================================

static void ExternalInterrupt0Handler(void)
{
    Digital_TogglePin(Pin4);
}


static void ExternalInterrupt1Handler(void)
{
    Digital_TogglePin(Pin5);
}


static inline void Setup(void)
{
    Digital_PinInit(Pin2, IO_PORT_D, IO_MODE_INPUT, 2);
    Digital_PinInit(Pin3, IO_PORT_D, IO_MODE_INPUT, 3);
    Digital_PinInit(Pin4, IO_PORT_D, IO_MODE_OUTPUT, 4);
    Digital_PinInit(Pin5, IO_PORT_D, IO_MODE_OUTPUT, 5);

    ISR_ExternalInterruptInit(EXT_INT_0, EXT_INT_SC_FALLING);
    ISR_AddInterruptHandler(ExternalInterrupt0Handler, INTERRUPT_VECTOR_EXT_INT0);
    ISR_ExternalInterruptEnable(EXT_INT_0);

    ISR_ExternalInterruptInit(EXT_INT_1, EXT_INT_SC_FALLING);
    ISR_AddInterruptHandler(ExternalInterrupt1Handler, INTERRUPT_VECTOR_EXT_INT1);
    ISR_ExternalInterruptEnable(EXT_INT_1);
    ISR_GlobalInterruptEnable();
}