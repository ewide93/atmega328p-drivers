//==================================================================================================
//
// File: types.h
//
// Purpose: Header file for easy inclusion of standard types.
//
//==================================================================================================
#ifndef _TYPES_H_
#define _TYPES_H_


//==================================================================================================
// Include directives.
//==================================================================================================
#include <stdint.h>
#include <stdbool.h>


//==================================================================================================
// Variable alias definitions.
//==================================================================================================
typedef unsigned char         U8;
typedef unsigned short        U16;
typedef unsigned int          U32;
typedef unsigned long long    U64;

typedef signed char           S8;
typedef signed short          S16;
typedef signed int            S32;
typedef signed long long      S64;

typedef float                 F32;

typedef bool                  BOOL;


//==================================================================================================
// Function pointer type definitions.
//==================================================================================================
typedef void (*VoidFunctionPtr)(void);


#endif // _TYPES_H_