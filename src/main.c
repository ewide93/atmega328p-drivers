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

/* For debug purposes. */
// #include <stdio.h>

//==================================================================================================
// Static function prototypes.
//==================================================================================================
static inline void Setup(void);
static void Timer0_CompareAHandler(void);


//==================================================================================================
// Variables
//==================================================================================================
Timer0CfgType Timer0Cfg = {
    .OutCompValA = 250,
    .OutCompValB = 250,
    .Prescaler = TIMER0_PRESCALER_64,
    .OutModeA = TIMER0_COMA_NONE,
    .OutModeB = TIMER0_COMB_NONE,
    .WaveGenMode = TIMER0_WGM_CTC };

//==================================================================================================
// Main program entry-point.
//==================================================================================================
int main(void)
{
    Setup();
    // UART_WriteString("Starting!\n", 11);
    // ADC_StartAutoSampling();

    while (TRUE)
    {

    }
    return 0;
}


//==================================================================================================
// Static function definitions.
//==================================================================================================
static void Timer0_CompareAHandler(void)
{
    Protocol_Run();
}

static inline void Setup(void)
{
    Digital_PinInit(4, IO_MODE_OUTPUT);
    Digital_PinInit(5, IO_MODE_OUTPUT);
    Digital_PinInit(6, IO_MODE_OUTPUT);

    Timer_Init(Timer0Handle, &Timer0Cfg, TIMER0_ID);
    ISR_TimerInterruptEnable(Timer0Handle, TIM_INT_COMPA);
    ISR_AddInterruptHandler(Timer0_CompareAHandler, INTERRUPT_VECTOR_TIM0_COMPA);

    // ADC_Init(ADC_REF_EXTERNAL, ADC_PRESCALER_128);
    // ADC_ConfigureAutoSampling(ADC_CHANNEL_0);
    // ADC_ConfigureAutoSampling(ADC_CHANNEL_3);
    // ISR_ADC_InterruptEnable();

    UART_Init(UART_DATA_BITS_8, UART_PARITY_NONE, UART_STOP_BITS_1, UART_BAUD_RATE_19200);
    ISR_UART_TxInterruptEnable();
    ISR_UART_RxInterruptEnable();
    Protocol_Init();

    ISR_GlobalInterruptEnable();
}