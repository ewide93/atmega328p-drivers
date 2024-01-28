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
#include "isr.h"
#include "fifo.h"
#include "register_macros.h"

//==================================================================================================
// Local preprocessor definitions
//==================================================================================================
#define UART_TX_BUFFER_SIZE 64
#define UART_RX_BUFFER_SIZE 64


//==================================================================================================
// Local variables
//==================================================================================================
static BOOL UART_Initialized = FALSE;
static U8 TxBuffer[UART_TX_BUFFER_SIZE] = { 0 };
static U8 NofTxBytes = 0;
static FifoType TxFifo;

//==================================================================================================
// Local function prototypes
//==================================================================================================
static void TxCompleteInterruptHandler(void);


//==================================================================================================
// External variable definitions
//==================================================================================================


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

static void TxCompleteInterruptHandler(void)
{
    U8 TxData = 0;
    if (NofTxBytes > 0)
    {
        Fifo_ReadByte(&TxFifo, &TxData);
        NofTxBytes--;
        UDR0 = TxData;
    }
}

//==================================================================================================
// External function definitions
//==================================================================================================
void UART_Init(const U8 DataBits, const U8 Parity, const U8 StopBits, const U8 BaudRate)
{
    if (UART_Initialized) return;
    Fifo_Init(&TxFifo, TxBuffer, UART_RX_BUFFER_SIZE);

    UART_SetDataBits(DataBits);
    UART_SetParity(Parity);
    UART_SetStopBits(StopBits);
    UART_SetBaudRate(BaudRate);

    // Enable transmitter hardware.
    UART_TxEnable();
    ISR_AddInterruptHandler(TxCompleteInterruptHandler, INTERRUPT_VECTOR_USART_TX);
    UART_Initialized = TRUE;
}

void UART_WriteByteBlocking(const char Data)
{
    // while (!(UCSR0A & (1 << UDRE0))) { };
    while (!ReadBit(UCSR0A, UDRE0)) { };
    UDR0 = Data;
}

void UART_Write(const char* Data, const U8 Size)
{
    U8 TxData = 0;
    for (U8 i = 0; i < Size; i++)
    {
        Fifo_WriteByte(&TxFifo, Data[i]);
        NofTxBytes++;
    }
    Fifo_ReadByte(&TxFifo, &TxData);
    NofTxBytes--;
    UDR0 = TxData;
}



