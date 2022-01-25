#include <MKL25Z4.h>
#include <stdio.h>
#include "LEDs.h"
#include "IR.h"
#include "uart.h"
#include "LCD_4bit.h"
#include "delay.h"

#define UART_EN

#define IR_SAMPLE_PERIOD 40000
#define UART_BAUDRATE 300

volatile uart_transceiver_t uart1_transceiver;
volatile uart_transceiver_t uart2_transceiver;

int main(void)
{
	static unsigned on_brightness = 0, off_brightness = 0;
	static int avg_diff;
	static int diff;
	unsigned n;

	Init_UART1(UART_BAUDRATE, sizeof(uint16_t), &uart1_transceiver);
  
	Init_LCD();	
	Clear_LCD();
	Set_Cursor(0, 0);
	Print_LCD("Hello World");
	
	Init_ADC();	
	Init_RGB_LEDs();
	Init_IR_LED();
	Control_RGB_LEDs(0, 0, 0);	
	
	__enable_irq();
	
	while (1)
	{
		diff = 0;
		for (n = 0; n < NUM_SAMPLES_TO_AVG; n++)
		{
			// measure IR level with IRLED off
			Control_IR_LED(0);
			Delay_us(T_DELAY_OFF);
			off_brightness = Measure_IR();

			// measure IR level with IRLED on
			Control_IR_LED(1);
			Delay_us(T_DELAY_ON);
			on_brightness = Measure_IR();

			// calculate difference
			diff += on_brightness - off_brightness;
		}
		avg_diff = diff / NUM_SAMPLES_TO_AVG;

		// light RGB LED according to range
		Display_Range(avg_diff);

		#ifdef UART_EN
		send_data(&uart1_transceiver, &avg_diff);
		#endif

		Delay(10);
	}
}
