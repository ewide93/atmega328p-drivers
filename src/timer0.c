//==================================================================================================
//
// File name: timer0.c
//
// Purpose:
//
//==================================================================================================


//==================================================================================================
// Include directives
//==================================================================================================
#include "timer.h"

//==================================================================================================
// Local preprocessor definitions
//==================================================================================================
#define OC0A_OUTPUT_ENABLE     (DDRD |= (1 << 6))
#define OC0B_OUTPUT_ENABLE     (DDRD |= (1 << 5))

//==================================================================================================
// Local variables
//==================================================================================================


//==================================================================================================
// Local function prototypes
//==================================================================================================
static inline void Timer0_SetPrescaler(const U8 Prescaler);
static inline void Timer0_SetWaveformGenerationMode(const U8 Mode);
static inline void Timer0_SetCompareMatchOutputModeA(const U8 Mode);
static inline void Timer0_SetCompareMatchOutputModeB(const U8 Mode);
static inline void Timer0_SetCompareValueA(const U8 CompareValue);
static inline void Timer0_SetCompareValueB(const U8 CompareValue);

//==================================================================================================
// Local function definitions
//==================================================================================================
/*
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer0_SetPrescaler(const U8 Prescaler)
{
    TCCR0B |= Prescaler;
}

/*
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer0_SetWaveformGenerationMode(const U8 Mode)
{
    TCCR0A |= (Mode & 0x03);
    TCCR0B |= ((Mode & 0x04) << 1);
}

/*
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer0_SetCompareMatchOutputModeA(const U8 Mode)
{
    TCCR0A |= (Mode << 6);
}

/*
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer0_SetCompareMatchOutputModeB(const U8 Mode)
{
    TCCR0A |= (Mode << 4);
}

/*
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer0_SetCompareValueA(const U8 CompareValue)
{
    OCR0A = CompareValue;
}

/*
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer0_SetCompareValueB(const U8 CompareValue)
{
    OCR0B = CompareValue;
}


//==================================================================================================
// External function definitions
//==================================================================================================
void Timer0_Init(const Timer0CfgType* Cfg)
{
    Timer0_SetPrescaler(Cfg->Prescaler);
    Timer0_SetWaveformGenerationMode(Cfg->WaveGenMode);
    Timer0_SetCompareMatchOutputModeA(Cfg->OutModeA);
    Timer0_SetCompareMatchOutputModeB(Cfg->OutModeB);
    Timer0_SetCompareValueA(Cfg->OutCompValA);
    Timer0_SetCompareValueB(Cfg->OutCompValB);
    if (Cfg->OutModeA > 0) OC0A_OUTPUT_ENABLE;
    if (Cfg->OutModeB > 0) OC0B_OUTPUT_ENABLE;
}


