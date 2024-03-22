//==================================================================================================
//
// File name: protocol.c
//
// Purpose:
//
//==================================================================================================


//==================================================================================================
// Include directives
//==================================================================================================
#include "protocol.h"

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
    RxPDU.LRC = Protocol_CalcLRC(&RxPDU);
    MessageReady = TRUE;
}

void Protocol_MessageRecievedEvent(void)
{
    if (MessageReady)
    {
        switch (RxPDU.FunctionCode)
        {
            case FUNC_CODE_TEST:
            {
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


