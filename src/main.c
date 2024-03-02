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

// ADC_CfgType ADC_Config = {
//     .Prescaler = ADC_PRESCALER_128,
//     .Reference = ADC_REF_VCC,
//     .TriggerSource = ADC_AUTO_TRIGGER_SOURCE_TIM0_COMPA
// };


//==================================================================================================
// Main program entry-point.
//==================================================================================================
int main(void)
{
    Setup();
    UART_WriteString("Starting!\n", 11);

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
    static U8 Counter = 0;
    static U8 Msg = 0x41;
    if (Counter++ >= 250)
    {
        UART_WriteByte(Msg++);
        UART_WriteByte(Msg++);
        if (Msg > 0x5B) Msg = 0x41;
        Counter = 0;
    }
}

static inline void Setup(void)
{
    Timer_Init(Timer0Handle, &Timer0Cfg, TIMER0_ID);
    ISR_TimerInterruptEnable(Timer0Handle, TIM_INT_COMPA);
    ISR_AddInterruptHandler(Timer0_CompareAHandler, INTERRUPT_VECTOR_TIM0_COMPA);

    // ADC_Init(&ADC_Config);
    // ADC_AutoTriggerEnable();

    UART_Init(UART_DATA_BITS_8, UART_PARITY_NONE, UART_STOP_BITS_1, UART_BAUD_RATE_115200);
    ISR_UART_TxInterruptEnable();
    ISR_UART_RxInterruptEnable();

    ISR_GlobalInterruptEnable();
}