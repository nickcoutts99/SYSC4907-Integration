#ifndef TIMERS_H
#define TIMERS_H
#include "MKL25Z4.h"
#include "ultrasonic_array.h"

#define BUS_CLOCK_FREQUENCY (24E6)
#define TICK_FREQUENCY (1E3)

#define LCD_UPDATE_PERIOD (TICK_FREQUENCY/10)
#define LED_ON_TIME_TICKS (500)
#define LED_UPDATE_PERIOD (TICK_FREQUENCY/50)

#define PLL_CLOCK_FREQUENCY (50000000)

#define PWM_MAX_COUNT (0xFFFF)
	
void Init_PIT(unsigned period);
void Stop_PIT(void);

void Init_TPM(ULTRASONIC_SENSOR* ultrasonic_cfg);
void Init_TPM_IRQ(void);
float TPM_PLL_Clock_Speed(int prescaleMode);

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
