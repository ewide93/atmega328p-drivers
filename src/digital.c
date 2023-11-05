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
static Digital_PinType Local_Pin3 = { 0 };
Digital_PinType* Pin3 = &Local_Pin3;
static Digital_PinType Local_Pin4 = { 0 };
Digital_PinType* Pin4 = &Local_Pin4;


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
        case INPUT:
        {
            break;
        }
        case INPUT_PULLUP:
        {
            *(PinPtr->PORT) |= (1 << PinPtr->PinNum);
            break;
        }
        case OUTPUT:
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

