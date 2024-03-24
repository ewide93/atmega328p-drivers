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
// Local variables
//==================================================================================================
static BOOL MessageReady = FALSE;

//==================================================================================================
// Local function prototypes
//==================================================================================================
static U8 Protocol_CalcLRC(const PDUType* PDU);

//==================================================================================================
// External variable definitions
//==================================================================================================


//==================================================================================================
// Local function definitions
//==================================================================================================
static U8 Protocol_CalcLRC(const PDUType* PDU)
{
    return LRC_Calc((U8*)PDU, (U8)(PROTOCOL_PDU_SIZE - 1U));
}

//==================================================================================================
// External function definitions
//==================================================================================================
void Protocol_AssemblePDU(FifoType* Fifo, PDUType* PDU)
{
    Fifo_ReadByte(Fifo, &PDU->FunctionCode);
    for (U8 i = 0; i < PROTOCOL_PAYLOAD_SIZE; i++)
    {
        Fifo_ReadByte(Fifo, &PDU->Data[i]);
    }
    Fifo_ReadByte(Fifo, &PDU->LRC);
    MessageReady = TRUE;
}

void Protocol_MessageRecievedEvent(const PDUType* PDU)
{
    BOOL MatchingLRC = FALSE;

    if (!MessageReady) return;

    /* Prepare hardware for response transmission. */
    UART_RxDisable();
    UART_TxEnable();

    /* Calculate & compare LRC checksums. */
    MatchingLRC = (PDU->LRC == Protocol_CalcLRC(PDU));
    if (!MatchingLRC)
    {
        Protocol_SendNACK();
    }
    else
    {
        /* TODO: Find more elegant solution to handle different mesages. */
        switch (PDU->FunctionCode)
        {
            case FUNC_CODE_TEST:
            {

                U8 Payload = PDU->Data[0];
                if (Payload == 0x04)
                {
                    Digital_TogglePin(Pin4);
                    Protocol_SendACK();
                }
                else if (Payload == 0x05)
                {
                    Digital_TogglePin(Pin5);
                    Protocol_SendACK();
                }
                else
                {
                    /* Debug LED */
                    Digital_SetPin(Pin6);
                    Protocol_SendNACK();
                }
                break;
            }
            default:
            {
                Protocol_SendNACK();
                break;
            }
        }
    }

    /* Prepare hardware for message reception. */
    UART_TxDisable();
    UART_RxEnable();
    MessageReady = FALSE;
}

void Protocol_SendACK(void)
{
    UART_WriteByte(PROTOCOL_ACK);
}

void Protocol_SendNACK(void)
{
    UART_WriteByte(PROTOCOL_NACK);
}


