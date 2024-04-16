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

//==================================================================================================
// Local variables
//==================================================================================================
#define TIMER0_DDR          (DDRD)
#define TIMER0_COMA_PIN     (6U)
#define TIMER0_COMB_PIN     (5U)

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
/*
 *  @brief
 *  @param
 *  @returns
 */
void Timer0_Init(const Timer0CfgType* Cfg)
{
    Timer0_SetPrescaler(Cfg->Prescaler);
    Timer0_SetWaveformGenerationMode(Cfg->WaveGenMode);
    Timer0_SetCompareMatchOutputModeA(Cfg->OutModeA);
    Timer0_SetCompareMatchOutputModeB(Cfg->OutModeB);
    Timer0_SetCompareValueA(Cfg->OutCompValA);
    Timer0_SetCompareValueB(Cfg->OutCompValB);
    if (Cfg->OutModeA > 0) Timer0_OutputAEnable();
    if (Cfg->OutModeB > 0) Timer0_OutputBEnable();
}

/*
 *  @brief
 *  @param
 *  @returns
 */
void Timer0_OutputAEnable(void)
{
    TIMER0_DDR |= (1 << TIMER0_COMA_PIN);
}

/*
 *  @brief
 *  @param
 *  @returns
 */
void Timer0_OutputBEnable(void)
{
    TIMER0_DDR |= (1 << TIMER0_COMB_PIN);
}
