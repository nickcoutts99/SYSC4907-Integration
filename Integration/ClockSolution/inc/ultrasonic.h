#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <MKL25Z4.h>
#include "LEDS.h"
#include "timers.h"

#define PIN_TRIG_PORT	PORTA
#define PIN_TRIG_PT	PTA
#define PIN_TRIG_SHIFT  ( 17 )
#define PIN_TRIG	(1 << PIN_TRIG_SHIFT)
#define PIN_TRIG_MUX	1

#define PIN_ECHO_PORT	PORTD
#define PIN_ECHO_PT	PTD
#define PIN_ECHO_SHIFT  ( 0 )
#define PIN_ECHO        ( 1 << PIN_ECHO_SHIFT)

void Init_Ultrasonic();
//void Generate_Trigger(void);
//void Measure_Reading(float* measurement);

#endif
