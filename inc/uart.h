//==================================================================================================
//
// File name: uart.h
//
// Purpose:
//
//==================================================================================================
#ifndef _UART_H_
#define _UART_H_


//==================================================================================================
// Include directives
//==================================================================================================
#include "types.h"
#include "hw_cfg.h"
#include "isr.h"
#include "fifo.h"
#include "register_macros.h"
#include "protocol.h"

//==================================================================================================
// Preprocessor definitions
//==================================================================================================
#define UART_DATA_BITS_5        (0x00U)
#define UART_DATA_BITS_6        (0x01U)
#define UART_DATA_BITS_7        (0x02U)
#define UART_DATA_BITS_8        (0x03U)
#define UART_DATA_BITS_9        (0x07U)

#define UART_PARITY_NONE        (0x00U)
#define UART_PARITY_EVEN        (0x02U)
#define UART_PARITY_ODD         (0x03U)

#define UART_STOP_BITS_1        (0x00U)
#define UART_STOP_BITS_2        (0x01U)

#define UART_BAUD_RATE_9600      (103U)
#define UART_BAUD_RATE_14400     (68U)
#define UART_BAUD_RATE_19200     (51U)
#define UART_BAUD_RATE_28800     (34U)
#define UART_BAUD_RATE_38400     (25U)
#define UART_BAUD_RATE_57600     (16U)
#define UART_BAUD_RATE_76800     (12U)
#define UART_BAUD_RATE_115200    (8U)


//==================================================================================================
// Structures and enumerations
//==================================================================================================


//==================================================================================================
// External variable declarations
//==================================================================================================


//==================================================================================================
// Function prototypes
//==================================================================================================
void UART_Init(const U8 DataBits, const U8 Parity, const U8 StopBits, const U8 BaudRate);
void UART_WriteByteBlocking(const U8 Data);
void UART_WriteByte(const U8 Data);
void UART_WriteString(const char* Data, const U8 Length);


//==================================================================================================
// Inline function definitions
//==================================================================================================
static inline void UART_TxEnable(void)
{
    UCSR0B |= (1 << TXEN0);
}

static inline void UART_TxDisable(void)
{
    UCSR0B &= ~(1 << TXEN0);
}

static inline void UART_RxEnable(void)
{
    UCSR0B |= (1 << RXEN0);
}

static inline void UART_RxDisable(void)
{
    UCSR0B &= ~(1 << RXEN0);
}


#endif // _UART_H_