//==================================================================================================
//
// File name: timer.h
//
// Purpose:
//
//==================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_


//==================================================================================================
// Include directives
//==================================================================================================
#include "types.h"
#include "hw_cfg.h"


//==================================================================================================
// Preprocessor definitions
//==================================================================================================
#define Timer0 ((Timer0Type*)Timer0Handle->Timer)    /* NOTE: May not be necessary... */
#define Timer1 ((Timer1Type*)Timer1Handle->Timer)    /* NOTE: May not be necessary... */
#define Timer2 ((Timer2Type*)Timer2Handle->Timer)    /* NOTE: May not be necessary... */

                                           /* Timer 0 Clock Prescalers                             */
#define TIMER0_PRESCALER_1      (0x01U)    /* Timer frequency: 16 MHz      -> Period time: 62.5 ns */
#define TIMER0_PRESCALER_8      (0x02U)    /* Timer frequency: 2 MHz       -> Period time: 0.5 us  */
#define TIMER0_PRESCALER_64     (0x03U)    /* Timer frequency: 250 kHz     -> Period time: 4 us    */
#define TIMER0_PRESCALER_256    (0x04U)    /* Timer frequency: 62.5 kHz    -> Period time: 16 us   */
#define TIMER0_PRESCALER_1024   (0x05U)    /* Timer frequency: 15.625 kHz  -> Period time: 64 us   */

                                           /* Timer 0 Waveform Generation Modes                    */
#define TIMER0_WGM_NORMAL       (0x00U)    /* Normal Mode                                          */
#define TIMER0_WGM_PCPWM_CNTMAX (0x01U)    /* Phase Correct PWM Mode, TOP = 0xFF                   */
#define TIMER0_WGM_CTC          (0x02U)    /* Clear Timer on Compare Match Mode                    */
#define TIMER0_FPWM_CNTMAX      (0x03U)    /* Fast PWM Mode, TOP = 0xFF                            */
#define TIMER0_PCPWM            (0x05U)    /* Phase Correct PWM Mode, TOP = OCR0A                  */
#define TIMER0_FPWM             (0x07U)    /* Fast PWM Mode, TOP = OCR0A                           */

                                           /* Timer 0 Compare Match Output Mode                    */
#define TIMER0_COMA_TOGGLE      (0x01U)    /* Toggle OC0A (Pin 6) on compare match                 */
#define TIMER0_COMA_CLEAR       (0x02U)    /* Clear  OC0A (Pin 6) on compare match                 */
#define TIMER0_COMA_SET         (0x03U)    /* Set OC0A (Pin 6) on compare match                    */
#define TIMER0_COMB_TOGGLE      (0x01U)    /* Toggle OC0B (Pin 5) on compare match                 */
#define TIMER0_COMB_CLEAR       (0x02U)    /* Clear  OC0B (Pin 5) on compare match                 */
#define TIMER0_COMB_SET         (0x03U)    /* Set OC0B (Pin 5) on compare match                    */


//==================================================================================================
// Structure definitions
//==================================================================================================
typedef struct Timer0Type              /* Memory mapped I/O structure for Timer 0   */
{
    volatile uint8_t CtrlRegA;         /* TCCR0A – Timer/Counter Control Register A */
    volatile uint8_t CtrlRegB;         /* TCCR0B – Timer/Counter Control Register B */
    volatile uint8_t CntReg;           /* TCNT0  – Timer/Counter Register           */
    volatile uint8_t OutCompRegA;      /* OCR0A  – Output Compare Register A        */
    volatile uint8_t OutCompRegB;      /* OCR0B  – Output Compare Register B        */
} Timer0Type;

typedef struct Timer1Type              /* Memory mapped I/O structure for Timer 1    */
{
    volatile uint8_t CtrlRegA;         /* TCCR1A – Timer/Counter1 Control Register A */
    volatile uint8_t CtrlRegB;         /* TCCR1B – Timer/Counter1 Control Register B */
    volatile uint8_t CtrlRegC;         /* TCCR1C – Timer/Counter1 Control Register C */
    volatile const uint8_t PadByte;    /* Reserved                                   */
    volatile uint16_t CntReg;          /* TCNT1  – Timer/Counter1                    */
    volatile uint16_t InputCaptReg;    /* ICR1   – Input Capture Register 1          */
    volatile uint16_t OutCompRegA;     /* OCR1A  – Output Compare Register 1 A       */
    volatile uint16_t OutCompRegB;     /* OCR1B  – Output Compare Register 1 B       */
} Timer1Type;

typedef struct Timer2Type               /* Memory mapped I/O structure for TImer 2   */
{
    volatile uint8_t CtrlRegA;          /* TCCR2A – Timer/Counter Control Register A */
    volatile uint8_t CtrlRegB;          /* TCCR2B – Timer/Counter Control Register B */
    volatile uint8_t CntReg;            /* TCNT2  – Timer/Counter Register           */
    volatile uint8_t OutCompRegA;       /* OCR2A  – Output Compare Register A        */
    volatile uint8_t OutCompRegB;       /* OCR2B  – Output Compare Register B        */
    volatile const uint8_t PadByte;     /* Reserved                                  */
    volatile uint8_t AsyncStatusReg;    /* ASSR   – Asynchronous Status Register     */
} Timer2Type;

typedef struct TimerType                /* Generic timer structure                   */
{
    void* const Timer;                  /* Pointer to timer MMIO structure           */
    const uint8_t TimerID;              /* .TimerID = X -> .Timer = TimerXType*      */
    volatile uint8_t* IntMaskReg;       /* Interrupt mask register                   */
} TimerType;


//==================================================================================================
// Enumerations
//==================================================================================================
typedef enum TIMER_MODE
{
    TIMER_MODE_NORMAL,
    TIMER_MODE_CTC,
    TIMER_MODE_FAST_PWM,
    TIMER_MODE_PHASE_CORRECT_PWM,
    TIMER_MODE_PHASE_FREQ_CORRECT_PWM,
} TIMER_MODE;


//==================================================================================================
// External variable declarations
//==================================================================================================
extern TimerType* Timer0Handle;
extern TimerType* Timer1Handle;
extern TimerType* Timer2Handle;


//==================================================================================================
// Function prototypes
//==================================================================================================
void Timer_Init(TimerType* TimerHandle, enum TIMER_MODE Mode);


#endif // _TIMER_H_