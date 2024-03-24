//==================================================================================================
//
// File: digital.h
//
// Purpose: Header-file containing type-definitions and function prototypes related to
//          the configuration and use of digital pins.
//
//==================================================================================================
#ifndef _DIGITAL_H_
#define _DIGITAL_H_


//==================================================================================================
// Include directives.
//==================================================================================================
#include "hw_cfg.h"
#include "types.h"


//==================================================================================================
// Definitions of enumerations and structures.
//==================================================================================================
typedef enum IOMode
{
    IO_MODE_INPUT,
    IO_MODE_INPUT_PULLUP,
    IO_MODE_OUTPUT
} IOModeEnum;

//==================================================================================================
// Function prototypes.
//==================================================================================================
void Digital_PinInit(const U8 Pin, const IOModeEnum Mode);
void Digital_SetPin(const U8 Pin);
void Digital_ClearPin(const U8 Pin);
void Digital_TogglePin(const U8 Pin);
BOOL Digital_ReadPin(const U8 Pin);

#endif // _DIGITAL_H_