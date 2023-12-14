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

typedef enum IO_PORT
{
    IO_PORT_B,
    IO_PORT_C,
    IO_PORT_D
} IO_PORT;

typedef struct
{
    volatile uint8_t PIN;
    volatile uint8_t DDR;
    volatile uint8_t PORT;
} IOPortType;

typedef struct
{
    IOPortType* IOPort;
    uint8_t PinNum;
} PinType;


//==================================================================================================
// External variables
//==================================================================================================
extern IOPortType* IOPortB;
extern IOPortType* IOPortC;
extern IOPortType* IOPortD;
extern PinType* Pin2;
extern PinType* Pin3;
extern PinType* Pin4;
extern PinType* Pin5;


//==================================================================================================
// Function prototypes.
//==================================================================================================
void Digital_PinInit(PinType* Pin, enum IO_MODE Mode);
void Digital_SetPin(PinType* Pin);
void Digital_TogglePin(PinType* Pin);
bool Digital_ReadPin(PinType* Pin);


#endif // _DIGITAL_H_