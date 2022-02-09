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

#define TESTING_MOTOR 1
#define TESTING_LCD 0


volatile uint8_t hour=0, minute=0, second=0;
volatile uint16_t millisecond=0;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	
	#if TESTING_MOTOR
	Init_PIT(BUS_CLOCK_FREQUENCY/TICK_FREQUENCY);
  Init_PWM();
	Init_Drive_Motor();

	__enable_irq();
	Start_PIT();
	UART1_INIT(UART_BAUDRATE_300, 128);
	char transmittedMessage[4];
	char displayMessage[17];
  int objectClose = 0;
	int distance = 0;
	#endif
	#if 0
	while (!objectClose) {
		
		if (Get_Num_Rx_Chars_Available() >= 3) {
			UART1_READ(transmittedMessage);
			distance = atoi(transmittedMessage);
			
			if(distance < 50){
				objectClose = 1;
			}
		}
	}
	
	
	Set_Stop();
	#else
	Set_Forward(80);
	Delay(500);
	Set_Stop();
	Delay(500);
	Set_Reverse(50);
	Delay(500);
	Set_Stop();
	#endif
		
	#if TESTING_LCD
	Init_LCD();
	
	Init_RGB_LEDs();
	
	UART1_INIT(UART_BAUDRATE_9600, 128);
	char transmittedMessage[5];
	char displayMessage[17];
	char testing[10];
	Print_LCD("nada");
	Control_RGB_LEDs(0,0,1);
	while(1){ 
		Clear_LCD();
		sprintf(testing,"%d",Get_Num_Rx_Chars_Available());
		Print_LCD(testing);
		if (Get_Num_Rx_Chars_Available() > 0) {
			Control_RGB_LEDs(0,1,0);
			UART1_READ(transmittedMessage);
			Control_RGB_LEDs(1,0,0);
			sprintf(displayMessage, "%s cm", transmittedMessage);
			Clear_LCD();
			Set_Cursor(0,0);
			Print_LCD(displayMessage);
			
		}	
	Delay(1000);		
	}
	#endif
}


// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   
