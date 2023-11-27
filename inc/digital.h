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
#ifdef DIGITAL_PIN_0
    extern Digital_PinType* Pin0;
#endif

#if defined(DIGITAL_PIN_1)
    extern Digital_PinType* Pin1;
#endif

#if defined(DIGITAL_PIN_2)
    extern Digital_PinType* Pin2;
#endif

#if defined(DIGITAL_PIN_3)
    extern Digital_PinType* Pin3;
#endif

#if defined(DIGITAL_PIN_4)
    extern Digital_PinType* Pin4;
#endif

#if defined(DIGITAL_PIN_5)
    extern Digital_PinType* Pin5;
#endif

#if defined(DIGITAL_PIN_6)
    extern Digital_PinType* Pin6;
#endif

#if defined(DIGITAL_PIN_7)
    extern Digital_PinType* Pin7;
#endif

#if defined(DIGITAL_PIN_8)
    extern Digital_PinType* Pin8;
#endif

#if defined(DIGITAL_PIN_9)
    extern Digital_PinType* Pin9;
#endif

#if defined(DIGITAL_PIN_10)
    extern Digital_PinType* Pin10;
#endif

#if defined(DIGITAL_PIN_11)
    extern Digital_PinType* Pin11;
#endif

#if defined(DIGITAL_PIN_12)
    extern Digital_PinType* Pin12;
#endif

#if defined(DIGITAL_PIN_13)
    extern Digital_PinType* Pin13;
#endif



//==================================================================================================
// Function prototypes.
//==================================================================================================
void Digital_PinInit(Digital_PinType* PinPtr, enum IO_PORT Port, enum IO_MODE Mode, uint8_t PinNum);
void Digital_SetPin(Digital_PinType* PinPtr);
void Digital_ClrPin(Digital_PinType* PinPtr);
void Digital_TogglePin(Digital_PinType* PinPtr);
bool Digital_ReadPin(Digital_PinType* PinPtr);


#endif // _DIGITAL_H_