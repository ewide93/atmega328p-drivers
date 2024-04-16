//==================================================================================================
//
// File name: timer.h
//
// Purpose: Common header to all timer peripherals.
//
//==================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//==================================================================================================
// Include directives
//==================================================================================================
#include "types.h"
#include "hw_cfg.h"
#include "isr.h"

//==================================================================================================
// Preprocessor definitions
//==================================================================================================
                                           /* Timer 0 Clock Prescalers                              */
#define TIMER0_PRESCALER_1      (0x01U)    /* Timer frequency: 16 MHz      -> Period time: 62.5 ns  */
#define TIMER0_PRESCALER_8      (0x02U)    /* Timer frequency: 2 MHz       -> Period time: 0.5 us   */
#define TIMER0_PRESCALER_64     (0x03U)    /* Timer frequency: 250 kHz     -> Period time: 4 us     */
#define TIMER0_PRESCALER_256    (0x04U)    /* Timer frequency: 62.5 kHz    -> Period time: 16 us    */
#define TIMER0_PRESCALER_1024   (0x05U)    /* Timer frequency: 15.625 kHz  -> Period time: 64 us    */

                                           /* Timer 0 Waveform Generation Modes                     */
#define TIMER0_WGM_NORMAL       (0x00U)    /* Normal Mode                                           */
#define TIMER0_WGM_PCPWM_CNTMAX (0x01U)    /* Phase Correct PWM Mode, TOP = 0xFF                    */
#define TIMER0_WGM_CTC          (0x02U)    /* Clear Timer on Compare Match Mode                     */
#define TIMER0_WGM_FPWM_CNTMAX  (0x03U)    /* Fast PWM Mode, TOP = 0xFF                             */
#define TIMER0_WGM_PCPWM        (0x05U)    /* Phase Correct PWM Mode, TOP = OCR0A                   */
#define TIMER0_WGM_FPWM         (0x07U)    /* Fast PWM Mode, TOP = OCR0A                            */

                                           /* Timer 0 Compare Match Output Mode                     */
#define TIMER0_COMA_NONE        (0x00U)    /* OC0A (Pin 6) disconnected                             */
#define TIMER0_COMA_TOGGLE      (0x01U)    /* Toggle OC0A (Pin 6) on compare match                  */
#define TIMER0_COMA_CLEAR       (0x02U)    /* Clear  OC0A (Pin 6) on compare match                  */
#define TIMER0_COMA_SET         (0x03U)    /* Set OC0A (Pin 6) on compare match                     */
#define TIMER0_COMB_NONE        (0x00U)    /* OC0B (Pin 5) disconnected                             */
#define TIMER0_COMB_TOGGLE      (0x01U)    /* Toggle OC0B (Pin 5) on compare match                  */
#define TIMER0_COMB_CLEAR       (0x02U)    /* Clear  OC0B (Pin 5) on compare match                  */
#define TIMER0_COMB_SET         (0x03U)    /* Set OC0B (Pin 5) on compare match                     */

                                           /* Timer 1 Clock Prescalers                              */
#define TIMER1_PRESCALER_1      (0x01U)    /* Timer frequency: 16 MHz      -> Period time: 62.5 ns  */
#define TIMER1_PRESCALER_8      (0x02U)    /* Timer frequency: 2 MHz       -> Period time: 0.5 us   */
#define TIMER1_PRESCALER_64     (0x03U)    /* Timer frequency: 250 kHz     -> Period time: 4 us     */
#define TIMER1_PRESCALER_256    (0x04U)    /* Timer frequency: 62.5 kHz    -> Period time: 16 us    */
#define TIMER1_PRESCALER_1024   (0x05U)    /* Timer frequency: 15.625 kHz  -> Period time: 64 us    */

                                           /* Timer 1 Waveform Generation Modes                     */
