//==================================================================================================
//
// File name: timer.h
//
// Purpose:
//
//==================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_


//==================================================================================================
// Include directives
//==================================================================================================
#include "types.h"
#include "hw_cfg.h"


//==================================================================================================
// Preprocessor definitions
//==================================================================================================


//==================================================================================================
// Structures and enumerations
//==================================================================================================
typedef struct Timer_8BitType
{
    volatile uint8_t* OutputCompRegA;
    volatile uint8_t* OutputCompRegB;
    volatile uint8_t* CtrlRegA;
    volatile uint8_t* CtrlRegB;
    volatile uint8_t* IntMaskReg;
} Timer_8BitType;

typedef struct Timer_16BitType
{
    volatile uint16_t* OutputCompRegA;
    volatile uint16_t* OutputCompRegB;
    volatile uint16_t* InputCaptureReg;
    volatile uint8_t* CtrlRegA;
    volatile uint8_t* CtrlRegB;
    volatile uint8_t* CtrlRegC;
    volatile uint8_t* IntMaskReg;
} Timer_16BitType;


//==================================================================================================
// External variable declarations
//==================================================================================================
#if defined(TIMER_0)
    extern Timer_8BitType* Timer0;
#endif

#if defined(TIMER_1)
    extern Timer_16BitType* Timer1;
#endif

#if defined(TIMER_2)
    extern Timer_8BitType* Timer2;
#endif

//==================================================================================================
// Function prototypes
//==================================================================================================


#endif // _TIMER_H_