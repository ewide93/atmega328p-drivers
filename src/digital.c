//==================================================================================================
//
// File: digital.c
//
// Purpose: Header-file containing function and variable definitions related to
//          the configuration and use of digital pins.
//
//==================================================================================================


//==================================================================================================
// Include directives.
//==================================================================================================
#include "digital.h"


//==================================================================================================
// Local macro definitions.
//==================================================================================================
#define PIN_NUM_MAX 7


//==================================================================================================
// Definitions of static objects and external object handles.
//==================================================================================================
#if defined(DIGITAL_PIN_0)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin0 = { 0 };
        Digital_PinType* Pin0 = &Local_Pin0;
    #endif
#endif

#if defined(DIGITAL_PIN_1)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin1 = { 0 };
        Digital_PinType* Pin1 = &Local_Pin1;
    #endif
#endif

#if defined(DIGITAL_PIN_2)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin2 = { 0 };
        Digital_PinType* Pin2 = &Local_Pin2;
    #endif
#endif

#if defined(DIGITAL_PIN_3)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin3 = { 0 };
        Digital_PinType* Pin3 = &Local_Pin3;
    #endif
#endif


#if defined(DIGITAL_PIN_4)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin4 = { 0 };
        Digital_PinType* Pin4 = &Local_Pin4;
    #endif
#endif

#if defined(DIGITAL_PIN_5)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin5 = { 0 };
        Digital_PinType* Pin5 = &Local_Pin5;
    #endif
#endif

#if defined(DIGITAL_PIN_6)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin6 = { 0 };
        Digital_PinType* Pin6 = &Local_Pin6;
    #endif
#endif

#if defined(DIGITAL_PIN_7)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin7 = { 0 };
        Digital_PinType* Pin7 = &Local_Pin7;
    #endif
#endif

#if defined(DIGITAL_PIN_8)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin8 = { 0 };
        Digital_PinType* Pin8 = &Local_Pin8;
    #endif
#endif

#if defined(DIGITAL_PIN_9)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin9 = { 0 };
        Digital_PinType* Pin9 = &Local_Pin9;
    #endif
#endif

#if defined(DIGITAL_PIN_10)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin10 = { 0 };
        Digital_PinType* Pin10 = &Local_Pin10;
    #endif
#endif

#if defined(DIGITAL_PIN_11)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin11 = { 0 };
        Digital_PinType* Pin11 = &Local_Pin11;
    #endif
#endif

#if defined(DIGITAL_PIN_12)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin12 = { 0 };
        Digital_PinType* Pin12 = &Local_Pin12;
    #endif
#endif

#if defined(DIGITAL_PIN_13)
    #if defined(CONFLICTING_PIN) || defined(ANOTHER_CONFILCTING_PIN)
        #error "Conflicting pin assignment."
    #else
        static Digital_PinType Local_Pin13 = { 0 };
        Digital_PinType* Pin13 = &Local_Pin13;
    #endif
#endif


//==================================================================================================
// Function definitions.
//==================================================================================================
void Digital_PinInit(Digital_PinType* PinPtr, enum IO_PORT Port, enum IO_MODE Mode, uint8_t PinNum)
{
    if (PinPtr->PinNum > PIN_NUM_MAX) return;
    if (Port == IO_PORT_C && PinPtr->PinNum > (PIN_NUM_MAX - 1)) return;
    PinPtr->PinNum = PinNum;

    switch (Port)
    {
        case IO_PORT_B:
        {
            PinPtr->DDR = &DDRB;
            PinPtr->PIN = &PINB;
            PinPtr->PORT = &PORTB;
            break;
        }
        case IO_PORT_C:
        {
            PinPtr->DDR = &DDRC;
            PinPtr->PIN = &PINC;
            PinPtr->PORT = &PORTC;
            break;
        }
        case IO_PORT_D:
        {
            PinPtr->DDR = &DDRD;
            PinPtr->PIN = &PIND;
            PinPtr->PORT = &PORTD;
            break;
        }
        default:
        {
            break;
        }
    }

    switch (Mode)
    {
        case IO_MODE_INPUT:
        {
            break;
        }
        case IO_MODE_INPUT_PULLUP:
        {
            *(PinPtr->PORT) |= (1 << PinPtr->PinNum);
            break;
        }
        case IO_MODE_OUTPUT:
        {
            *(PinPtr->DDR) |= (1 << PinPtr->PinNum);
            break;
        }
        default:
        {
            break;
        }
    }
    return;
}

void Digital_SetPin(Digital_PinType* PinPtr)
{
    *(PinPtr->PORT) |= (1 << PinPtr->PinNum);
    return;
}

void Digital_ClrPin(Digital_PinType* PinPtr)
{
    *(PinPtr->PORT) &= ~(1 << PinPtr->PinNum);
    return;
}

void Digital_TogglePin(Digital_PinType* PinPtr)
{
    *(PinPtr->PORT) ^= (1 << PinPtr->PinNum);
    return;
}

bool Digital_ReadPin(Digital_PinType* PinPtr)
{
    return (*(PinPtr->PIN) & (1 << PinPtr->PinNum));
}

