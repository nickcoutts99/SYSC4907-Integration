#ifndef MOTOR_H
#define MOTOR_H

#include <MKL25Z4.h>
#include "timers.h"

#define PIN_INA1_PORT	PORTA
#define PIN_INA1_PT	PTA
#define PIN_INA1_SHIFT  ( 2 )
#define PIN_INA1	(1 << PIN_INA1_SHIFT)

#define PIN_INB1_PORT	PORTA
#define PIN_INB1_PT	PTA
#define PIN_INB1_SHIFT  ( 1 )
#define PIN_INB1        ( 1 << PIN_INB1_SHIFT)


#define PIN_INA2_PORT	PORTC
#define PIN_INA2_PT	PTC
#define PIN_INA2_SHIFT  ( 8 )
#define PIN_INA2	(1 << PIN_INA2_SHIFT)

#define PIN_INB2_PORT	PORTC
#define PIN_INB2_PT	PTC
#define PIN_INB2_SHIFT  ( 9 )
#define PIN_INB2        ( 1 << PIN_INB2_SHIFT)

void Init_Drive_Motor(void);
void Set_Drive_Stop(void);
void Set_Drive_Forward(uint8_t duty_cycle);
void Set_Drive_Reverse(uint8_t duty_cycle);

void Init_Steering_Motor(void);
void Set_Steering_Stop(void);
void Set_Steering_Forward(uint8_t duty_cycle);
void Set_Steering_Reverse(uint8_t duty_cycle);


#endif
