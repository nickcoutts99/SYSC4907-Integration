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

#define TESTING_MOTOR 0
#define TESTING_LCD 1


volatile uint8_t hour=0, minute=0, second=0;
volatile uint16_t millisecond=0;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	
	#if TESTING_MOTOR
	//Init_PIT(BUS_CLOCK_FREQUENCY/TICK_FREQUENCY);
  Init_PWM();
	Init_Drive_Motor();
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
		
	#if TESTING_LCD
	/*
	Init_LCD();
	Init_Drive_Motor();
	Init_PWM();
	
	Init_RGB_LEDs();
	
	UART1_INIT(UART_BAUDRATE_300, 128);
	char transmittedMessage[5];
	char displayMessage[17];
	char testing[10];
	//Print_LCD("nada");
	Control_RGB_LEDs(0,0,1);
	while(1){ 
		Clear_LCD();
//		sprintf(testing,"%d",Get_Num_Rx_Chars_Available());
//		Print_LCD(testing);
//		if (Get_Num_Rx_Chars_Available() > 0) {
			Control_RGB_LEDs(0,1,0);
			UART1_READ(transmittedMessage);
			Control_RGB_LEDs(1,0,0);
			sprintf(displayMessage, "%s cm", transmittedMessage);
			Clear_LCD();
			Set_Cursor(0,0);
			Print_LCD(displayMessage);
			
	Delay(500);		
	}*/
	
	///*
	//Init_LCD();
	Init_Drive_Motor();
	Init_PWM();
	
	Init_RGB_LEDs();
	
	UART1_INIT(UART_BAUDRATE_300, 128);
	char transmittedMessage[5];
	char displayMessage[17];
	char testing[10];
	//int distance = 100;
	//Print_LCD("nada");
	Control_RGB_LEDs(0,0,1);
	
	while(1){
		Set_Forward(80);		
		//Clear_LCD();
			Control_RGB_LEDs(1,0,0);
			UART1_READ(transmittedMessage);
			Control_RGB_LEDs(0,1,0);
			sprintf(displayMessage, "%s cm", transmittedMessage);
			int distance = atoi(transmittedMessage);
		if( distance > 0 && distance < 10){
			Control_RGB_LEDs(0,0,1);
			Set_Stop();
			//break;
		}
		//Control_RGB_LEDs(1,1,1);
			//Clear_LCD();
			//Set_Cursor(0,0);
			//Print_LCD(displayMessage);
			
	Delay(200);		
	}
	
	//*/
	#endif
}


// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   
