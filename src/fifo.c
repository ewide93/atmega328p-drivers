//==================================================================================================
//
// File name: fifo.c
//
// Purpose: Implementation of circular data structure with a "First In, First Out" principle.
//          Note: Wrap-around logic requires the size of the underlying buffer
//                to be a power of two.
//
//==================================================================================================

//==================================================================================================
// Include directives
//==================================================================================================
#include "fifo.h"

//==================================================================================================
// External function definitions
//==================================================================================================
/*
 *  @brief Initialization function for fifo structures.
 *  @param Fifo
 *      Pointer to fifo structure.
 *  @param Buffer
 *      Pointer to buffer where data for the fifo to manage is stored.
 *  @param Length
 *      Length of buffer.
 *  @returns
 */
void Fifo_Init(FifoType* Fifo, U8* Buffer, const U8 Length)
{
    Fifo->Buffer = Buffer;
    Fifo->Length = Length;
    Fifo->Mask = Length - 1;
    Fifo->Head = 0;
    Fifo->Tail = 0;
    Fifo->NofItems = 0;
}

/*
 *  @brief Write one byte of data to the fifo.
 *  @param Fifo
 *      Pointer to fifo structure.
 *  @param Data
 *      Byte to be written.
 *  @returns
 */
void Fifo_WriteByte(FifoType* Fifo, U8 Data)
{
    if (Fifo_Full(Fifo)) return;
    Fifo->Buffer[Fifo->Head] = Data;
    Fifo->Head = (Fifo->Head + 1) & Fifo->Mask;
    Fifo->NofItems++;
}

/*
 *  @brief Read one byte of data from the fifo.
 *  @param Fifo
 *      Pointer to fifo structure.
 *  @param Data
 *      Pointer to where the read data should be stored.
 *  @returns
 */
void Fifo_ReadByte(FifoType* Fifo, U8* Data)
{
    if (Fifo_Empty(Fifo)) return;
    *Data = Fifo->Buffer[Fifo->Tail];
    Fifo->Tail = (Fifo->Tail + 1) & Fifo->Mask;
    Fifo->NofItems--;
}

/*
 *  @brief Checks if a fifo structure is empty.
 *  @param Fifo
 *      Pointer to fifo structure.
 *  @returns
 *      TRUE = empty, FALSE = not empty
 */
BOOL Fifo_Empty(const FifoType* Fifo)
{
    return Fifo->NofItems == 0;
}

/*
 *  @brief Checks if a fifo structure is full.
 *  @param Fifo
 *      Pointer to fifo structure.
 *  @returns
 *      TRUE = full, FALSE = not full
 */
BOOL Fifo_Full(const FifoType* Fifo)
{
    return Fifo->NofItems == Fifo->Length;
}

/*
 *  @brief Checks a fifo structure for the number of bytes that
 *         can be written before overwrite protection kicks in.
 *  @param Fifo
 *      Pointer to fifo structure.
 *  @returns
 *      Number of available bytes that can be written.
 */
U8 Fifo_GetNofAvailable(const FifoType* Fifo)
{
    return (Fifo->Length - Fifo->NofItems);
}

/*
 *  @brief Checks a fifo structure for the number of bytes
 *         that are in the underlying buffer that has not been read.
 *  @param Fifo
 *      Pointer to fifo strcture.
 *  @returns
 *      Number of bytes that can be read.
 */
U8 Fifo_GetNofItems(const FifoType* Fifo)
{
    return Fifo->NofItems;
}

/*
 *  @brief Resets a fifo structure and zero-fills it's underlying buffer.
 *  @param Fifo
 *      Pointer to fifo structure.
 *  @returns
 */
void Fifo_Clear(FifoType* Fifo)
{
    for (U8 i = 0; i < Fifo->Length; i++)
    {
        Fifo->Buffer[i] = 0;
    }

    Fifo->Head = 0;
    Fifo->Tail = 0;
    Fifo->NofItems = 0;
}



