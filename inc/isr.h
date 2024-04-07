//==================================================================================================
//
// File: isr.h
//
// Purpose: Interrupt Service Routine header.
//
//==================================================================================================
#ifndef _ISR_H_
#define _ISR_H_

//==================================================================================================
// Include directives.
//==================================================================================================
#include "types.h"
#include "hw_cfg.h"
#include "register_macros.h"

//==================================================================================================
// Structures & enumerations.
//==================================================================================================
typedef enum    /* Interrupt Vector */
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
} InterruptVectorEnum;

typedef enum    /* External Interrupt */
{
    EXT_INT_0,
    EXT_INT_1
} ExtIntEnum;

typedef enum    /* External Interrupt Sense Control */
{
    EXT_INT_SC_LOW,
    EXT_INT_SC_ANY,
    EXT_INT_SC_FALLING,
    EXT_INT_SC_RISING,
} ExtIntSenseEnum;



//==================================================================================================
// Function prototypes.
//==================================================================================================
/*
 *  @brief Initialize an external interrupt with a specified edge sensitivity.
 *  @param Interrupt
 *      External interrupt to configure.
 *  @param SenseControl
 *      Edge sensitivity of the interrupt.
 *  @returns
 */
void ISR_ExternalInterruptInit(ExtIntEnum Interrupt, ExtIntSenseEnum SenseControl);

/*
 *  @brief Enable a specific external interrupt.
 *  @param
 *  @returns
 */
void ISR_ExternalInterruptEnable(ExtIntEnum Interrupt);

/*
 *  @brief Disable a specific external interrupt.
 *  @param
 *  @returns
 */
void ISR_ExternalInterruptDisable(ExtIntEnum Interrupt);

/*
 *  @brief Make specified function the interrupt handler of the given interrupt.
 *  @param
 *  @returns
 */
void ISR_AddInterruptHandler(VoidFunctionPtr Function, InterruptVectorEnum InterruptVector);

//==================================================================================================
// Inline function definitions.
//==================================================================================================
/*
 *  @brief Enable interrupts globally.
 *  @param
 *  @returns
 */
static inline void ISR_GlobalInterruptEnable(void)
{
    asm("SEI");
}

/*
 *  @brief Disable interrupts globally.
 *  @param
 *  @returns
 */
static inline void ISR_GlobalInterruptDisable(void)
{
    asm("CLI");
}

//--------------------------------------------------------------------------------------------------
// Function : ISR_SPI_InterruptEnable
// Brief    : Enable SPI transfer complete interrupt.
//--------------------------------------------------------------------------------------------------
static inline void ISR_SPI_InterruptEnable(void)
{
    SetBit(SPCR, SPIE);
}

//--------------------------------------------------------------------------------------------------
// Function : ISR_SPI_InterruptDisable
// Brief    : Disable SPI transfer complete interrupt.
//--------------------------------------------------------------------------------------------------
static inline void ISR_SPI_InterruptDisable(void)
{
    ClearBit(SPCR, SPIE);
}

#endif // _ISR_H_