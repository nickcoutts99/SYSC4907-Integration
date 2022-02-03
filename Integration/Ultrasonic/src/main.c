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

#define UART_EN

#define IR_SAMPLE_PERIOD 40000
#define UART_BAUDRATE 300

volatile uart_transceiver_t uart1_transceiver;
volatile uart_transceiver_t uart2_transceiver;


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	static unsigned on_brightness = 0, off_brightness = 0;
	static int avg_diff;
	static int diff;
	unsigned n;

	Init_UART1(UART_BAUDRATE, sizeof(uint16_t), &uart1_transceiver);
  
	Init_LCD();	
	Clear_LCD();
	Set_Cursor(0, 0);
	Print_LCD("Hello World");
	
	//Init_ADC();	
	Init_RGB_LEDs();
	//Init_IR_LED();
	Control_RGB_LEDs(0, 0, 0);	
	
	__enable_irq();
	
	while(1) {
		avg_diff = 5;

		// light RGB LED according to range
		//Display_Range(avg_diff);
			
		#ifdef UART_EN
		send_data(&uart1_transceiver, &avg_diff);
		#endif
		
		Delay(10);
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
