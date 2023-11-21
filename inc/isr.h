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


//==================================================================================================
// Preprocessor definitions.
//==================================================================================================


//==================================================================================================
// Definitions of enumerations and structures.
//==================================================================================================

// Interrupt Vector
typedef enum INTERRUPT_VECTOR
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

// External Interrupt
typedef enum EXT_INT
{
    EXT_INT_0,
    EXT_INT_1
} EXT_INT;

// External Interrupt Sense Control
typedef enum EXT_INT_SC
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

#endif // _ISR_H_