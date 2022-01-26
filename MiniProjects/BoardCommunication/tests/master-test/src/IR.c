#include "IR.h"

int Threshold[NUM_RANGE_STEPS] = {34000, 27000, 20000, 14000, 8000, 0};
const int Colors[NUM_RANGE_STEPS][3] = {{1, 1, 1},	// white
										{1, 0, 1},	// magenta
										{1, 0, 0},	// red
										{1, 1, 0},	// yellow
										{0, 0, 1},	// blue
										{0, 1, 0}}; // green

void Init_ADC(void)
{

	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT);
	ADC0->CFG1 = 0x9C; // 16 bit
	ADC0->SC2 = 0;
}

void Control_IR_LED(unsigned int led_on)
{
	if (led_on)
	{
		PTB->PCOR = MASK(IR_LED_POS);
	}
	else
	{
		PTB->PSOR = MASK(IR_LED_POS);
	}
}
void Init_IR_LED(void)
{
	PORTB->PCR[IR_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[IR_LED_POS] |= PORT_PCR_MUX(1);
	PTB->PDDR |= MASK(IR_LED_POS);

	// start off with IR LED turned off
	Control_IR_LED(0);
}

unsigned Measure_IR(void)
{
	volatile unsigned res = 0;

	ADC0->SC1[0] = IR_PHOTOTRANSISTOR_CHANNEL; // start conversion on channel 0

	while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		;
	res = ADC0->R[0];
	// complement result since voltage falls with increasing IR level
	// but we want result to rise with increasing IR level
	return 0xffff - res;
}

void Display_Range(int b)
{
	unsigned i;

	for (i = 0; i < NUM_RANGE_STEPS - 1; i++)
	{
		if (b > Threshold[i])
			break;
	}
	Control_RGB_LEDs(
		(unsigned)Colors[i][RED],
		(unsigned)Colors[i][GREEN],
		(unsigned)Colors[i][BLUE]);
}

void Delay_us(volatile unsigned int time_del)
{
	// This is a very imprecise and fragile implementation!
	time_del = 9 * time_del + time_del / 2;
	while (time_del--);
}
