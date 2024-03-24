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
#define PIN_ARRAY_OFFSET  (2U)

//==================================================================================================
// Structures and enumerations
//==================================================================================================
typedef struct
{
    volatile uint8_t InputPinReg;
    volatile uint8_t DataDirReg;
    volatile uint8_t DataReg;
} IOPortType;

typedef struct
{
    IOPortType* Port;
    const U8 Shift;
} PinType;


//==================================================================================================
// Local variables
//==================================================================================================
static PinType Pins[12] =
{
    {.Port = IO_PORT_D_ADDRESS, .Shift = 2},        /* Pin 2 */
    {.Port = IO_PORT_D_ADDRESS, .Shift = 3},        /* Pin 3 */
    {.Port = IO_PORT_D_ADDRESS, .Shift = 4},        /* Pin 4 */
    {.Port = IO_PORT_D_ADDRESS, .Shift = 5},        /* Pin 5 */
    {.Port = IO_PORT_D_ADDRESS, .Shift = 6},        /* Pin 6 */
    {.Port = IO_PORT_D_ADDRESS, .Shift = 7},        /* Pin 7 */
    {.Port = IO_PORT_B_ADDRESS, .Shift = 0},        /* Pin 8 */
    {.Port = IO_PORT_B_ADDRESS, .Shift = 1},        /* Pin 9 */
    {.Port = IO_PORT_B_ADDRESS, .Shift = 2},        /* Pin 10 */
    {.Port = IO_PORT_B_ADDRESS, .Shift = 3},        /* Pin 11 */
    {.Port = IO_PORT_B_ADDRESS, .Shift = 4},        /* Pin 12 */
    {.Port = IO_PORT_B_ADDRESS, .Shift = 5},        /* Pin 13 */

};

//==================================================================================================
// Local function definitions.
//==================================================================================================
static inline BOOL Digital_PinValid(const U8 Pin)
{
    return (Pin >= 2 && Pin <= 13);
}

//==================================================================================================
// External function definitions.
//==================================================================================================
void Digital_PinInit(const U8 Pin, const IOModeEnum Mode)
{
    if (!Digital_PinValid(Pin)) return;

    switch (Mode)
    {
        case IO_MODE_INPUT:
        {
            break;
        }
        case IO_MODE_INPUT_PULLUP:
        {
            Pins[Pin - PIN_ARRAY_OFFSET].Port->DataReg |= (1 << Pins[Pin - PIN_ARRAY_OFFSET].Shift);
            break;
        }
        case IO_MODE_OUTPUT:
        {
            Pins[Pin - PIN_ARRAY_OFFSET].Port->DataDirReg |= (1 << Pins[Pin - PIN_ARRAY_OFFSET].Shift);
            break;
        }
        default: { break; }
    }
}

void Digital_SetPin(const U8 Pin)
{
    if (Digital_PinValid(Pin))
    {
        Pins[Pin - PIN_ARRAY_OFFSET].Port->DataReg |= (1 << Pins[Pin - PIN_ARRAY_OFFSET].Shift);
    }
}

void Digital_ClearPin(const U8 Pin)
{
    if (Digital_PinValid(Pin))
    {
        Pins[Pin - PIN_ARRAY_OFFSET].Port->DataReg &= ~(1 << Pins[Pin - PIN_ARRAY_OFFSET].Shift);
    }
}

void Digital_TogglePin(const U8 Pin)
{
    if (Digital_PinValid(Pin))
    {
        Pins[Pin - PIN_ARRAY_OFFSET].Port->DataReg ^= (1 << Pins[Pin - PIN_ARRAY_OFFSET].Shift);
    }
}

BOOL Digital_ReadPin(const U8 Pin)
{
    if (Digital_PinValid(Pin))
    {
        return (Pins[Pin - PIN_ARRAY_OFFSET].Port->InputPinReg & (1 << Pins[Pin - PIN_ARRAY_OFFSET].Shift));
    }
    else return FALSE;
}

