//==================================================================================================
//
// File name: spi.c
//
// Purpose:
//
//==================================================================================================

//==================================================================================================
// Include directives
//==================================================================================================
#include "spi.h"

//==================================================================================================
// Local preprocessor definitions
//==================================================================================================
#define SPI_DDR                 (DDRB)
#define SPI_MOSI_SHIFT          (3U)
#define SPI_MISO_SHIFT          (4U)
#define SPI_SCK_SHIFT           (5U)
#define SPI_SS_SHIFT            (2U)

#define SPCR_DORD_MASK          (0x01U)
#define SPCR_DORD_SHIFT         (5U)

#define SPCR_MODE_MASK          (0x03U)
#define SPCR_MODE_SHIFT         (2U)
#define SPCR_MODE_CLEAR_MASK    (~(SPCR_MODE_MASK << SPCR_MODE_SHIFT))

#define SPCR_SPR_MASK           (0x03U)
#define SPCR_SPR_SHIFT          (0U)
#define SPCR_SPR_CLEAR_MASK     (~(SPCR_SPR_MASK << SPCR_SPR_SHIFT))

#define SPSR_SPI2X_MASK         (0x04U)
#define SPSR_SPI2X_RIGHT_SHIFT  (2U)
#define SPSR_SPI2X_CLEAR_MASK   (~(SPSR_SPI2X_MASK) >> SPSR_SPI2X_RIGHT_SHIFT)

#define SPI_TX_BUFFER_LENGTH    (32U)
#define SPI_RX_BUFFER_LENGTH    (32U)
#define SPI_DUMMY_WRITE_VALUE   (0x00U)

//==================================================================================================
// Structures & enumerations
//==================================================================================================

//==================================================================================================
// Local variables
//==================================================================================================
static BOOL SPI_Initialized = FALSE;
static U8 TxBuffer[SPI_TX_BUFFER_LENGTH] = { 0 };
static U8 RxBuffer[SPI_RX_BUFFER_LENGTH] = { 0 };
static FifoType TxFifo;
static FifoType RxFifo;

//==================================================================================================
// Local function prototypes
//==================================================================================================
static inline void SPI_SetDataOrder(const U8 DataOrder);
static inline void SPI_SetMode(const U8 Mode);
static inline void SPI_SetFrequency(const U8 Frequency);

//==================================================================================================
// Local function definitions
//==================================================================================================
/**
 *  @brief Configure data order of SPI peripheral.
 *  @param DataOrder
 *      0 =MSB first, 1 = LSB first
 *  @returns
 */
static inline void SPI_SetDataOrder(const U8 DataOrder)
{
    ClearBit(SPCR, DORD);
    SPCR |= ((DataOrder & SPCR_DORD_MASK) << SPCR_DORD_SHIFT);
}

/**
 *  @brief Configure operating mode of SPI peripheral.
 *  @param Mode
 *      Operating mode, 0 - 3.
 *  @returns
 */
static inline void SPI_SetMode(const U8 Mode)
{
    SPCR &= SPCR_MODE_CLEAR_MASK;
    SPCR |= ((Mode & SPCR_MODE_MASK) << SPCR_MODE_SHIFT);
}

/**
 *  @brief Configure clock frequency of SPI peripheral.
 *  @param Frequency
 *      SPIClkFreqEnum (U8), peripheral clock frequency.
 *  @returns
 */
static inline void SPI_SetFrequency(const U8 Frequency)
{
    SPCR &= SPCR_SPR_CLEAR_MASK;
    SPCR |= ((Frequency & SPCR_SPR_MASK) << SPCR_SPR_SHIFT);
    SPSR &= SPSR_SPI2X_CLEAR_MASK;
    SPSR |= ((Frequency & SPSR_SPI2X_MASK) >> SPSR_SPI2X_RIGHT_SHIFT);
}


//==================================================================================================
// External function definitions
//==================================================================================================
/**
 *  @brief Initialize SPI peripheral for slave operation.
 *  @param
 *  @returns
 */
// void SPI_SlaveInit(const U8 Mode, const U8 DataOrder)
// {

// }

/**
 *  @brief Initialize SPI peripheral for master operation.
 *  @param
 *  @returns
 */
void SPI_MasterInit(const U8 Mode, const U8 DataOrder, const U8 Frequency)
{
    if (!SPI_Initialized)
    {
        /* Initialize private variables. */
        Fifo_Init(&TxFifo, TxBuffer, SPI_TX_BUFFER_LENGTH);
        Fifo_Init(&RxFifo, RxBuffer, SPI_RX_BUFFER_LENGTH);

        /* Configure peripheral frequency, mode & data shifting order */
        SPI_SetDataOrder(DataOrder);
        SPI_SetFrequency(Frequency);
        SPI_SetMode(Mode);

        /* Configure Master Mode */
        SetBit(SPCR, MSTR);

        /* Set MOSI, SCK & SS as outputs */
        SPI_DDR |= ((1 << SPI_MOSI_SHIFT) | (1 << SPI_SCK_SHIFT) | (1 << SPI_SS_SHIFT));

        /* Enable peripheral. */
        SPI_Enable();

        SPI_Initialized = TRUE;
    }
}

/**
 *  @brief Write one byte of data, ignoring data shifted
 *         back into SPI shift register.
 *  @param Data
 *      Data to be written.
 *  @returns
 */
void SPI_WriteByteBlocking(const U8 Data)
{
    SPDR = Data;
    while (!ReadBit(SPSR, SPIF)) { }
    (void)SPDR;
}

/**
 *  @brief Write one byte of dummy data in order to recieve a
 *         byte into the SPI shift register.
 *  @param
 *  @returns
 *      Recieved byte of data.
 */
U8 SPI_ReadByteBlocking(void)
{
    SPDR = SPI_DUMMY_WRITE_VALUE;
    while (!ReadBit(SPSR, SPIF)) { }
    return SPDR;
}

/**
 *  @brief Write one byte, recieve on byte...
 *  @param Data
 *      Data to be written.
 *  @returns
 *      Recieved byte of data.
 */
U8 SPI_ExchangeByteBlocking(const U8 Data)
{
    SPDR = Data;
    while (!ReadBit(SPSR, SPIF)) { }
    return SPDR;
}

