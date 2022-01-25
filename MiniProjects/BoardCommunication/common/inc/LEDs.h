#ifndef LEDS_H
#define LEDS_H

#include <MKL25Z4.h>
#include "user_defs.h"

// Freedom KL25Z LEDs
#define RED_LED_POS (18)   // on port B
#define GREEN_LED_POS (19) // on port B
#define BLUE_LED_POS (1)   // on port D

// function prototypes
void Init_RGB_LEDs(void);
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);

#endif
