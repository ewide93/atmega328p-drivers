//==================================================================================================
//
// File name: timer1.c
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
#define TIMER1_DDR                  (DDRB)
#define TIMER1_COMA_PIN             (1U)
#define TIMER1_COMB_PIN             (2U)

#define TCCR1B_CS_MASK              (0x07U)
#define TCCR1B_CS_SHIFT             (0U)
#define TCCR1B_CS_CLEAR_MASK        (~(TCCR1B_CS_MASK << TCCR1B_CS_SHIFT))

#define TCCR1A_WGM_MASK             (0x03U)
#define TCCR1A_WGM_SHIFT            (0U)
#define TCCR1A_WGM_CLEAR_MASK       (~(TCCR1A_WGM_MASK << TCCR1A_WGM_SHIFT))

#define TCCR1B_WGM_MASK             (0x0CU)
#define TCCR1B_WGM_SHIFT            (1U)
#define TCCR1B_WGM_CLEAR_MASK       (~(TCCR1B_WGM_MASK << TCCR1B_WGM_SHIFT))

#define TCCR1A_COMA_MASK            (0x03U)
#define TCCR1A_COMA_SHIFT           (6U)
#define TCCR1A_COMA_CLEAR_MASK      (~(TCCR1A_COMA_MASK << TCCR1A_COMA_SHIFT))

#define TCCR1A_COMB_MASK            (0x03U)
#define TCCR1A_COMB_SHIFT           (4U)
#define TCCR1A_COMB_CLEAR_MASK      (~(TCCR1A_COMA_MASK << TCCR1A_COMA_SHIFT))

//==================================================================================================
// Local variables
//==================================================================================================

//==================================================================================================
// Local function prototypes
//==================================================================================================
static inline void Timer1_SetPrescaler(const U8 Prescaler);
static inline void Timer1_SetWaveformGenerationMode(const U8 Mode);
static inline void Timer1_SetCompareMatchOutputModeA(const U8 Mode);
static inline void Timer1_SetCompareMatchOutputModeB(const U8 Mode);
static inline void Timer1_SetCompareValueA(const U16 CompareValue);
static inline void Timer1_SetCompareValueB(const U16 CompareValue);

//==================================================================================================
// Local function definitions
//==================================================================================================
/**
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer1_SetPrescaler(const U8 Prescaler)
{
    TCCR1B &= TCCR1B_CS_CLEAR_MASK;
    TCCR1B |= ((Prescaler & TCCR1B_CS_MASK) << TCCR1B_CS_SHIFT);
}

/**
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer1_SetWaveformGenerationMode(const U8 Mode)
{
    TCCR1A &= TCCR1A_WGM_CLEAR_MASK;
    TCCR1A |= ((Mode & TCCR1A_WGM_MASK) << TCCR1A_WGM_SHIFT);
    TCCR1B &= TCCR1B_WGM_CLEAR_MASK;
    TCCR1B |= ((Mode & TCCR1B_WGM_MASK) << TCCR1B_WGM_SHIFT);
}

/**
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer1_SetCompareMatchOutputModeA(const U8 Mode)
{
    TCCR1A &= TCCR1A_COMA_CLEAR_MASK;
    TCCR1A |= ((Mode & TCCR1A_COMA_MASK) << TCCR1A_COMA_SHIFT);
}

/**
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer1_SetCompareMatchOutputModeB(const U8 Mode)
{
    TCCR1A &= TCCR1A_COMB_CLEAR_MASK;
    TCCR1A |= ((Mode & TCCR1A_COMB_MASK) << TCCR1A_COMB_SHIFT);
}

/**
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer1_SetCompareValueA(const U16 CompareValue)
{
    OCR1A = CompareValue;
}

/**
 *  @brief
 *  @param
 *  @returns
 */
static inline void Timer1_SetCompareValueB(const U16 CompareValue)
{
    OCR1B = CompareValue;
}


//==================================================================================================
// External function definitions
//==================================================================================================
/**
 *  @brief
 *  @param
 *  @returns
 */
void Timer1_Init(const Timer1CfgType* Cfg)
{
    Timer1_SetPrescaler(Cfg->Prescaler);
    Timer1_SetWaveformGenerationMode(Cfg->WaveGenMode);
    Timer1_SetCompareMatchOutputModeA(Cfg->OutModeA);
    Timer1_SetCompareMatchOutputModeB(Cfg->OutModeB);
    Timer1_SetCompareValueA(Cfg->OutCompValA);
    Timer1_SetCompareValueB(Cfg->OutCompValB);
    if (Cfg->OutModeA > 0) Timer1_OutputAEnable();
    if (Cfg->OutModeB > 0) Timer1_OutputBEnable();
}

/**
 *  @brief
 *  @param
 *  @returns
 */
void Timer1_OutputAEnable(void)
{
    TIMER1_DDR |= (1 << TIMER1_COMA_PIN);
}

/**
 *  @brief
 *  @param
 *  @returns
 */
void Timer1_OutputBEnable(void)
{
    TIMER1_DDR |= (1 << TIMER1_COMB_PIN);
}
