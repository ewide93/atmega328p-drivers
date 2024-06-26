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
// Structures and enumerations
//==================================================================================================
typedef struct FifoType
{
    U8* Buffer;
    U8 Length;
    U8 Mask;
    U8 Head;
    U8 Tail;
    U8 NofItems;
} FifoType;

//==================================================================================================
// Function prototypes
//==================================================================================================
void Fifo_Init(FifoType* Fifo, U8* Buffer, const U8 Length);
void Fifo_WriteByte(FifoType* Fifo, U8 Data);
void Fifo_ReadByte(FifoType* Fifo, U8* Data);
BOOL Fifo_Empty(const FifoType* Fifo);
BOOL Fifo_Full(const FifoType* Fifo);
U8 Fifo_GetNofAvailable(const FifoType* Fifo);
U8 Fifo_GetNofItems(const FifoType* Fifo);
void Fifo_Clear(FifoType* Fifo);

#endif // _FIFO_H_