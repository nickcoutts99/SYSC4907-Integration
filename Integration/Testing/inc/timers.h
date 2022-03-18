#ifndef TIMERS_H
#define TIMERS_H
#include "MKL25Z4.h"

#define BUS_CLOCK_FREQUENCY (24E6)
#define TICK_FREQUENCY (1E3)

#define LCD_UPDATE_PERIOD (TICK_FREQUENCY/10)
#define LED_ON_TIME_TICKS (500)
#define LED_UPDATE_PERIOD (TICK_FREQUENCY/50)

#define PWM_MAX_COUNT (600)
#define TIMEOUT_COUNT ()
#define PIT_MAX_VALUE (0xFFFFFFFF) //(0xFFFFFFFF) //32 bit pit
#define TIMEOUT_VALUE (72E6)


void Init_PITs(unsigned period, unsigned timeout_period);
void Start_PITs(void);
void Stop_PITs(void);
void Init_PWM(void);
void Set_PWM_Value_Ch0(uint8_t duty_cycle);
void Set_PWM_Value_Ch1(uint8_t duty_cycle);

#endif
