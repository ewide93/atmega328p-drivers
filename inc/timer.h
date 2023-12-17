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
// Structure definitions
//==================================================================================================
typedef struct Timer0Type
{
    volatile uint8_t CtrlRegA;
    volatile uint8_t CtrlRegB;
    volatile uint8_t CntReg;
    volatile uint8_t OutCompRegA;
    volatile uint8_t OutCompRegB;
} Timer0Type;

typedef struct Timer1Type
{
    volatile uint8_t CtrlRegA;
    volatile uint8_t CtrlRegB;
    volatile uint8_t CtrlRegC;
    volatile const uint8_t PadByte;
    volatile uint16_t CntReg;
    volatile uint16_t InputCaptReg;
    volatile uint16_t OutCompRegA;
    volatile uint16_t OutCompRegB;
} Timer1Type;

typedef struct Timer2Type
{
    volatile uint8_t CtrlRegA;
    volatile uint8_t CtrlRegB;
    volatile uint8_t CntReg;
    volatile uint8_t OutCompRegA;
    volatile uint8_t OutCompRegB;
    volatile const uint8_t PadByte;
    volatile uint8_t AsyncStatusReg;
} Timer2Type;

typedef struct TimerType
{
    void* Timer;
    uint8_t TimerID;
} TimerType;


//==================================================================================================
// Enumerations
//==================================================================================================
typedef enum TIMER_MODE
{
    TIMER_MODE_NORMAL,
    TIMER_MODE_CTC,
    TIMER_MODE_FAST_PWM,
    TIMER_MODE_PHASE_CORRECT_PWM,
    TIMER_MODE_PHASE_FREQ_CORRECT_PWM,
} TIMER_MODE;


//==================================================================================================
// External variable declarations
//==================================================================================================
extern TimerType* Timer0;
extern TimerType* Timer1;
extern TimerType* Timer2;


//==================================================================================================
// Function prototypes
//==================================================================================================
void Timer_Init(TimerType* Timer, enum TIMER_MODE Mode);


#endif // _TIMER_H_