#define TIMER1_WGM_NORMAL       (0x00U)    /* Normal Mode                                           */
#define TIMER1_WGM_PCPWM_8_BIT  (0x01U)    /* Phase Correct PWM Mode, 8-bit operation, TOP = 0xFF   */
#define TIMER1_WGM_PCPWM_9_BIT  (0x02U)    /* Phase Correct PWM Mode, 9-bit operation, TOP = 0x1FF  */
#define TIMER1_WGM_PCPWM_10_BIT (0x03U)    /* Phase Correct PWM Mode, 10-bit operation, TOP = 0x3FF */
#define TIMER1_WGM_CTC          (0x04U)    /* Clear Timer on Compare Match Mode                     */
#define TIMER1_WGM_FPWM_8_BIT   (0x05U)    /* Fast PWM Mode, 8-bit operation, TOP = 0xFF            */
#define TIMER1_WGM_FPWM_9_BIT   (0x06U)    /* Fast PWM Mode, 9-bit operation, TOP = 0x1FF           */
#define TIMER1_WGM_FPWM_10_BIT  (0x07U)    /* Fast PWM Mode, 10-bit operation, TOP = 0x3FF          */
#define TIMER1_WGM_PFCPWM       (0x09U)    /* Phase & Frequency Correct PWM Mode, TOP = OCR1A       */
#define TIMER1_WGM_PCPWM        (0x0BU)    /* Phase Correct PWM Mode, TOP = OCR1A                   */
#define TIMER1_WGM_FPWM         (0x0FU)    /* Fast PWM Mode, TOP = OCR1A                            */

                                           /* Timer 1 Compare Match Output Mode                     */
#define TIMER1_COMA_NONE        (0x00U)    /* OC1A (Pin 9) disconnected                             */
#define TIMER1_COMA_TOGGLE      (0x01U)    /* Toggle OC1A (Pin 9) on compare match                  */
#define TIMER1_COMA_CLEAR       (0x02U)    /* Clear  OC1A (Pin 9) on compare match                  */
#define TIMER1_COMA_SET         (0x03U)    /* Set OC1A (Pin 9) on compare match                     */
#define TIMER1_COMB_NONE        (0x00U)    /* OC1B (Pin 10) disconnected                            */
#define TIMER1_COMB_TOGGLE      (0x01U)    /* Toggle OC1B (Pin 10) on compare match                 */
#define TIMER1_COMB_CLEAR       (0x02U)    /* Clear  OC1B (Pin 10) on compare match                 */
#define TIMER1_COMB_SET         (0x03U)    /* Set OC1B (Pin 10) on compare match                    */

/* Default config generating timer interrupt with a period time of 1ms. */
#define TIMER0_DEFAULT_CFG ( &(Timer0CfgType) \
    { \
        .OutCompValA = 250, \
        .OutCompValB = 0, \
        .Prescaler = TIMER0_PRESCALER_64, \
        .OutModeA = TIMER0_COMA_NONE, \
        .OutModeB = TIMER0_COMB_NONE, \
        .WaveGenMode = TIMER0_WGM_CTC \
    } )

/* Default config generating timer interrupt with a period time of 1ms. */
#define TIMER1_DEFAULT_CFG ( &(Timer1CfgType) \
    { \
        .OutCompValA = 250, \
        .OutCompValB = 0, \
        .Prescaler = TIMER1_PRESCALER_64, \
        .OutModeA = TIMER1_COMA_NONE, \
        .OutModeB = TIMER1_COMB_NONE, \
        .WaveGenMode = TIMER1_WGM_CTC \
    } )

//==================================================================================================
// Structures & enumerations
//==================================================================================================
typedef enum
{
    TIMER0 = 0x00,
    TIMER1 = 0x01,
    TIMER2 = 0x02
} TimerEnum;

typedef enum
{
    TIM_INT_OVF = 0x00,
    TIM_INT_COMPA = 0x01,
    TIM_INT_COMPB = 0x02,
    TIM_INT_CAPT  = 0x05
} TimerInterruptEnum;

typedef struct
{
    U8 Prescaler;
    U8 WaveGenMode;
    U8 OutModeA;
    U8 OutCompValA;
    U8 OutModeB;
    U8 OutCompValB;
} Timer0CfgType;

typedef struct
{
    U8 Prescaler;
    U8 WaveGenMode;
    U8 OutModeA;
    U16 OutCompValA;
    U8 OutModeB;
    U16 OutCompValB;
} Timer1CfgType;

typedef struct
{
    U8 Placeholder;
} Timer2CfgType;

//==================================================================================================
// Function prototypes
//==================================================================================================
void Timer_InterruptEnable(const TimerEnum Timer, const TimerInterruptEnum Interrupt);
void Timer_InterruptDisable(const TimerEnum Timer, const TimerInterruptEnum Interrupt);
void Timer0_Init(const Timer0CfgType* Cfg);
void Timer0_OutputAEnable(void);
void Timer0_OutputBEnable(void);
void Timer1_Init(const Timer1CfgType* Cfg);
void Timer1_OutputAEnable(void);
void Timer1_OutputBEnable(void);
/* TODO: Timer1 Input Capture functionality? */

#endif // _TIMER_H_