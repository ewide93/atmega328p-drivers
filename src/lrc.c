//==================================================================================================
//
// File name: lrc.c
//
// Purpose: Implements functionality for performing Longitudinal Redundancy Checking.
//
//==================================================================================================

//==================================================================================================
// Include directives
//==================================================================================================
#include "lrc.h"

//==================================================================================================
// External function definitions
//==================================================================================================
U8 LRC_Calc(const U8* Data, const U8 Length)
{
    U8 LRC = 0;
    for (U8 i = 0; i < Length; i++)
    {
        LRC += Data[i];
    }
    return ((0xFF - LRC) + 1);
}



