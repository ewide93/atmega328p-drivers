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
#define IO_PORT_B_ADDRESS ((IOPortType*)0x23U)
#define IO_PORT_C_ADDRESS ((IOPortType*)0x26U)
#define IO_PORT_D_ADDRESS ((IOPortType*)0x29U)
#define PIN_NUM_MAX       (7U)


//==================================================================================================
// Definition of external variables
//==================================================================================================
static PinType Pin2_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 2 };
PinType* Pin2 = &Pin2_Local;

static PinType Pin3_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 3 };
PinType* Pin3 = &Pin3_Local;

static PinType Pin4_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 4 };
PinType* Pin4 = &Pin4_Local;

static PinType Pin5_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 5 };
PinType* Pin5 = &Pin5_Local;

static PinType Pin6_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 6 };
PinType* Pin6 = &Pin6_Local;

static PinType Pin7_Local = { .IOPort = IO_PORT_D_ADDRESS, .PinNum = 7 };
PinType* Pin7 = &Pin7_Local;

static PinType Pin8_Local = { .IOPort = IO_PORT_B_ADDRESS, .PinNum = 0 };
PinType* Pin8 = &Pin8_Local;

static PinType Pin9_Local = { .IOPort = IO_PORT_B_ADDRESS, .PinNum = 1 };
PinType* Pin9 = &Pin9_Local;

static PinType Pin10_Local = { .IOPort = IO_PORT_B_ADDRESS, .PinNum = 2 };
PinType* Pin10 = &Pin10_Local;

static PinType Pin11_Local = { .IOPort = IO_PORT_B_ADDRESS, .PinNum = 3 };
PinType* Pin11 = &Pin11_Local;

static PinType Pin12_Local = { .IOPort = IO_PORT_B_ADDRESS, .PinNum = 4 };
PinType* Pin12 = &Pin12_Local;

static PinType Pin13_Local = { .IOPort = IO_PORT_B_ADDRESS, .PinNum = 5 };
PinType* Pin13 = &Pin13_Local;


//==================================================================================================
// Function definitions.
//==================================================================================================
void Digital_PinInit(PinType* Pin, IOModeEnum Mode)
{
    if (Pin->PinNum > PIN_NUM_MAX) return;
    if (Pin->IOPort == IO_PORT_C_ADDRESS && Pin->PinNum > (PIN_NUM_MAX - 1)) return;

    switch (Mode)
    {
        case IO_MODE_INPUT: { break; }
        case IO_MODE_INPUT_PULLUP: { Pin->IOPort->DataReg |= (1 << Pin->PinNum); break; }
        case IO_MODE_OUTPUT: { Pin->IOPort->DataDirReg |= (1 << Pin->PinNum); break; }
        default: { break; }
    }
}

void Digital_SetPin(PinType* Pin)
{
    Pin->IOPort->DataReg |= (1 << Pin->PinNum);
}

void Digital_ClearPin(PinType* Pin)
{
    Pin->IOPort->DataReg &= ~(1 << Pin->PinNum);
}

void Digital_TogglePin(PinType* Pin)
{
    Pin->IOPort->DataReg ^= (1 << Pin->PinNum);
}

bool Digital_ReadPin(PinType* Pin)
{
    return Pin->IOPort->InputPinReg & (1 << Pin->PinNum);
}

