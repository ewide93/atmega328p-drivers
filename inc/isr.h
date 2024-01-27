//==================================================================================================
//
// File: isr.h
//
// Purpose:
//
//==================================================================================================
#ifndef _ISR_H_
#define _ISR_H_


//==================================================================================================
// Include directives.
//==================================================================================================
#include "types.h"
#include "hw_cfg.h"
#include "timer.h"


//==================================================================================================
// Preprocessor definitions.
//==================================================================================================
#define TIM_INT_OVF   (0x00U)
#define TIM_INT_COMPA (0x01U)
#define TIM_INT_COMPB (0x02U)
#define TIM_INT_CAPT  (0x20U)

//==================================================================================================
// Definitions of enumerations and structures.
//==================================================================================================
typedef enum INTERRUPT_VECTOR                /* Interrupt Vector */
{
    INTERRUPT_VECTOR_EXT_INT0,
    INTERRUPT_VECTOR_EXT_INT1,
    INTERRUPT_VECTOR_PC_INT0,
    INTERRUPT_VECTOR_PC_INT1,
    INTERRUPT_VECTOR_PC_INT2,
    INTERRUPT_VECTOR_WDT,
    INTERRUPT_VECTOR_TIM2_COMPA,
    INTERRUPT_VECTOR_TIM2_COMPB,
    INTERRUPT_VECTOR_TIM2_OVF,
    INTERRUPT_VECTOR_TIM1_CAPT,
    INTERRUPT_VECTOR_TIM1_COMPA,
    INTERRUPT_VECTOR_TIM1_COMPB,
    INTERRUPT_VECTOR_TIM1_OVF,
    INTERRUPT_VECTOR_TIM0_COMPA,
    INTERRUPT_VECTOR_TIM0_COMPB,
    INTERRUPT_VECTOR_TIM0_OVF,
    INTERRUPT_VECTOR_SPI_STC,
    INTERRUPT_VECTOR_USART_RX,
    INTERRUPT_VECTOR_USART_DRE,
    INTERRUPT_VECTOR_USART_TX,
    INTERRUPT_VECTOR_ADC,
    INTERRUPT_VECTOR_EE_RDY,
    INTERRUPT_VECTOR_ACOMP,
    INTERRUPT_VECTOR_TWI,
    INTERRUPT_VECTOR_SPM_RDY,
} INTERRUPT_VECTOR;

typedef enum EXT_INT                         /* External Interrupt */
{
    EXT_INT_0,
    EXT_INT_1
} EXT_INT;

typedef enum EXT_INT_SC                      /* External Interrupt Sense Control */
{
    EXT_INT_SC_LOW,
    EXT_INT_SC_ANY,
    EXT_INT_SC_FALLING,
    EXT_INT_SC_RISING,
} EXT_INT_SC;

//==================================================================================================
// Function prototypes.
//==================================================================================================

//--------------------------------------------------------------------------------------------------
// Function : ISR_GlobalInterruptEnable
// Brief    : Enable interrupts globally.
//--------------------------------------------------------------------------------------------------
void ISR_GlobalInterruptEnable(void);

//--------------------------------------------------------------------------------------------------
// Function : ISR_GlobalInterruptDisable
// Brief    : Disable interrupts globally.
//--------------------------------------------------------------------------------------------------
void ISR_GlobalInterruptDisable(void);

//--------------------------------------------------------------------------------------------------
// Function : ISR_ExternalInterruptInit
// Brief    : Initialize an external interrupt.
//--------------------------------------------------------------------------------------------------
void ISR_ExternalInterruptInit(EXT_INT Interrupt, EXT_INT_SC SenseControl);

//--------------------------------------------------------------------------------------------------
// Function : ISR_ExternalInterruptEnable
// Brief    : Enable a specific external interrupt.
//--------------------------------------------------------------------------------------------------
void ISR_ExternalInterruptEnable(EXT_INT Interrupt);

//--------------------------------------------------------------------------------------------------
// Function : ISR_ExternalInterruptDisable
// Brief    : Disable a specific external interrupt.
//--------------------------------------------------------------------------------------------------
void ISR_ExternalInterruptDisable(EXT_INT Interrupt);

//--------------------------------------------------------------------------------------------------
// Function : ISR_AddInterruptHandler
// Brief    : Make specified function the interrupt handler of the given interrupt.
//--------------------------------------------------------------------------------------------------
void ISR_AddInterruptHandler(VoidFunctionPtr Function, INTERRUPT_VECTOR InterruptVector);

//--------------------------------------------------------------------------------------------------
// Function : ISR_TimerInterruptEnable
// Brief    : Enable the specified interrupt for the given timer.
//--------------------------------------------------------------------------------------------------
void ISR_TimerInterruptEnable(TimerType* TimerHandle, const uint8_t Interrupt);

//--------------------------------------------------------------------------------------------------
// Function : ISR_TimerInterruptEnable
// Brief    : Disable the specified interrupt for the given timer.
//--------------------------------------------------------------------------------------------------
void ISR_TimerInterruptDisable(TimerType* TimerHandle, const uint8_t Interrupt);

//--------------------------------------------------------------------------------------------------
// Function : ISR_TimerInterruptToggle
// Brief    : Toggle the specified interrupt for the given timer.
//--------------------------------------------------------------------------------------------------
void ISR_TimerInterruptToggle(TimerType* TimerHandle, const uint8_t Interrupt);

// TODO: Interrupt functionality for ADC
void ISR_ADC_InterruptEnable(void);
void ISR_ADC_InterruptDisable(void);
void ISR_ADC_InterruptToggle(void);

#endif // _ISR_H_