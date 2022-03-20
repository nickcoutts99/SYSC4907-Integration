#ifndef SWITCHES_H
#define SWITCHES_H
#include "gpio_defs.h"

// Switches on port D for interrupt support
#define SW_POS (6)
//#define SW_POS_STOP (5)

// Function prototypes
extern void Init_Switch(void);

// Shared variables
extern volatile unsigned MOTOR_STOP;

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
