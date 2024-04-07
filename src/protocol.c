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
// Local function prototypes
//==================================================================================================
static U8 Protocol_CalcLRC(const PDUType* PDU);
static void Protocol_AssembleAckPDU(void);
static void Protocol_AssembleNackPDU(void);
static void Protocol_HandleMessage(void);
static void Protocol_SendResponse(const PDUType* PDU);
static void Protocol_AssembleRxPDU(FifoType* Fifo, PDUType* PDU);
static void Protocol_AssembleTxPDU(PDUType* PDU, const U8 FunctionCode, const U8* Data);

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
/*
 *  @brief Convenience function to calculate LRC checksum for a PDU.
 *  @param PDU
 *      Pointer to PDU for which a LRC is to be calculated.
 *  @returns
 *      LRC checksum.
 */
static U8 Protocol_CalcLRC(const PDUType* PDU)
{
    return LRC_Calc((U8*)PDU, (U8)(PROTOCOL_PDU_SIZE - 1U));
}

/*
 *  @brief Assemble a generic acknowledge response.
 *  @param
 *  @returns
 */
static void Protocol_AssembleAckPDU(void)
{
    const U8 DummyData[PROTOCOL_PAYLOAD_SIZE] = { 0 };
    Protocol_AssembleTxPDU(&Protocol.TxPDU, PROTOCOL_ACK, DummyData);
}

/*
 *  @brief Assemble a generic non-acknowledge response.
 *  @param
 *  @returns
 */
static void Protocol_AssembleNackPDU(void)
{
    const U8 DummyData[PROTOCOL_PAYLOAD_SIZE] = { 0 };
    Protocol_AssembleTxPDU(&Protocol.TxPDU, PROTOCOL_NACK, DummyData);
}

/*
 *  @brief Handle incoming messages and prepare response PDU.
 *  @param
 *  @returns
 */
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

/*
 *  @brief Load UART transmit buffer with a prepared response PDU.
 *  @param PDU
 *      Response PDU.
 *  @returns
 */
static void Protocol_SendResponse(const PDUType* PDU)
{
    const U8* PDUPtr = (U8*)PDU;
    for (U8 i = 0; i < PROTOCOL_PDU_SIZE; i++)
    {
        UART_WriteByte(*PDUPtr + i);
    }
}

//==================================================================================================
// External function definitions
//==================================================================================================
/*
 *  @brief Initialization of protocol state & data structures.
 *  @param
 *  @returns
 */
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

/*
 *  @brief Execute protocol FSM. Should be invoked periodically.
 *  @param
 *  @returns
 */
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
                // Calculate & compare LRC checksums.
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

/*
 *  @brief Event signalling a message has been transmitted.
 *  @note Called from UART interrupt context.
 *  @param
 *  @returns
 */
void Protocol_MessageTxEvent(void)
{
    FSM_SetState(&Protocol.State, PROTOCOL_STATE_IDLE);
    UART_TxDisable();
}

/*
 *  @brief Event signalling a message is ready to be handled.
 *  @note Called from UART interrupt context.
 *  @param Fifo
 *      Pointer to buffer storing data recieved over UART.
 *  @returns
 */
void Protocol_MessageRxEvent(FifoType* Fifo)
{
    Protocol_AssembleRxPDU(Fifo, &Protocol.RxPDU);
    FSM_SetState(&Protocol.State, PROTOCOL_STATE_RX);
    Protocol.RxMessageReady = TRUE;
    UART_RxDisable();
}

/*
 *  @brief Event signalling a recieved message has been handled.
 *  @param
 *  @returns
 */
void Protocol_RxMessageHandledEvent(void)
{
    FSM_SetState(&Protocol.State, PROTOCOL_STATE_TX);
    Protocol.RxMessageReady = FALSE;
    Protocol.TxMessageReady = TRUE;
    UART_TxEnable();
}

/*
 *  @brief Event signalling that the transmission of a message has been handled.
 *  @param
 *  @returns
 */
void Protocol_TxMessageHandledEvent(void)
{
    Protocol.TxMessageReady = FALSE;
    UART_RxEnable();
}

/*
 *  @brief Assemble a sequence of recieved bytes into a PDU.
 *  @param Fifo
 *      Buffer containing raw data.
 *  @param PDU
 *      Pointer to PDU structure where the assembled PDU should be stored.
 *  @returns
 */
void Protocol_AssembleRxPDU(FifoType* Fifo, PDUType* PDU)
{
    Fifo_ReadByte(Fifo, &PDU->FunctionCode);
    for (U8 i = 0; i < PROTOCOL_PAYLOAD_SIZE; i++)
    {
        Fifo_ReadByte(Fifo, &PDU->Data[i]);
    }
    Fifo_ReadByte(Fifo, &PDU->LRC);
}

/*
 *  @brief Assemble a PDU for transmission.
 *  @param PDU
 *      Pointer to PDU structure where the assembled PDU should be stored.
 *  @param FunctionCode
 *      The function code for the PDU (First byte).
 *  @param Data
 *      Array containing PDU payload.
 *  @returns
 */
void Protocol_AssembleTxPDU(PDUType* PDU, const U8 FunctionCode, const U8* Data)
{
    PDU->FunctionCode = FunctionCode;
    for (U8 i = 0; i < PROTOCOL_PAYLOAD_SIZE; i++)
    {
        PDU->Data[i] = Data[i];
    }
    PDU->LRC = LRC_Calc((U8*)PDU, PROTOCOL_FUNC_CODE_SIZE + PROTOCOL_PAYLOAD_SIZE);
}
