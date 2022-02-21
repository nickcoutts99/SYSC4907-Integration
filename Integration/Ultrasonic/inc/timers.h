#ifndef TIMERS_H
#define TIMERS_H
#include "MKL25Z4.h"

#define BUS_CLOCK_FREQUENCY (24E6)
#define TICK_FREQUENCY (1E3)

#define LCD_UPDATE_PERIOD (TICK_FREQUENCY/10)
#define LED_ON_TIME_TICKS (500)
#define LED_UPDATE_PERIOD (TICK_FREQUENCY/50)

#define PLL_CLOCK_FREQUENCY (50000000)

#define PWM_MAX_COUNT (0xFFFF)

void Init_PITs(unsigned period1, unsigned period2);
void Start_PIT1(void);
void Stop_PIT1(void);
void Start_PIT2(void);
void Stop_PIT2(void);

void Init_TPM(void);
void Set_PWM_Value(uint8_t duty_cycle);

extern volatile unsigned PIT_interrupt_counter;
extern volatile unsigned LCD_update_requested;
float TPM_PLL_Clock_Speed(int prescaleMode);

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
