/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include <stdio.h>
#include <stdlib.h>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "LEDs.h"
#include "timers.h"
#include "delay.h"
#include "motor.h"
#include "adc.h"

volatile uint8_t hour=0, minute=0, second=0;
volatile uint16_t millisecond=0;
volatile uint8_t currentAngle = 135;
volatile uint32_t turnDelay = 5;
double voltage;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
 

void turn(uint8_t angle){
	int angleDifference = currentAngle - angle;
	if (angleDifference > 0){
		int i = 0;
		for (i = angleDifference; i > 0; i--){
			currentAngle = currentAngle-1;
			Set_PWM_Servo(currentAngle );
			Delay(turnDelay);
			
		}
	}
	else{
		int i = 0;
		for(i = currentAngle; i<angle; i++){
			currentAngle = currentAngle+1;
			Set_PWM_Servo(currentAngle);
			Delay(turnDelay);
		}
	}
}
//void set_turn_delay( int speed){

	
//}
int main (void) {

	//Init_PIT(BUS_CLOCK_FREQUENCY/TICK_FREQUENCY);
  //Init_PWM();
  //Init_Drive_Motor();
	Init_RGB_LEDs();
	Init_ADC();

	Control_RGB_LEDs(1,1,1);
	//__enable_irq();
	//Start_PIT();
	
	while (1) {
		
		/*Delay(1000);
		Set_Forward(100);
		Delay(333);
	  Set_Stop();
		Delay(1000);
		Set_Reverse(100);
		Delay(333);
	  Set_Stop();*/
		//Delay(1000);
		voltage = Get_Position();
		if (voltage > 4.2 || voltage <1.8){
			Control_RGB_LEDs(1,0,0);
		}else {
			Control_RGB_LEDs(0,1,0);
		}
		Delay(1000);
		
		
	}
}


// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
