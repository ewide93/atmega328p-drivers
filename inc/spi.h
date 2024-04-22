//==================================================================================================
//
// File name: spi.h
//
// Purpose:
//
//==================================================================================================
#ifndef _SPI_H_
#define _SPI_H_

//==================================================================================================
// Include directives
//==================================================================================================
#include "types.h"
#include "hw_cfg.h"
#include "digital.h"
#include "register_macros.h"

//==================================================================================================
// Preprocessor definitions
//==================================================================================================

//==================================================================================================
// Structures and enumerations
//==================================================================================================
/**
 *  @brief Enumeration of the supported SPI operating modes.
 */
typedef enum
{
    SPI_MODE_0 = 0x00U,     /* CPOL = 0, CPHA = 0 */
    SPI_MODE_1 = 0x01U,     /* CPOL = 0, CPHA = 1 */
    SPI_MODE_2 = 0x02U,     /* CPOL = 1, CPHA = 0 */
    SPI_MODE_3 = 0x03U      /* CPOL = 1, CPHA = 1 */
} SPIModeEnum;

/**
 * @brief Enumeration of the different SPI data orders.
*/
typedef enum
{
    DATA_ORDER_MSB_FIRST = 0x00U,      /* Most Significant Bit first  */
    DATA_ORDER_LSB_FIRST = 0x01U       /* Least Significant Bit first */
} SPIDataOrderEnum;

/**
 * @brief Enumeration of the available clock frequencies of the SPI peripheral.
*/
typedef enum
{
    SPI_CLK_FREQ_4_MHz = 0x00U,
    SPI_CLK_FREQ_1_MHz = 0x01U,
    SPI_CLK_FREQ_250_kHz = 0x02U,
    SPI_CLK_FREQ_125_kHz = 0x03U,
    SPI_CLK_FREQ_8_MHz = 0x04U,
    SPI_CLK_FREQ_2_MHz = 0x05U,
    SPI_CLK_FREQ_500_kHz = 0x06U
} SPIClkFreqEnum;

//==================================================================================================
// External variable declarations
//==================================================================================================


//==================================================================================================
// Function prototypes
//==================================================================================================
void SPI_MasterInit(const U8 Mode, const U8 DataOrder, const U8 Frequency);
// TODO: Implement SlaveInit function...
// void SPI_SlaveInit(const U8 Mode, const U8 DataOrder);

//==================================================================================================
// Inline function definitions
//==================================================================================================
/**
 *  @brief Enable SPI peripheral hardware.
 *  @param
 *  @returns
 */
static inline void SPI_Enable(void)
{
    SetBit(SPCR, SPE);
}

/**
 *  @brief Disable SPI peripheral hardware.
 *  @param
 *  @returns
 */
static inline void SPI_Disable(void)
{
    ClearBit(SPCR, SPE);
}

/**
 *  @brief Enable SPI transmission complete interrupt.
 *  @param
 *  @returns
 */
static inline void SPI_InterruptEnable(void)
{
    SetBit(SPCR, SPIE);
}

/**
 *  @brief Disble SPI transmission complete interrupt.
 *  @param
 *  @returns
 */
static inline void SPI_InterruptDisable(void)
{
    ClearBit(SPCR, SPIE);
}

#endif // _SPI_H_