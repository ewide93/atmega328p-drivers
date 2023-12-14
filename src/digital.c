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
#define IO_PORT_B_ADDRESS (IOPortType*)(0x23)
#define IO_PORT_C_ADDRESS (IOPortType*)(0x26)
#define IO_PORT_D_ADDRESS (IOPortType*)(0x29)
#define PIN_NUM_MAX       (7U)


//==================================================================================================
// Definition of external variables
//==================================================================================================
IOPortType* IOPortB = IO_PORT_B_ADDRESS;
IOPortType* IOPortC = IO_PORT_C_ADDRESS;
IOPortType* IOPortD = IO_PORT_D_ADDRESS;

static PinType Pin2_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 2 };
PinType* Pin2 = &Pin2_Local;

static PinType Pin3_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 3 };
PinType* Pin3 = &Pin3_Local;

static PinType Pin4_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 4 };
PinType* Pin4 = &Pin4_Local;

static PinType Pin5_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 5 };
PinType* Pin5 = &Pin5_Local;


//==================================================================================================
// Function definitions.
//==================================================================================================
void Digital_PinInit(PinType* Pin, enum IO_MODE Mode)
{
    if (Pin->PinNum > PIN_NUM_MAX) return;
    if (Pin->IOPort == IO_PORT_C_ADDRESS && Pin->PinNum > (PIN_NUM_MAX - 1)) return;

    switch (Mode)
    {
        case IO_MODE_INPUT: { break; }
        case IO_MODE_INPUT_PULLUP: { Pin->IOPort->PORT |= (1 << Pin->PinNum); break; }
        case IO_MODE_OUTPUT: { Pin->IOPort->DDR |= (1 << Pin->PinNum); break; }
        default: { break; }
    }
}

void Digital_SetPin(PinType* Pin)
{
    Pin->IOPort->PORT |= (1 << Pin->PinNum);
    return;
}

void Digital_ClrPin(PinType* Pin)
{
    Pin->IOPort->PORT &= ~(1 << Pin->PinNum);
    return;
}

void Digital_TogglePin(PinType* Pin)
{
    Pin->IOPort->PORT ^= (1 << Pin->PinNum);
    return;
}

bool Digital_ReadPin(PinType* Pin)
{
    return Pin->IOPort->PIN & (1 << Pin->PinNum);
}

