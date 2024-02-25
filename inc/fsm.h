//==================================================================================================
//
// File name: fsm.h
//
// Purpose: Implementation of generic type representing a Finite State Machine.
//          Note: This implementation relies on state enumerations not using
//                the number 0 for any purpose. The desired initial state should be
//                enumerated as 1.
//
//==================================================================================================
#ifndef _FSM_H_
#define _FSM_H_


//==================================================================================================
// Include directives
//==================================================================================================
#include "types.h"

//==================================================================================================
// Preprocessor definitions
//==================================================================================================
#define FSM_STATE_NONE      (0U)
#define FSM_STATE_INITIAL   (1U)

//==================================================================================================
// Structures and enumerations
//==================================================================================================
typedef struct FSM
{
    U8 CurrentState;
    U8 PreviousState;
} FSMType;


//==================================================================================================
// External variable declarations
//==================================================================================================


//==================================================================================================
// Function prototypes
//==================================================================================================
void FSM_Init(FSMType* StateMachine);
void FSM_SetState(FSMType* StateMachine, const U8 NewState);
U8 FSM_GetCurrentState(const FSMType* StateMachine);
U8 FSM_GetPreviousState(const FSMType* StateMachine);

#endif // _FSM_H_