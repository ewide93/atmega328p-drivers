//==================================================================================================
//
// File: hw_cfg.h
//
// Purpose: Header-file containing hardware-specific definitions for ATmega328P.
//
//==================================================================================================
#ifndef _HW_CFG_
#define _HW_CFG_


//==================================================================================================
// Hardware specific definitions.
//==================================================================================================
#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#ifndef F_CPU
    #define F_CPU 16000000UL
#endif


//==================================================================================================
// Pin definitions, enabling/disabling of pin functions.
//==================================================================================================
// #define DIGITAL_PIN_0
// #define DIGITAL_PIN_1
#define DIGITAL_PIN_2
#define DIGITAL_PIN_3
#define DIGITAL_PIN_4
#define DIGITAL_PIN_5
// #define DIGITAL_PIN_6
// #define DIGITAL_PIN_7
// #define DIGITAL_PIN_8
// #define DIGITAL_PIN_9
// #define DIGITAL_PIN_10
// #define DIGITAL_PIN_11
// #define DIGITAL_PIN_12
// #define DIGITAL_PIN_13

//==================================================================================================
// Include directives.
//==================================================================================================
#include <avr/io.h>


#endif // _HW_CFG_