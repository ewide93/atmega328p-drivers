//==================================================================================================
//
// File: isr.h
//
// Purpose:
//
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
void ISR_GlobalInterruptEnable(void);
void ISR_GlobalInterruptDisable(void);
void ISR_ExternalInterruptInit(EXT_INT Interrupt, EXT_INT_SC SenseControl);
void ISR_ExternalInterruptEnable(EXT_INT Interrupt);
void ISR_ExternalInterruptDisable(EXT_INT Interrupt);

#endif // _ISR_H_