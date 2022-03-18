#ifndef IR_H
#define IR_H

#define MASK(x) (1UL << (x))

// I/O pin assignments
#define IR_LED_POS (1) // on port B bit 1


#define IR_PHOTOTRANSISTOR_CHANNEL (8) // on port B bit 0

#define T_DELAY_ON (30)
#define T_DELAY_OFF (30)

#define NUM_RANGE_STEPS (6)

#define NUM_SAMPLES_TO_AVG (10)

#define BRIGHTNESS_RANGE (600)

#define RED (0)
#define GREEN (1)
#define BLUE (2)
void Init_ADC(void);
void Control_IR_LED(unsigned int);
void Init_IR_LED(void);
unsigned Measure_IR(void);
void Display_Range(int);
int get_avg_diff(void);

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
