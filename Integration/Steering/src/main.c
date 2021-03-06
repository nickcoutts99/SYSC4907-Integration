/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include <stdio.h>
#include <stdlib.h>
#include "GPIO_defs.h"
#include "timers.h"
#include "delay.h"
#include "uart.h"
#include "lcd_4bit.h"
#include "LEDs.h"
#include "motor.h"
#include "IR.h"

#define TESTING_MOTOR_ULTRASONIC 1 //NOTE CHECK GPIO_DEFS.c
#define TESTING_MOTOR 0
#define TESTING_LED 0
#define FORWARD_SPEED (15)

volatile unsigned irStopSignal = 0;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	
	#if TESTING_MOTOR_ULTRASONIC
	Init_Drive_Motor();
	Init_PWM();
	Init_GPIO();
	
	NVIC_SetPriority(PORTA_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);
	
	
	
	Init_RGB_LEDs();
	
	__enable_irq();
	
	Control_RGB_LEDs(0,0,1);
	while(!irStopSignal){ 
		if(check_ultrasonic_low()){
			Control_RGB_LEDs(0,1,0);
			Set_Forward(FORWARD_SPEED);
		}
	}
	#endif
		
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
	Init_RGB_LEDs();
	while(1){
		Set_Forward(80);
		Control_RGB_LEDs(0,1,0);
		Delay(500);
		Set_Stop();
		Control_RGB_LEDs(1,0,0);

		Delay(500);
	}
	#endif
}

// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   
