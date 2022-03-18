/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include <stdio.h>
#include <stdlib.h>
#include "GPIO_defs.h"
#include "timers.h"
#include "delay.h"
#include "lcd_4bit.h"
#include "LEDs.h"
#include "motor.h"

#define TESTING_MOTOR 0
#define TESTING_LED 1
#define FORWARD_SPEED (80)

volatile extern unsigned timeout;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	
	#if TESTING_LED
	//Init_GPIO();
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	ULTRASONIC_READING_PORT->PCR[ULTRASONIC_READING_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	ULTRASONIC_READING_PORT->PCR[ULTRASONIC_READING_SHIFT] |=  PORT_PCR_MUX(1) | PORT_PCR_IRQC(12); 
	ULTRASONIC_READING_PT->PDDR |= MASK(ULTRASONIC_READING_SHIFT); //output
	Delay(1000);
	ULTRASONIC_READING_PT->PSOR |= MASK(ULTRASONIC_READING_SHIFT); 
	Delay(10);
	ULTRASONIC_READING_PT->PCOR |= MASK(ULTRASONIC_READING_SHIFT); 
	
	#endif
	#if TESTING_MOTOR
	Init_PWM();
	Init_Drive_Motor();
	Init_Steering_Motor();
	
	while(1){
		Set_Drive_Forward(80);
		Set_Steering_Forward(80);
		Control_RGB_LEDs(0,1,0);
		Delay(500);
		Set_Drive_Stop();
		Set_Steering_Stop();
		Control_RGB_LEDs(1,0,0);

		Delay(500);
	}
	#endif
}

// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   
