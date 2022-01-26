#ifndef IR_H
#define IR_H

#include <MKL25Z4.h>
#include "user_defs.h"
#include "LEDs.h"

extern int Threshold[NUM_RANGE_STEPS];
extern const int Colors[NUM_RANGE_STEPS][3];

void Init_ADC(void);
void Control_IR_LED(unsigned int led_on);
void Init_IR_LED(void);
unsigned Measure_IR(void);
void Display_Range(int b);
void Delay_us(volatile unsigned int time_del);

#endif
