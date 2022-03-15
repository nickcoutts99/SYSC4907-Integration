#include <MKL25Z4.h>
#ifndef GPIO_DEFS_H
#define GPIO_DEFS_H

// basic light switch 
#define LED1_POS (1)	// on port A
#define LED2_POS (2)	// on port A
#define SW1_POS (5)		// on port A

//ultrasonic reading
#define ULTRASONIC_READING_PORT (PORTA)
#define ULTRASONIC_READING_PT (PTA)
#define ULTRASONIC_READING_SHIFT (16)

#define MASK(x) (1UL << (x))
void Init_GPIO();
int check_ultrasonic_low();
#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
