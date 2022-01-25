/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include <stdio.h>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "LEDs.h"
#include "timers.h"
#include "delay.h"

volatile uint8_t hour=0, minute=0, second=0;
volatile uint16_t millisecond=0;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
 void set_Forward(uint8_t duty_cycle) {
	Set_PWM_Value_Ch0(duty_cycle);
	Set_PWM_Value_Ch1(0);
}

void set_Reverse(uint8_t duty_cycle) {
	Set_PWM_Value_Ch1(duty_cycle);
	Set_PWM_Value_Ch0(0);
}

void set_Stop(){
	Set_PWM_Value_Ch1(0);
	Set_PWM_Value_Ch0(0);
}
int main (void) {

	//Init_PIT(BUS_CLOCK_FREQUENCY/TICK_FREQUENCY);
  Init_PWM();



	//__enable_irq();
	//Start_PIT();
  
	while (1) {
		Delay(1000);
		Set_PWM_Servo(0);
		set_Forward(100);
		
		Delay(1000);
		Set_PWM_Servo(30);
		set_Stop();
		
		Delay(1000);
		Set_PWM_Servo(60);
		set_Forward(50);
		
		Delay(1000);
		set_Stop();
		Set_PWM_Servo(90);
		
		Delay(1000);
		Set_PWM_Servo(120);
		set_Reverse(100);
		
		Delay(1000);
		Set_PWM_Servo(0);
		set_Stop();
		
		Delay(1000);
		Set_PWM_Servo(30);
		set_Reverse(50);
		
		Delay(1000);
		Set_PWM_Servo(60);
		set_Stop();
	}
}


// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   