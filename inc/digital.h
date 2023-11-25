//==================================================================================================
//
// File: digital.h
//
// Purpose: Header-file containing type-definitions and function prototypes related to
//          the configuration and use of digital pins.
//
//==================================================================================================
#ifndef _DIGITAL_H
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

typedef struct Digital_PinType
{
    volatile uint8_t* PORT;
    volatile uint8_t* DDR;
    volatile uint8_t* PIN;
    uint8_t PinNum;
} Digital_PinType;


//==================================================================================================
// Declaration of object handles.
//==================================================================================================
extern Digital_PinType* Pin2;
extern Digital_PinType* Pin3;
extern Digital_PinType* Pin4;
extern Digital_PinType* Pin5;


//==================================================================================================
// Function prototypes.
//==================================================================================================
void Digital_PinInit(Digital_PinType* PinPtr, enum IO_PORT Port, enum IO_MODE Mode, uint8_t PinNum);
void Digital_SetPin(Digital_PinType* PinPtr);
void Digital_ClrPin(Digital_PinType* PinPtr);
void Digital_TogglePin(Digital_PinType* PinPtr);
bool Digital_ReadPin(Digital_PinType* PinPtr);


#endif // _DIGITAL_H_