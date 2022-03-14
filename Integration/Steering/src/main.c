/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include <stdio.h>
#include <stdlib.h>
#include "timers.h"
#include "delay.h"
#include "uart.h"
#include "lcd_4bit.h"
#include "LEDs.h"
#include "motor.h"
#include "IR.h"

#define TESTING_MOTOR 0
#define TESTING_LED 1

volatile extern unsigned timeout;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	
	#if TESTING_MOTOR
	Init_LCD();
  Init_PWM();
	//Init_Drive_Motor();
	Init_RGB_LEDs();

	__enable_irq();
	//Start_PIT();
	UART1_INIT(UART_BAUDRATE_300, 128);
	char transmittedMessage[5];
	char displayMessage[17];
  int objectClose = 0;
	int distance = 100;
	//Set_Forward(50);
	Control_RGB_LEDs(0,1,0);
	while (!objectClose) {
			UART1_READ(transmittedMessage);
			distance = atoi(transmittedMessage);
		 Print_LCD(transmittedMessage);
			
			if(distance < 10){
				objectClose = 1;
			}
			Delay(100);
	}
	Control_RGB_LEDs(1,0,0);
	Set_Stop();
	
	/*
	
	Set_Stop();
	
	Set_Forward(80);
	Delay(500);
	Set_Stop();
	Delay(500);
	Set_Reverse(50);
	Delay(500);
	Set_Stop();*/
	#endif
		
	#if TESTING_LED
	
	PORTA->PCR[16] &= ~PORT_PCR_MUX_MASK;          
	PORTA->PCR[16] |=  PORT_PCR_MUX(1) | PORT_PCR_IRQC(12); 
	PTA->PDDR &= ~MASK(16); //input
	
	Init_PWM();
	
	Init_RGB_LEDs();
	NVIC_SetPriority(PORTA_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);
	__enable_irq();
	
//	UART1_INIT(UART_BAUDRATE_9600, 128);
	char transmittedMessage[5];
	Control_RGB_LEDs(0,0,1);
	while(1){ 
		if(~(PORTA->ISFR) & MASK(16)){
			Control_RGB_LEDs(0,1,0);
		}
		//UART1_READ(transmittedMessage);
		//float distance = atof(transmittedMessage);
			
//		if (distance < 15){
//			Control_RGB_LEDs(1,0,0);
//		}
//		else {
//			Control_RGB_LEDs(0,1,0);
//		}
			
		//Delay(500);		
	}
	
	/*
	Init_LCD();
	Init_Drive_Motor();
	Init_PWM();
	
	Init_RGB_LEDs();
	
	UART1_INIT(UART_BAUDRATE_300, 128);
	char transmittedMessage[5];
	char displayMessage[17];
	char testing[10];
	int distance = 100;
	
	while(1){
		Set_Forward(80);		
		//Clear_LCD();
		UART1_READ(transmittedMessage);
			
			//sprintf(displayMessage, "%s cm", transmittedMessage);
		int distance = atoi(transmittedMessage);
		
		Clear_LCD();
		Set_Cursor(0,0);
		Print_LCD(transmittedMessage);
		
		//Delay(20);
		if( distance >= 1 && distance < 15){
			Control_RGB_LEDs(1,0,0);
			Set_Stop();
			//break;
		}
		else{
			Control_RGB_LEDs(0,1,0);
		}
		//Control_RGB_LEDs(1,1,1);
			//Clear_LCD();
			//Set_Cursor(0,0);
			//Print_LCD(displayMessage);
			
	Delay(100);		
	}
	
	*/
	#endif
	#if 0
	int default_brightness;
	int brightness_diff = 0;
	int curr_brightness;
	char num_rotations[10];
	int rotations = 0;
	int black = 1;
	int rpm = 0;
	unsigned ticks = 0;
	int time = 0;
	char rpm_value[10];
	
	Init_ADC();
	//Init_RGB_LEDs();
	Init_IR_LED();
	//Control_RGB_LEDs(0, 0, 0);
	Init_LCD();
	
	Init_PITs(PIT_MAX_VALUE, TIMEOUT_VALUE);
	
	default_brightness = get_avg_diff();
	sprintf(num_rotations, "%5d", default_brightness);
	
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("        0");
	Start_PITs();
	while (1) {
		curr_brightness = get_avg_diff();
		
		// light RGB LED according to range
		// Display_Range(avg_diff);
		// Delay(50);
		if(timeout){
			Stop_PITs();
			timeout = 0;
			rpm = 0;
			Start_PITs();
			Set_Cursor(0, 1);
			Print_LCD("0        ");
		}
			
		/*
		if timeout
			set rpm to 0
			set timeout false
		*/
		brightness_diff = default_brightness - curr_brightness;
		if (black && (brightness_diff > BRIGHTNESS_RANGE || brightness_diff < -BRIGHTNESS_RANGE)) {
			rotations++;
			black = 0;
			
			ticks = PIT_MAX_VALUE - Get_RPM_PIT_Val();
			Stop_PITs();
			Start_PITs();
			rpm = (int) ConvertTicksToRPM(ticks);
			
			sprintf(rpm_value, "%d", rpm);
			
			
			
			/*
			stop pit and read value
			
			start both PIT
			do math			
			output value
			*/
			sprintf(num_rotations, "%9d", rotations);
			
			Clear_LCD();
			
			Set_Cursor(0, 1);
			Print_LCD(rpm_value);
			
			Set_Cursor(0, 0);
			Print_LCD(num_rotations);
			
		} else if (!black && (brightness_diff < BRIGHTNESS_RANGE && brightness_diff > -BRIGHTNESS_RANGE)) {
			black = 1;
		}
	}
	#endif
}
void PORTA_IRQHandler(void) {
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	if(PORTA->ISFR & MASK(16)) {
		Control_RGB_LEDs(1,0,0);
	}
	PORTA->ISFR = 0xffffffff;
	
}

// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   
