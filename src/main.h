/********************************************************************************
* main.h: Header containing include directives to libraries that are expected 
*         to be needed in most of the project files.
********************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#ifndef F_CPU
    #define F_CPU 16000000UL
#endif

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#endif // _MAIN_H_