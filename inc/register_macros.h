//==================================================================================================
//
// File name: register_macros.h
//
// Purpose: Collection of macros for register manipulation.
//
//==================================================================================================
#ifndef _REGISTER_MACROS_H_
#define _REGISTER_MACROS_H_


//==================================================================================================
// Preprocessor definitions
//==================================================================================================
#define SetBit(Register, Bit)                ((Register) |= (1 << (Bit)))
#define ClearBit(Register, Bit)              ((Register) &= ~(1 << (Bit)))
#define ReadBit(Register, Bit)               (((Register) & (1 << (Bit))))
#define MaskShiftLeft(Val, Mask, Shift)      (((Val) & (Mask)) << (Shift))
#define MaskShiftRight(Val, Mask, Shift)     (((Val) & (Mask)) >> (Shift))

#endif // _REGISTER_MACROS_H_