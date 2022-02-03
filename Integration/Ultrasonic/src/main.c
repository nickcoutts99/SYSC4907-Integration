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

#define BUFFER_SIZE (4)
volatile uint8_t hour=0, minute=0, second=0;
volatile uint16_t millisecond=0;

volatile int tpm0_flag = 0;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
#if 0
	float measurement = 0;
	char measurementStr[17];
	Init_RGB_LEDs();
	Init_PIT(240); //gives us a period of 10 microseconds
	Init_Ultrasonic();
	Init_LCD();
	__enable_irq();
	Clear_LCD();
	Set_Cursor(0,0);
	Init_TPM();
	while(1) {
		Generate_Trigger();
		Measure_Reading(&measurement);
		sprintf(measurementStr, "%d", (int) measurement);
		Set_Cursor(0,1);
		Print_LCD(measurementStr);
		toggle_RGB_LEDs(1,0,0);
		Delay(1000);
		Clear_LCD();
	}
	
#else
	float measurement = 0;
	char measurementStr[BUFFER_SIZE];
	Init_RGB_LEDs();
	Init_LCD();
	Init_PIT(240); //gives us a period of 10 microseconds
	Init_Ultrasonic();
	UART1_INIT(UART_BAUDRATE_300, 128);
	__enable_irq();
	int minimumDist = 200;
	Init_TPM();
	while(1) {
		Generate_Trigger();
		Measure_Reading(&measurement);
		snprintf(measurementStr,BUFFER_SIZE, "%d", (int) measurement);
		Set_Cursor(0,1);
		Print_LCD(measurementStr);
		toggle_RGB_LEDs(1,0,0);
		if(measurement < minimumDist){ 
			UART1_SEND("5");
			
			Delay(2000);
			Clear_LCD();
		}
	}

#endif
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
