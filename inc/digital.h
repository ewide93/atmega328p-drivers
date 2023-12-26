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
typedef enum IO_MODE
{
    IO_MODE_INPUT,
    IO_MODE_INPUT_PULLUP,
    IO_MODE_OUTPUT
} IO_MODE;

typedef struct
{
    volatile uint8_t InputPinReg;
    volatile uint8_t DataDirReg;
    volatile uint8_t DataReg;
} IOPortType;

typedef struct
{
    IOPortType* IOPort;
    uint8_t PinNum;
} PinType;


//==================================================================================================
// External variables
//==================================================================================================
extern PinType* Pin2;
extern PinType* Pin3;
extern PinType* Pin4;
extern PinType* Pin5;
extern PinType* Pin6;
extern PinType* Pin7;
extern PinType* Pin8;
extern PinType* Pin9;
extern PinType* Pin10;
extern PinType* Pin11;
extern PinType* Pin12;
extern PinType* Pin13;


//==================================================================================================
// Function prototypes.
//==================================================================================================
void Digital_PinInit(PinType* Pin, enum IO_MODE Mode);
void Digital_SetPin(PinType* Pin);
void Digital_ClearPin(PinType* Pin);
void Digital_TogglePin(PinType* Pin);
bool Digital_ReadPin(PinType* Pin);


#endif // _DIGITAL_H_