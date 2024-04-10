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
#include "timer.h"
#include "adc.h"
#include "uart.h"
#include "fsm.h"
#include "protocol.h"

//==================================================================================================
// Static function prototypes.
//==================================================================================================
static inline void Setup(void);
static void Timer0_CompareAHandler(void);


//==================================================================================================
// Variables
//==================================================================================================

//==================================================================================================
// Main program entry-point.
//==================================================================================================
int main(void)
{
    Setup();
    // ADC_StartAutoSampling();

    while (TRUE)
    {
        Protocol_Run();
    }
    return 0;
}


//==================================================================================================
// Static function definitions.
//==================================================================================================
static void Timer0_CompareAHandler(void)
{
    // Protocol_Run();
}

static inline void Setup(void)
{
    Digital_PinInit(4, IO_MODE_OUTPUT);
    Digital_PinInit(5, IO_MODE_OUTPUT);
    Digital_PinInit(6, IO_MODE_OUTPUT);

    Timer0_Init(TIMER0_DEFAULT_CFG);
    Timer_InterruptEnable(TIMER0, TIM_INT_COMPA);
    ISR_AddInterruptHandler(Timer0_CompareAHandler, INTERRUPT_VECTOR_TIM0_COMPA);

    // ADC_Init(ADC_REF_EXTERNAL, ADC_PRESCALER_128);
    // ADC_ConfigureAutoSampling(ADC_CHANNEL_0);
    // ADC_ConfigureAutoSampling(ADC_CHANNEL_3);
    // ADC_InterruptEnable();

    UART_Init(UART_DATA_BITS_8, UART_PARITY_NONE, UART_STOP_BITS_1, UART_BAUD_RATE_19200);
    UART_TxInterruptEnable();
    UART_RxInterruptEnable();
    Protocol_Init();

    ISR_GlobalInterruptEnable();
}