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

#define TESTING_MOTOR 1
#define TESTING_LED 0
#define FORWARD_SPEED (80)

volatile extern unsigned timeout;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	
	#if TESTING_LED
	Init_GPIO();
	
	Init_RGB_LEDs();
	
	__enable_irq();
	
	//char transmittedMessage[5];
	Control_RGB_LEDs(0,0,1);
	while(1){ 
		if(check_ultrasonic_low()){
			Control_RGB_LEDs(0,1,0);
		}
		
	}
		
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
