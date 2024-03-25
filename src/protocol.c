//==================================================================================================
//
// File name: protocol.c
//
// Purpose: Implementation of a messaging protocol over UART.
//
//==================================================================================================

//==================================================================================================
// Include directives
//==================================================================================================
#include "protocol.h"
#include "digital.h"

//==================================================================================================
// Local preprocessor definitions
//==================================================================================================

//==================================================================================================
// Local function prototypes
//==================================================================================================
static U8 Protocol_CalcLRC(const PDUType* PDU);
static void Protocol_HandleMessage(void);

//==================================================================================================
// Structures & enumerations.
//==================================================================================================
typedef struct
{
    PDUType PDU;
    FSMType State;
    BOOL Initialized;
    BOOL MessageReady;
} ProtocolHandlerType;

//==================================================================================================
// Local variables
//==================================================================================================
static ProtocolHandlerType Protocol;

//==================================================================================================
// Local function definitions
//==================================================================================================
static U8 Protocol_CalcLRC(const PDUType* PDU)
{
    return LRC_Calc((U8*)PDU, (U8)(PROTOCOL_PDU_SIZE - 1U));
}

static void Protocol_HandleMessage(void)
{
    /* TODO: Find more elegant solution to handle different messages. */
    switch (Protocol.PDU.FunctionCode)
    {
        case FUNC_CODE_TEST:
        {
            U8 Payload = Protocol.PDU.Data[0];
            Digital_TogglePin(Payload);
            Protocol_SendACK();
            break;
        }
        default:
        {
            Protocol_SendNACK();
            break;
        }
    }
}

//==================================================================================================
// External function definitions
//==================================================================================================
void Protocol_Init(void)
{
    if (!Protocol.Initialized)
    {
        /* Initialize PDU structure. */
        Protocol.PDU.FunctionCode = 0;
        for (U8 i = 0; i < PROTOCOL_PAYLOAD_SIZE; i++)
        {
            Protocol.PDU.Data[i] = 0;
        }
        Protocol.PDU.LRC = 0;

        /* Initialize FSM structure. */
        FSM_Init(&Protocol.State);

        /* Initialize status booleans. */
        Protocol.MessageReady = FALSE;
        Protocol.Initialized = TRUE;
    }
}

void Protocol_Run(void)
{
    U8 State = FSM_GetCurrentState(&Protocol.State);

    switch (State)
    {
        case PROTOCOL_STATE_NONE:
        {
            break;
        }
        case PROTOCOL_STATE_RX:
        {
            if (Protocol.MessageReady)
            {
                /* Calculate & compare LRC checksums. */
                if ( !(Protocol.PDU.LRC == Protocol_CalcLRC(&Protocol.PDU)) )
                {
                    Protocol_SendNACK();
                }
                else
                {
                    Protocol_HandleMessage();
                }

                Protocol.MessageReady = FALSE;
            }

            break;
        }
        case PROTOCOL_STATE_TX:
        {
            break;
        }
        case PROTOCOL_STATE_ERROR:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

PDUType* Protocol_GetPDUPtr(void)
{
    return &Protocol.PDU;
}

void Protocol_AssemblePDU(FifoType* Fifo, PDUType* PDU)
{
    Fifo_ReadByte(Fifo, &PDU->FunctionCode);
    for (U8 i = 0; i < PROTOCOL_PAYLOAD_SIZE; i++)
    {
        Fifo_ReadByte(Fifo, &PDU->Data[i]);
    }
    Fifo_ReadByte(Fifo, &PDU->LRC);
    Protocol.MessageReady = TRUE;
}

void Protocol_SendACK(void)
{
    UART_WriteByte(PROTOCOL_ACK);
}

void Protocol_SendNACK(void)
{
    UART_WriteByte(PROTOCOL_NACK);
}


