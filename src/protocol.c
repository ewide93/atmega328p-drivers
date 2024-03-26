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
static void Protocol_AssembleAckPDU(void);
static void Protocol_AssembleNackPDU(void);
static void Protocol_HandleMessage(void);
static void Protocol_SendResponse(const PDUType* PDU);

//==================================================================================================
// Structures & enumerations.
//==================================================================================================
typedef struct
{
    PDUType RxPDU;
    PDUType TxPDU;
    FSMType State;
    BOOL Initialized;
    BOOL RxMessageReady;
    BOOL TxMessageReady;
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

static void Protocol_AssembleAckPDU(void)
{
    U8 DummyData[PROTOCOL_PAYLOAD_SIZE] = { 0 };
    Protocol_AssembleTxPDU(&Protocol.TxPDU, PROTOCOL_ACK, DummyData);
}

static void Protocol_AssembleNackPDU(void)
{
    U8 DummyData[PROTOCOL_PAYLOAD_SIZE] = { 0 };
    Protocol_AssembleTxPDU(&Protocol.TxPDU, PROTOCOL_NACK, DummyData);
}

static void Protocol_HandleMessage(void)
{
    /* TODO: Find more elegant solution to handle different messages. */
    switch (Protocol.RxPDU.FunctionCode)
    {
        case FUNC_CODE_TEST:
        {
            U8 Payload = Protocol.RxPDU.Data[0];
            Digital_TogglePin(Payload);
            Protocol_AssembleAckPDU();
            break;
        }
        default:
        {
            Protocol_AssembleNackPDU();
            break;
        }
    }
}

static void Protocol_SendResponse(const PDUType* PDU)
{
    U8* PDUPtr = (U8*)PDU;
    for (U8 i = 0; i < PROTOCOL_PDU_SIZE; i++)
    {
        UART_WriteByte(*PDUPtr + i);
    }
}

//==================================================================================================
// External function definitions
//==================================================================================================
void Protocol_Init(void)
{
    if (!Protocol.Initialized)
    {
        /* Initialize PDU structures. */
        Protocol.TxPDU.FunctionCode = 0;
        Protocol.RxPDU.FunctionCode = 0;

        for (U8 i = 0; i < PROTOCOL_PAYLOAD_SIZE; i++)
        {
            Protocol.TxPDU.Data[i] = 0;
            Protocol.RxPDU.Data[i] = 0;
        }
        Protocol.TxPDU.LRC = 0;
        Protocol.RxPDU.LRC = 0;

        /* Initialize FSM structure. */
        FSM_Init(&Protocol.State);

        /* Initialize status booleans. */
        Protocol.TxMessageReady = FALSE;
        Protocol.RxMessageReady = FALSE;
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
        case PROTOCOL_STATE_IDLE:
        {
            break;
        }
        case PROTOCOL_STATE_RX:
        {
            if (Protocol.RxMessageReady)
            {
                /* Calculate & compare LRC checksums. */
                if ( !(Protocol.RxPDU.LRC == Protocol_CalcLRC(&Protocol.RxPDU)) )
                {
                    Protocol_AssembleNackPDU();
                }
                else
                {
                    Protocol_HandleMessage();
                }

                Protocol_RxMessageHandledEvent();
            }

            break;
        }
        case PROTOCOL_STATE_TX:
        {
            if (Protocol.TxMessageReady)
            {
                Protocol_SendResponse(&Protocol.TxPDU);
                Protocol_TxMessageHandledEvent();
            }
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

PDUType* Protocol_GetRxPDUPtr(void)
{
    return &Protocol.RxPDU;
}

PDUType* Protocol_GetTxPDUPtr(void)
{
    return &Protocol.TxPDU;
}

void Protocol_MessageTxEvent(void)
{
    FSM_SetState(&Protocol.State, PROTOCOL_STATE_IDLE);
    UART_TxDisable();
    UART_RxEnable();
}

void Protocol_MessageRxEvent(void)
{
    FSM_SetState(&Protocol.State, PROTOCOL_STATE_RX);
    Protocol.RxMessageReady = TRUE;
    UART_RxDisable();
}

void Protocol_RxMessageHandledEvent(void)
{
    FSM_SetState(&Protocol.State, PROTOCOL_STATE_TX);
    Protocol.RxMessageReady = FALSE;
    Protocol.TxMessageReady = TRUE;
    UART_TxEnable();
}

void Protocol_TxMessageHandledEvent(void)
{
    Protocol.TxMessageReady = FALSE;
}



void Protocol_AssembleRxPDU(FifoType* Fifo, PDUType* PDU)
{
    Fifo_ReadByte(Fifo, &PDU->FunctionCode);
    for (U8 i = 0; i < PROTOCOL_PAYLOAD_SIZE; i++)
    {
        Fifo_ReadByte(Fifo, &PDU->Data[i]);
    }
    Fifo_ReadByte(Fifo, &PDU->LRC);
}

void Protocol_AssembleTxPDU(PDUType* PDU, const U8 FunctionCode, const U8* Data)
{
    PDU->FunctionCode = FunctionCode;
    for (U8 i = 0; i < PROTOCOL_PAYLOAD_SIZE; i++)
    {
        PDU->Data[i] = Data[i];
    }
    PDU->LRC = LRC_Calc((U8*)PDU, PROTOCOL_FUNC_CODE_SIZE + PROTOCOL_PAYLOAD_SIZE);
}

void Protocol_SendACK(void)
{
    UART_WriteByte(PROTOCOL_ACK);
}

void Protocol_SendNACK(void)
{
    UART_WriteByte(PROTOCOL_NACK);
}


