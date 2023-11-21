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
#include <avr/interrupt.h>


//==================================================================================================
// Preprocessor definitions.
//==================================================================================================
#define EXT_INT0_VECTOR 0
#define EXT_INT1_VECTOR 1


//==================================================================================================
// Definitions of enumerations and structures.
//==================================================================================================

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

void ISR_AddInterruptHandler(VoidFunctionPtr Function, uint8_t Interrupt);

#endif // _ISR_H_