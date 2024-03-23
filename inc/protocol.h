//==================================================================================================
//
// File name: protocol.h
//
// Purpose: Implementation of a messaging protocol over UART.
//
//==================================================================================================
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_


//==================================================================================================
// Include directives
//==================================================================================================
#include "types.h"
#include "fifo.h"
#include "lrc.h"
#include "uart.h"

//==================================================================================================
// Preprocessor definitions
//==================================================================================================
#define PROTOCOL_FUNC_CODE_SIZE (1U)
#define PROTOCOL_PAYLOAD_SIZE   (6U)
#define PROTOCOL_LRC_SIZE       (1U)
#define PROTOCOL_PDU_SIZE       ((U8)(PROTOCOL_FUNC_CODE_SIZE + PROTOCOL_PAYLOAD_SIZE + PROTOCOL_LRC_SIZE))

#define PROTOCOL_ACK            (0x55U)
#define PROTOCOL_NACK           (0xAAU)

//==================================================================================================
// Structures and enumerations
//==================================================================================================
typedef struct
{
    U8 FunctionCode;
    U8 Data[PROTOCOL_PAYLOAD_SIZE];
    U8 LRC;
} PDUType;

typedef enum
{
    FUNC_CODE_TEST = 0x00,
} FunctionCodeEnum;

//==================================================================================================
// External variable declarations
//==================================================================================================


//==================================================================================================
// Function prototypes
//==================================================================================================
void Protocol_AssemblePDU(FifoType* Data);
void Protocol_MessageRecievedEvent(void);
void Protocol_SendACK(void);
void Protocol_SendNACK(void);

#endif // _PROTOCOL_H_