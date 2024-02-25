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
#define SPI_SCK_PIN                 Pin13;
#define SPI_MISO_PIN                Pin12;
#define SPI_MOSI_PIN                Pin11;
#define SPI_SS_PIN                  Pin10;

#define SPI_MODE_0                  (0x00U)       /* CPOL = 0, CPHA = 0 */
#define SPI_MODE_1                  (0x01U)       /* CPOL = 0, CPHA = 1 */
#define SPI_MODE_2                  (0x02U)       /* CPOL = 1, CPHA = 0 */
#define SPI_MODE_3                  (0x03U)       /* CPOL = 1, CPHA = 1 */

#define SPI_DATA_ORDER_MSB_FIRST    (0x00U)
#define SPI_DATA_ORDER_LSB_FIRST    (0x01U)

//==================================================================================================
// Structures and enumerations
//==================================================================================================


//==================================================================================================
// External variable declarations
//==================================================================================================


//==================================================================================================
// Function prototypes
//==================================================================================================
void SPI_SlaveInit();
void SPI_MasterInit();

//==================================================================================================
// Inline function definitions
//==================================================================================================
static inline void SPI_Enable(void)
{
    SetBit(SPCR, SPE);
}

#endif // _SPI_H_