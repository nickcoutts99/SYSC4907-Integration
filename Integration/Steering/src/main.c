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

#define UART_EN

#define BUFF_SIZE (16)

extern uint8_t CR_received;

volatile uart_transceiver_t uart1_transceiver;
volatile uart_transceiver_t uart2_transceiver;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	uint16_t i;
	
	Init_UART1(UART_BAUDRATE, sizeof(uint16_t), &uart1_transceiver);
	
	char buff[BUFF_SIZE];
	__enable_irq();
	
	Init_LCD();
	Set_Cursor(0,0);
	Print_LCD("bruh");
	
	while(1) {
		if (Get_Num_Rx_Chars_Available() >= 2) {
			Control_RGB_LEDs(0,1,0);
			i = 0;
			i = (uint16_t)get_data(&uart1_transceiver);
			sprintf(buff, "TEST: %u", i);
			Clear_LCD();
			Set_Cursor(0,0);
			Print_LCD(buff);
			Set_Cursor(0,1);
			Print_LCD("Interrupt");
			Delay(20);
		}
	}
}


// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   
