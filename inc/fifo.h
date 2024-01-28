//==================================================================================================
//
// File name: fifo.h
//
// Purpose:
//
//==================================================================================================
#ifndef _FIFO_H_
#define _FIFO_H_


//==================================================================================================
// Include directives
//==================================================================================================
#include "types.h"


//==================================================================================================
// Preprocessor definitions
//==================================================================================================


//==================================================================================================
// Structures and enumerations
//==================================================================================================
typedef struct FifoType
{
    U8* Buffer;
    U8 Size;
    U8 Mask;
    U8 Head;
    U8 Tail;
} FifoType;

//==================================================================================================
// External variable declarations
//==================================================================================================


//==================================================================================================
// Function prototypes
//==================================================================================================
void Fifo_Init(FifoType* Fifo, U8* Buffer, const U8 Size);
void Fifo_WriteByte(FifoType* Fifo, U8 Data);
void Fifo_ReadByte(FifoType* Fifo, U8* Data);
BOOL Fifo_Empty(FifoType* Fifo);
BOOL Fifo_Full(FifoType* Fifo);

#endif // _FIFO_H_