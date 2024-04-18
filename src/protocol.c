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
static inline void Protocol_MessageNotImplemented(void);
static void Protocol_TestMessageHandler(void);

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
static const VoidFunctionPtr MessageHandlers[256] =
{
    Protocol_MessageNotImplemented,             /* Function code: 0x00 */
    Protocol_MessageNotImplemented,             /* Function code: 0x01 */
    Protocol_MessageNotImplemented,             /* Function code: 0x02 */
    Protocol_MessageNotImplemented,             /* Function code: 0x03 */
    Protocol_MessageNotImplemented,             /* Function code: 0x04 */
    Protocol_MessageNotImplemented,             /* Function code: 0x05 */
    Protocol_MessageNotImplemented,             /* Function code: 0x06 */
    Protocol_MessageNotImplemented,             /* Function code: 0x07 */
    Protocol_MessageNotImplemented,             /* Function code: 0x08 */
    Protocol_MessageNotImplemented,             /* Function code: 0x09 */
    Protocol_MessageNotImplemented,             /* Function code: 0x0A */
    Protocol_MessageNotImplemented,             /* Function code: 0x0B */
    Protocol_MessageNotImplemented,             /* Function code: 0x0C */
    Protocol_MessageNotImplemented,             /* Function code: 0x0D */
    Protocol_MessageNotImplemented,             /* Function code: 0x0E */
    Protocol_MessageNotImplemented,             /* Function code: 0x0F */
    Protocol_MessageNotImplemented,             /* Function code: 0x10 */
    Protocol_MessageNotImplemented,             /* Function code: 0x11 */
    Protocol_MessageNotImplemented,             /* Function code: 0x12 */
    Protocol_MessageNotImplemented,             /* Function code: 0x13 */
    Protocol_MessageNotImplemented,             /* Function code: 0x14 */
    Protocol_MessageNotImplemented,             /* Function code: 0x15 */
    Protocol_MessageNotImplemented,             /* Function code: 0x16 */
    Protocol_MessageNotImplemented,             /* Function code: 0x17 */
    Protocol_MessageNotImplemented,             /* Function code: 0x18 */
    Protocol_MessageNotImplemented,             /* Function code: 0x19 */
    Protocol_MessageNotImplemented,             /* Function code: 0x1A */
    Protocol_MessageNotImplemented,             /* Function code: 0x1B */
    Protocol_MessageNotImplemented,             /* Function code: 0x1C */
    Protocol_MessageNotImplemented,             /* Function code: 0x1D */
    Protocol_MessageNotImplemented,             /* Function code: 0x1E */
    Protocol_MessageNotImplemented,             /* Function code: 0x1F */
    Protocol_TestMessageHandler,                /* Function code: 0x20 */
    Protocol_MessageNotImplemented,             /* Function code: 0x21 */
    Protocol_MessageNotImplemented,             /* Function code: 0x22 */
    Protocol_MessageNotImplemented,             /* Function code: 0x23 */
    Protocol_MessageNotImplemented,             /* Function code: 0x24 */
    Protocol_MessageNotImplemented,             /* Function code: 0x25 */
    Protocol_MessageNotImplemented,             /* Function code: 0x26 */
    Protocol_MessageNotImplemented,             /* Function code: 0x27 */
    Protocol_MessageNotImplemented,             /* Function code: 0x28 */
    Protocol_MessageNotImplemented,             /* Function code: 0x29 */
    Protocol_MessageNotImplemented,             /* Function code: 0x2A */
    Protocol_MessageNotImplemented,             /* Function code: 0x2B */
    Protocol_MessageNotImplemented,             /* Function code: 0x2C */
    Protocol_MessageNotImplemented,             /* Function code: 0x2D */
    Protocol_MessageNotImplemented,             /* Function code: 0x2E */
    Protocol_MessageNotImplemented,             /* Function code: 0x2F */
    Protocol_MessageNotImplemented,             /* Function code: 0x30 */
    Protocol_MessageNotImplemented,             /* Function code: 0x31 */
    Protocol_MessageNotImplemented,             /* Function code: 0x32 */
    Protocol_MessageNotImplemented,             /* Function code: 0x33 */
    Protocol_MessageNotImplemented,             /* Function code: 0x34 */
    Protocol_MessageNotImplemented,             /* Function code: 0x35 */
    Protocol_MessageNotImplemented,             /* Function code: 0x36 */
    Protocol_MessageNotImplemented,             /* Function code: 0x37 */
    Protocol_MessageNotImplemented,             /* Function code: 0x38 */
    Protocol_MessageNotImplemented,             /* Function code: 0x39 */
    Protocol_MessageNotImplemented,             /* Function code: 0x3A */
    Protocol_MessageNotImplemented,             /* Function code: 0x3B */
    Protocol_MessageNotImplemented,             /* Function code: 0x3C */
    Protocol_MessageNotImplemented,             /* Function code: 0x3D */
    Protocol_MessageNotImplemented,             /* Function code: 0x3E */
    Protocol_MessageNotImplemented,             /* Function code: 0x3F */
    Protocol_MessageNotImplemented,             /* Function code: 0x40 */
    Protocol_MessageNotImplemented,             /* Function code: 0x41 */
    Protocol_MessageNotImplemented,             /* Function code: 0x42 */
    Protocol_MessageNotImplemented,             /* Function code: 0x43 */
    Protocol_MessageNotImplemented,             /* Function code: 0x44 */
    Protocol_MessageNotImplemented,             /* Function code: 0x45 */
    Protocol_MessageNotImplemented,             /* Function code: 0x46 */
    Protocol_MessageNotImplemented,             /* Function code: 0x47 */
    Protocol_MessageNotImplemented,             /* Function code: 0x48 */
    Protocol_MessageNotImplemented,             /* Function code: 0x49 */
    Protocol_MessageNotImplemented,             /* Function code: 0x4A */
    Protocol_MessageNotImplemented,             /* Function code: 0x4B */
    Protocol_MessageNotImplemented,             /* Function code: 0x4C */
    Protocol_MessageNotImplemented,             /* Function code: 0x4D */
    Protocol_MessageNotImplemented,             /* Function code: 0x4E */
    Protocol_MessageNotImplemented,             /* Function code: 0x4F */
    Protocol_MessageNotImplemented,             /* Function code: 0x50 */
    Protocol_MessageNotImplemented,             /* Function code: 0x51 */
    Protocol_MessageNotImplemented,             /* Function code: 0x52 */
    Protocol_MessageNotImplemented,             /* Function code: 0x53 */
    Protocol_MessageNotImplemented,             /* Function code: 0x54 */
    Protocol_MessageNotImplemented,             /* Function code: 0x55 */
    Protocol_MessageNotImplemented,             /* Function code: 0x56 */
    Protocol_MessageNotImplemented,             /* Function code: 0x57 */
    Protocol_MessageNotImplemented,             /* Function code: 0x58 */
    Protocol_MessageNotImplemented,             /* Function code: 0x59 */
    Protocol_MessageNotImplemented,             /* Function code: 0x5A */
    Protocol_MessageNotImplemented,             /* Function code: 0x5B */
    Protocol_MessageNotImplemented,             /* Function code: 0x5C */
    Protocol_MessageNotImplemented,             /* Function code: 0x5D */
    Protocol_MessageNotImplemented,             /* Function code: 0x5E */
    Protocol_MessageNotImplemented,             /* Function code: 0x5F */
    Protocol_MessageNotImplemented,             /* Function code: 0x60 */
    Protocol_MessageNotImplemented,             /* Function code: 0x61 */
    Protocol_MessageNotImplemented,             /* Function code: 0x62 */
    Protocol_MessageNotImplemented,             /* Function code: 0x63 */
    Protocol_MessageNotImplemented,             /* Function code: 0x64 */
    Protocol_MessageNotImplemented,             /* Function code: 0x65 */
    Protocol_MessageNotImplemented,             /* Function code: 0x66 */
    Protocol_MessageNotImplemented,             /* Function code: 0x67 */
    Protocol_MessageNotImplemented,             /* Function code: 0x68 */
    Protocol_MessageNotImplemented,             /* Function code: 0x69 */
    Protocol_MessageNotImplemented,             /* Function code: 0x6A */
    Protocol_MessageNotImplemented,             /* Function code: 0x6B */
    Protocol_MessageNotImplemented,             /* Function code: 0x6C */
    Protocol_MessageNotImplemented,             /* Function code: 0x6D */
    Protocol_MessageNotImplemented,             /* Function code: 0x6E */
    Protocol_MessageNotImplemented,             /* Function code: 0x6F */
    Protocol_MessageNotImplemented,             /* Function code: 0x70 */
    Protocol_MessageNotImplemented,             /* Function code: 0x71 */
    Protocol_MessageNotImplemented,             /* Function code: 0x72 */
    Protocol_MessageNotImplemented,             /* Function code: 0x73 */
    Protocol_MessageNotImplemented,             /* Function code: 0x74 */
    Protocol_MessageNotImplemented,             /* Function code: 0x75 */
    Protocol_MessageNotImplemented,             /* Function code: 0x76 */
    Protocol_MessageNotImplemented,             /* Function code: 0x77 */
    Protocol_MessageNotImplemented,             /* Function code: 0x78 */
    Protocol_MessageNotImplemented,             /* Function code: 0x79 */
    Protocol_MessageNotImplemented,             /* Function code: 0x7A */
    Protocol_MessageNotImplemented,             /* Function code: 0x7B */
    Protocol_MessageNotImplemented,             /* Function code: 0x7C */
    Protocol_MessageNotImplemented,             /* Function code: 0x7D */
    Protocol_MessageNotImplemented,             /* Function code: 0x7E */
    Protocol_MessageNotImplemented,             /* Function code: 0x7F */
    Protocol_MessageNotImplemented,             /* Function code: 0x80 */
    Protocol_MessageNotImplemented,             /* Function code: 0x81 */
    Protocol_MessageNotImplemented,             /* Function code: 0x82 */
    Protocol_MessageNotImplemented,             /* Function code: 0x83 */
    Protocol_MessageNotImplemented,             /* Function code: 0x84 */
    Protocol_MessageNotImplemented,             /* Function code: 0x85 */
    Protocol_MessageNotImplemented,             /* Function code: 0x86 */
    Protocol_MessageNotImplemented,             /* Function code: 0x87 */
    Protocol_MessageNotImplemented,             /* Function code: 0x88 */
    Protocol_MessageNotImplemented,             /* Function code: 0x89 */
    Protocol_MessageNotImplemented,             /* Function code: 0x8A */
    Protocol_MessageNotImplemented,             /* Function code: 0x8B */
    Protocol_MessageNotImplemented,             /* Function code: 0x8C */
    Protocol_MessageNotImplemented,             /* Function code: 0x8D */
    Protocol_MessageNotImplemented,             /* Function code: 0x8E */
    Protocol_MessageNotImplemented,             /* Function code: 0x8F */
    Protocol_MessageNotImplemented,             /* Function code: 0x90 */
    Protocol_MessageNotImplemented,             /* Function code: 0x91 */
    Protocol_MessageNotImplemented,             /* Function code: 0x92 */
    Protocol_MessageNotImplemented,             /* Function code: 0x93 */
    Protocol_MessageNotImplemented,             /* Function code: 0x94 */
    Protocol_MessageNotImplemented,             /* Function code: 0x95 */
    Protocol_MessageNotImplemented,             /* Function code: 0x96 */
    Protocol_MessageNotImplemented,             /* Function code: 0x97 */
    Protocol_MessageNotImplemented,             /* Function code: 0x98 */
    Protocol_MessageNotImplemented,             /* Function code: 0x99 */
    Protocol_MessageNotImplemented,             /* Function code: 0x9A */
    Protocol_MessageNotImplemented,             /* Function code: 0x9B */
    Protocol_MessageNotImplemented,             /* Function code: 0x9C */
    Protocol_MessageNotImplemented,             /* Function code: 0x9D */
    Protocol_MessageNotImplemented,             /* Function code: 0x9E */
    Protocol_MessageNotImplemented,             /* Function code: 0x9F */
    Protocol_MessageNotImplemented,             /* Function code: 0xA0 */
    Protocol_MessageNotImplemented,             /* Function code: 0xA1 */
    Protocol_MessageNotImplemented,             /* Function code: 0xA2 */
    Protocol_MessageNotImplemented,             /* Function code: 0xA3 */
    Protocol_MessageNotImplemented,             /* Function code: 0xA4 */
    Protocol_MessageNotImplemented,             /* Function code: 0xA5 */
    Protocol_MessageNotImplemented,             /* Function code: 0xA6 */
    Protocol_MessageNotImplemented,             /* Function code: 0xA7 */
    Protocol_MessageNotImplemented,             /* Function code: 0xA8 */
    Protocol_MessageNotImplemented,             /* Function code: 0xA9 */
    Protocol_MessageNotImplemented,             /* Function code: 0xAA */
    Protocol_MessageNotImplemented,             /* Function code: 0xAB */
    Protocol_MessageNotImplemented,             /* Function code: 0xAC */
    Protocol_MessageNotImplemented,             /* Function code: 0xAD */
    Protocol_MessageNotImplemented,             /* Function code: 0xAE */
    Protocol_MessageNotImplemented,             /* Function code: 0xAF */
    Protocol_MessageNotImplemented,             /* Function code: 0xB0 */
    Protocol_MessageNotImplemented,             /* Function code: 0xB1 */
    Protocol_MessageNotImplemented,             /* Function code: 0xB2 */
    Protocol_MessageNotImplemented,             /* Function code: 0xB3 */
    Protocol_MessageNotImplemented,             /* Function code: 0xB4 */
    Protocol_MessageNotImplemented,             /* Function code: 0xB5 */
    Protocol_MessageNotImplemented,             /* Function code: 0xB6 */
    Protocol_MessageNotImplemented,             /* Function code: 0xB7 */
    Protocol_MessageNotImplemented,             /* Function code: 0xB8 */
    Protocol_MessageNotImplemented,             /* Function code: 0xB9 */
    Protocol_MessageNotImplemented,             /* Function code: 0xBA */
    Protocol_MessageNotImplemented,             /* Function code: 0xBB */
    Protocol_MessageNotImplemented,             /* Function code: 0xBC */
    Protocol_MessageNotImplemented,             /* Function code: 0xBD */
    Protocol_MessageNotImplemented,             /* Function code: 0xBE */
    Protocol_MessageNotImplemented,             /* Function code: 0xBF */
    Protocol_MessageNotImplemented,             /* Function code: 0xC0 */
    Protocol_MessageNotImplemented,             /* Function code: 0xC1 */
    Protocol_MessageNotImplemented,             /* Function code: 0xC2 */
    Protocol_MessageNotImplemented,             /* Function code: 0xC3 */
    Protocol_MessageNotImplemented,             /* Function code: 0xC4 */
    Protocol_MessageNotImplemented,             /* Function code: 0xC5 */
    Protocol_MessageNotImplemented,             /* Function code: 0xC6 */
    Protocol_MessageNotImplemented,             /* Function code: 0xC7 */
    Protocol_MessageNotImplemented,             /* Function code: 0xC8 */
    Protocol_MessageNotImplemented,             /* Function code: 0xC9 */
    Protocol_MessageNotImplemented,             /* Function code: 0xCA */
    Protocol_MessageNotImplemented,             /* Function code: 0xCB */
    Protocol_MessageNotImplemented,             /* Function code: 0xCC */
    Protocol_MessageNotImplemented,             /* Function code: 0xCD */
    Protocol_MessageNotImplemented,             /* Function code: 0xCE */
    Protocol_MessageNotImplemented,             /* Function code: 0xCF */
    Protocol_MessageNotImplemented,             /* Function code: 0xD0 */
    Protocol_MessageNotImplemented,             /* Function code: 0xD1 */
    Protocol_MessageNotImplemented,             /* Function code: 0xD2 */
    Protocol_MessageNotImplemented,             /* Function code: 0xD3 */
    Protocol_MessageNotImplemented,             /* Function code: 0xD4 */
    Protocol_MessageNotImplemented,             /* Function code: 0xD5 */
    Protocol_MessageNotImplemented,             /* Function code: 0xD6 */
    Protocol_MessageNotImplemented,             /* Function code: 0xD7 */
    Protocol_MessageNotImplemented,             /* Function code: 0xD8 */
    Protocol_MessageNotImplemented,             /* Function code: 0xD9 */
    Protocol_MessageNotImplemented,             /* Function code: 0xDA */
    Protocol_MessageNotImplemented,             /* Function code: 0xDB */
    Protocol_MessageNotImplemented,             /* Function code: 0xDC */
    Protocol_MessageNotImplemented,             /* Function code: 0xDD */
    Protocol_MessageNotImplemented,             /* Function code: 0xDE */
    Protocol_MessageNotImplemented,             /* Function code: 0xDF */
    Protocol_MessageNotImplemented,             /* Function code: 0xE0 */
    Protocol_MessageNotImplemented,             /* Function code: 0xE1 */
    Protocol_MessageNotImplemented,             /* Function code: 0xE2 */
    Protocol_MessageNotImplemented,             /* Function code: 0xE3 */
    Protocol_MessageNotImplemented,             /* Function code: 0xE4 */
    Protocol_MessageNotImplemented,             /* Function code: 0xE5 */
    Protocol_MessageNotImplemented,             /* Function code: 0xE6 */
    Protocol_MessageNotImplemented,             /* Function code: 0xE7 */
    Protocol_MessageNotImplemented,             /* Function code: 0xE8 */
    Protocol_MessageNotImplemented,             /* Function code: 0xE9 */
    Protocol_MessageNotImplemented,             /* Function code: 0xEA */
    Protocol_MessageNotImplemented,             /* Function code: 0xEB */
    Protocol_MessageNotImplemented,             /* Function code: 0xEC */
    Protocol_MessageNotImplemented,             /* Function code: 0xED */
    Protocol_MessageNotImplemented,             /* Function code: 0xEE */
    Protocol_MessageNotImplemented,             /* Function code: 0xEF */
    Protocol_MessageNotImplemented,             /* Function code: 0xF0 */
    Protocol_MessageNotImplemented,             /* Function code: 0xF1 */
    Protocol_MessageNotImplemented,             /* Function code: 0xF2 */
    Protocol_MessageNotImplemented,             /* Function code: 0xF3 */
    Protocol_MessageNotImplemented,             /* Function code: 0xF4 */
    Protocol_MessageNotImplemented,             /* Function code: 0xF5 */
    Protocol_MessageNotImplemented,             /* Function code: 0xF6 */
    Protocol_MessageNotImplemented,             /* Function code: 0xF7 */
    Protocol_MessageNotImplemented,             /* Function code: 0xF8 */
    Protocol_MessageNotImplemented,             /* Function code: 0xF9 */
    Protocol_MessageNotImplemented,             /* Function code: 0xFA */
    Protocol_MessageNotImplemented,             /* Function code: 0xFB */
    Protocol_MessageNotImplemented,             /* Function code: 0xFC */
    Protocol_MessageNotImplemented,             /* Function code: 0xFD */
    Protocol_MessageNotImplemented,             /* Function code: 0xFE */
    Protocol_MessageNotImplemented,             /* Function code: 0xFF */
};

//==================================================================================================
// Local function definitions
//==================================================================================================
/*
 *  @brief Function that assembles a non-acknowledge response to
 *         indicate that this function code is not implemented.
 *  @param
 *  @returns
 */
static inline void Protocol_MessageNotImplemented(void)
{
    Protocol_AssembleNackPDU();
}

static void Protocol_TestMessageHandler(void)
{
    U8 Payload = Protocol.RxPDU.Data[0];
    Digital_TogglePin(Payload);
    Protocol_AssembleAckPDU();
}


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
    MessageHandlers[Protocol.RxPDU.FunctionCode]();
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
    UART_RxDisable();
    Protocol_AssembleRxPDU(Fifo, &Protocol.RxPDU);
    Protocol.RxMessageReady = TRUE;
    FSM_SetState(&Protocol.State, PROTOCOL_STATE_RX);
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
