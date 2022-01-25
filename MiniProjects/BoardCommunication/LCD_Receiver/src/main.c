#include <MKL25Z4.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "delay.h"
#include "uart.h"
#include "switches.h"
#include "math.h"

#define UART_EN

#define BUFF_SIZE (16)

extern uint8_t CR_received;

volatile uart_transceiver_t uart1_transceiver;
volatile uart_transceiver_t uart2_transceiver;
volatile unsigned send_button = 0;
volatile unsigned send_button_update = 0;
#define UART_BAUDRATE 9600


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	uint16_t i;
	float f;
	
	Init_UART1(UART_BAUDRATE, sizeof(uint16_t), &uart1_transceiver);

	
	/*
	//polling approach
	char bugger[16];
	*/
	
	//interrupt approach
	char buff[BUFF_SIZE];
	__enable_irq();
	
	Init_4way_Switch();
	
	Init_LCD();
	Set_Cursor(0,0);
	Print_LCD("bruh");
	
	while(1) {
		/*
		//polling approach
		i = 0;
		i |= (uint16_t)(UART1_Receive_Poll() << 8);
		i |= (uint8_t)UART1_Receive_Poll();
		sprintf(bugger, "IR: %u", i);
		Clear_LCD();
		Set_Cursor(0,0);
		Print_LCD(bugger);
		Set_Cursor(0,1);
		Print_LCD("Polling);
		Delay(10);
		*/
		
		//interrupt approach
		
		if (Get_Num_Rx_Chars_Available() >= 2) {
			get_data(&uart1_transceiver, &i);
			f = -13.54 * log(i) + 144.48;
			sprintf(buff, "IR: %f cm", f);
			//Clear_LCD();
			Set_Cursor(0,0);
			Print_LCD(buff);
			Delay(5);
		}
		/*
		if (send_button_update) {
			send_data(&uart1_transceiver, &send_button);
			send_button_update = 0;
		}
		*/
		
		
		send_data(&uart1_transceiver, &send_button);
		sprintf(buff, "Sent: %u", send_button);
		//Clear_LCD();
		Set_Cursor(0,1);
		Print_LCD(buff);
		Delay(500);
		send_button++;
		
	}
}

// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
