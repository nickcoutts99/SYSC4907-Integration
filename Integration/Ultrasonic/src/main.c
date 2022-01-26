/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include <stdio.h>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "LEDs.h"
#include "timers.h"
#include "delay.h"
#include "ultrasonic.h"
#include "uart.h"

volatile uint8_t hour=0, minute=0, second=0;
volatile uint16_t millisecond=0;

volatile int tpm0_flag = 0;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
#if 0
	char buffer[9];
	
	Init_RGB_LEDs();
	PORTD->PCR[0] = PORT_PCR_MUX(4);
	// Init_LCD();
	Init_PIT(BUS_CLOCK_FREQUENCY/TICK_FREQUENCY);
	Init_PWM();
	
	Control_RGB_LEDs(0,0,0);

	/*
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD(" Hello  ");
	Set_Cursor(0,1);
	Print_LCD(" World! ");
	*/

	__enable_irq();
	
	Start_PIT();
	// Clear_LCD();
	
	
	while (1) {
		
		Control_RGB_LEDs(0, 0, 0);
		Delay(10);
		
		/*
		if (LCD_update_requested) {
			LCD_update_requested = 0; // Clear the request
			sprintf(buffer, "%02d:%02d", hour, minute);
			Set_Cursor(0,0);
			Print_LCD(buffer);
			sprintf(buffer, "%02d.%03d", second, millisecond);
			Set_Cursor(0,1);
			Print_LCD(buffer);
		}
		*/
	}
#else
	float measurement = 0;
	char measurementStr[17];
	Init_RGB_LEDs();
	Init_PIT(240); //gives us a period of 10 microseconds
	Init_Ultrasonic();
	//Init_LCD();
	UART1_INIT(UART_BAUDRATE_300, 128);
	__enable_irq();
	//Clear_LCD();
	Set_Cursor(0,0);
	Init_TPM();
	while(1) {
		Generate_Trigger();
		Measure_Reading(&measurement);
		sprintf(measurementStr, "%f", measurement);
		UART1_SEND(measurementStr);
		//Set_Cursor(0,1);
		//Print_LCD(measurementStr);
		toggle_RGB_LEDs(1,0,0);
		Delay(1000);
		//Clear_LCD();
	}

#endif
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
