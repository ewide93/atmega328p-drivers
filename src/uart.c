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
void UART_Init(void)
{
    if (UART_Initialized) return;
    // NOTE: Simple 8N1 configuration for test purposes.
    Fifo_Init(&TxFifo, TxBuffer, UART_RX_BUFFER_SIZE);

    // 8-bit payload, 9600 kbps baud rate.
    UCSR0C |= (0x03 << 1);
    UBRR0 = 103;

    // Enable transmitter hardware.
    UART_TxEnable();
    ISR_AddInterruptHandler(TxCompleteInterruptHandler, INTERRUPT_VECTOR_USART_TX);
    UART_Initialized = TRUE;
}

void UART_WriteByteBlocking(const char Data)
{
    while (!(UCSR0A & (1 << UDRE0))) { };
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



