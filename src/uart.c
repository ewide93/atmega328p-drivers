//==================================================================================================
//
// File name: uart.c
//
// Purpose:
//
//==================================================================================================


//==================================================================================================
// Include directives
//==================================================================================================
#include "uart.h"

//==================================================================================================
// Local preprocessor definitions
//==================================================================================================
#define UART_TX_BUFFER_LENGTH 64
#define UART_RX_BUFFER_LENGTH 64

//==================================================================================================
// Local variables
//==================================================================================================
static BOOL UART_Initialized = FALSE;
static U8 TxBuffer[UART_TX_BUFFER_LENGTH] = { 0 };
static U8 RxBuffer[UART_RX_BUFFER_LENGTH] = { 0 };
static FifoType TxFifo;
static FifoType RxFifo;

//==================================================================================================
// Local function prototypes
//==================================================================================================
static void UART_TxCompleteInterruptHandler(void);
static void UART_RxCompleteInterruptHandler(void);

//==================================================================================================
// Local function definitions
//==================================================================================================
static inline void UART_SetDataBits(const U8 DataBits)
{
    UCSR0B |= (DataBits & 0x04);
    UCSR0C |= ((DataBits & 0x03) << 2);
}

static inline void UART_SetParity(const U8 Parity)
{
    UCSR0C |= ((Parity & 0x03) << 5);
}

static inline void UART_SetStopBits(const U8 StopBits)
{
    UCSR0C |= ((StopBits & 0x01) << 3);
}

static inline void UART_SetBaudRate(const U8 BaudRate)
{
    UBRR0 = BaudRate;
}

static inline BOOL UART_DataRegEmpty(void)
{
    return (ReadBit(UCSR0A, UDRE0) != 0);
}


static void UART_TxCompleteInterruptHandler(void)
{
    U8 TxData = 0;
    if (TxFifo.NofItems > 0)
    {
        Fifo_ReadByte(&TxFifo, &TxData);
        UDR0 = TxData;
    }
}

static void UART_RxCompleteInterruptHandler(void)
{
    const U8 RxData = UDR0;
    Fifo_WriteByte(&RxFifo, RxData);

    if (Fifo_GetNofItems(&RxFifo) >= PROTOCOL_PDU_SIZE)
    {
        Protocol_AssemblePDU(&RxFifo);
        Protocol_MessageRecievedEvent();
    }
}


//==================================================================================================
// External function definitions
//==================================================================================================
void UART_Init(const U8 DataBits, const U8 Parity, const U8 StopBits, const U8 BaudRate)
{
    if (UART_Initialized) return;

    /* Initialize Rx/Tx buffer objects. */
    Fifo_Init(&TxFifo, TxBuffer, UART_RX_BUFFER_LENGTH);
    Fifo_Init(&RxFifo, RxBuffer, UART_RX_BUFFER_LENGTH);

    /* Initialize UART hardware. */
    UART_SetDataBits(DataBits);
    UART_SetParity(Parity);
    UART_SetStopBits(StopBits);
    UART_SetBaudRate(BaudRate);

    /* Configure interrupt handlers for Rx/Tx interrupts. */
    ISR_AddInterruptHandler(UART_TxCompleteInterruptHandler, INTERRUPT_VECTOR_USART_TX);
    ISR_AddInterruptHandler(UART_RxCompleteInterruptHandler, INTERRUPT_VECTOR_USART_RX);

    /* Enable transmitter & reciever hardware. */
    UART_TxEnable();
    UART_RxEnable();

    UART_Initialized = TRUE;
}

void UART_WriteByteBlocking(const U8 Data)
{
    const U8 TxData = Data;
    while (!UART_DataRegEmpty()) { };
    UDR0 = TxData;
}

void UART_WriteByte(const U8 Data)
{
    if (!Fifo_Full(&TxFifo))
    {
        const U8 TxData = Data;

        if (Fifo_Empty(&TxFifo) && UART_DataRegEmpty())
        {
            UDR0 = TxData;
        }
        else
        {
            Fifo_WriteByte(&TxFifo, TxData);
        }
    }

}

void UART_WriteString(const char* Data, const U8 Length)
{
    U8 TxData = 0;

    if (Fifo_GetNofAvailable(&TxFifo) >= Length)
    {
        /* Check wether the data to be added is to be transmitted immediately. */
        BOOL TxFifoEmpty = Fifo_Empty(&TxFifo);

        for (U8 i = 0; i < Length; i++)
        {
            Fifo_WriteByte(&TxFifo, Data[i]);
        }

        /* Start sending data if no other data is in FIFO. */
        if (TxFifoEmpty)
        {
            Fifo_ReadByte(&TxFifo, &TxData);
            UDR0 = TxData;
        }
    }
    else return;
}



