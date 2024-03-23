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
static PDUType RxPDU = { 0 };
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
void Protocol_AssemblePDU(FifoType* Data)
{
    Fifo_ReadByte(Data, &RxPDU.FunctionCode);
    for (U8 i = 0; i < PROTOCOL_PAYLOAD_SIZE; i++)
    {
        Fifo_ReadByte(Data, &RxPDU.Data[i]);
    }
    Fifo_ReadByte(Data, &RxPDU.LRC);
    MessageReady = TRUE;
}

void Protocol_MessageRecievedEvent(void)
{
    if (MessageReady)
    {
        (void)Protocol_CalcLRC(&RxPDU);
        switch (RxPDU.FunctionCode)
        {
            case FUNC_CODE_TEST:
            {
                if (RxPDU.Data[0] == 4U)
                {
                    Digital_TogglePin(Pin4);
                    Protocol_SendACK();
                }
                else if (RxPDU.Data[0] == 5U)
                {
                    Digital_TogglePin(Pin5);
                    Protocol_SendACK();
                }
                else
                {
                    Protocol_SendNACK();
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
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


