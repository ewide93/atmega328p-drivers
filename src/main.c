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
static void ExternalInterrupt0Handler(void);
static void ExternalInterrupt1Handler(void);
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

ADC_CfgType ADC_Config = {
    .Prescaler = ADC_PRESCALER_128,
    .Reference = ADC_REF_VCC,
    .TriggerSource = ADC_AUTO_TRIGGER_SOURCE_TIM0_COMPA
};

FSMType TestMachine;
typedef enum
{
    TEST_STATE_NONE,
    TEST_STATE_PRINT_1,
    TEST_STATE_PRINT_2,
} TestStateEnum;


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
    Digital_ClearPin(Pin4);
    ISR_TimerInterruptToggle(Timer0Handle, TIM_INT_COMPA);
}


static void ExternalInterrupt1Handler(void)
{
    Digital_ClearPin(Pin5);
    ISR_TimerInterruptToggle(Timer0Handle, TIM_INT_COMPB);
}

static void Timer0_CompareAHandler(void)
{
    static uint8_t Counter = 0;
    if (Counter++ >= 250)
    {
        const U8 State = FSM_GetCurrentState(&TestMachine);
        const U8 PrevState = FSM_GetPreviousState(&TestMachine);

        if (PrevState == FSM_STATE_NONE) UART_Write("Starting!\r\n", 12);

        switch (State)
        {
            case TEST_STATE_PRINT_1:
            {
                UART_Write("Hello ", 7);
                FSM_SetState(&TestMachine, TEST_STATE_PRINT_2);
                break;
            }
            case TEST_STATE_PRINT_2:
            {
                UART_Write("World!\r\n", 9);
                FSM_SetState(&TestMachine, TEST_STATE_PRINT_1);
                break;
            }
            default:
            {
                break;
            }
        }
        Counter = 0;
    }
}

static inline void Setup(void)
{
    Digital_PinInit(Pin2, IO_MODE_INPUT);
    Digital_PinInit(Pin3, IO_MODE_INPUT);
    Digital_PinInit(Pin4, IO_MODE_OUTPUT);
    Digital_PinInit(Pin5, IO_MODE_OUTPUT);

    FSM_Init(&TestMachine);

    ISR_ExternalInterruptInit(EXT_INT_0, EXT_INT_SC_FALLING);
    ISR_AddInterruptHandler(ExternalInterrupt0Handler, INTERRUPT_VECTOR_EXT_INT0);
    ISR_ExternalInterruptEnable(EXT_INT_0);

    ISR_ExternalInterruptInit(EXT_INT_1, EXT_INT_SC_FALLING);
    ISR_AddInterruptHandler(ExternalInterrupt1Handler, INTERRUPT_VECTOR_EXT_INT1);
    ISR_ExternalInterruptEnable(EXT_INT_1);

    Timer_Init(Timer0Handle, &Timer0Cfg, TIMER0_ID);
    ISR_TimerInterruptEnable(Timer0Handle, TIM_INT_COMPA);
    ISR_AddInterruptHandler(Timer0_CompareAHandler, INTERRUPT_VECTOR_TIM0_COMPA);

    // ADC_Init(&ADC_Config);
    // ADC_AutoTriggerEnable();
    UART_Init(UART_DATA_BITS_8, UART_PARITY_NONE, UART_STOP_BITS_1, UART_BAUD_RATE_115200);
    ISR_UART_TxInterruptEnable();

    ISR_GlobalInterruptEnable();
}