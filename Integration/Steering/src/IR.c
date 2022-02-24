#include <MKL25Z4.H>
#include <stdio.h>
#include "IR.h"
#include "LEDs.h"
#include "timers.h"

// Hard-coded black and white -> which is closer to value
int Threshold[NUM_RANGE_STEPS] = {34000, 27000, 20000, 14000, 8000, 0};

const int Colors[NUM_RANGE_STEPS][3] = {{ 1, 1, 1}, // white
																	{ 1, 0, 1}, // magenta
																	{ 1, 0, 0}, // red
																	{ 1, 1, 0}, // yellow
																	{ 0, 0, 1}, // blue
																	{ 0, 1, 0}};// green 

void Init_ADC(void) {
	
	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT); 
	ADC0->CFG1 = 0x9C; //1001 1100 16 bit //Configuration register 1, 465
	ADC0->SC2 = 0;  //not using any comparators
}

void Control_IR_LED(unsigned int led_on) {
	if (led_on) {
			PTB->PCOR = MASK(IR_LED_POS); // if led_on is 1, then it is cleared to 0, turning LED on, active low 
	} else {
			PTB->PSOR = MASK(IR_LED_POS); // if led_on is 0, then its setting it to 1, LED off, active low
	}
}	
void Init_IR_LED(void) {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	PORTB->PCR[IR_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[IR_LED_POS] |= PORT_PCR_MUX(1);          
	PTB->PDDR |= MASK(IR_LED_POS); // Setting the Port Data Direction Register to output
	
	// start off with IR LED turned off
	Control_IR_LED(0);
}

unsigned Measure_IR(void) {
	volatile unsigned res=0;
	
	// settign it to portB bit 0
	ADC0->SC1[0] = IR_PHOTOTRANSISTOR_CHANNEL; // start conversion on channel 0, 8th bit setting to 1, conversion complete flag
	
	while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)) // while conversion not done, keep waiting to be done
		;
	res = ADC0->R[0]; // storing the reading from the IR sensor 
	// complement result since voltage falls with increasing IR level
	// but we want result to rise with increasing IR level
	
	return 0xffff-res; // we have the voltage falling, we need the voltage rising so we complement it
}

void Display_Range(int b) {
	unsigned i;
	
	for (i=0; i<NUM_RANGE_STEPS-1; i++) {
		if (b > Threshold[i])
			break;
	}
	Control_RGB_LEDs(Colors[i][RED], Colors[i][GREEN], Colors[i][BLUE]);
}

void Delay_us(volatile unsigned int time_del) {
	// This is a very imprecise and fragile implementation!
	time_del = 9*time_del + time_del/2; 
	while (time_del--) {
		;
	}
}

int get_avg_diff(void) {
	int on_brightness = 0, off_brightness=0;
	int avg_diff;
	int diff;
	unsigned n;
	
	diff = 0;
	
	for (n = 0; n < NUM_SAMPLES_TO_AVG; n++) {
		// measure IR level with IRLED off
		Control_IR_LED(0);
		Delay_us(T_DELAY_OFF);
		off_brightness = Measure_IR();
	
		// measure IR level with IRLED on
		Control_IR_LED(1);
		Delay_us(T_DELAY_ON);
		on_brightness = Measure_IR();
		
		// there is a base brightness
		// there is a different in brightness when the IR LED reads its 
		// hence need to calculate brightness

		// calculate difference
		diff += on_brightness - off_brightness;
	}
	avg_diff = diff/NUM_SAMPLES_TO_AVG;
	
	return avg_diff;
}

int ConvertTicksToRPM(unsigned ticks){
	float seconds = ticks/BUS_CLOCK_FREQUENCY;
	return 60/seconds;
}
/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
/*
int main (void) {
	int default_brightness;
	int temp = 0;
	int curr_brightness;
	char num_rotations[10];
	int rotations = 0;
	int black = 1;
	char brightness_value[10];
	
	Init_ADC();
	//Init_RGB_LEDs();
	Init_IR_LED();
	//Control_RGB_LEDs(0, 0, 0);
	Init_LCD();
	
	default_brightness = get_avg_diff();
	sprintf(num_rotations, "%5d", default_brightness);
	
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("        0");
	
	while (1) {
		curr_brightness = get_avg_diff();
		
		// light RGB LED according to range
		// Display_Range(avg_diff);
		// Delay(50);
		
		temp = default_brightness - curr_brightness;
		if (black && (temp > BRIGHTNESS_RANGE || temp < -BRIGHTNESS_RANGE)) {
			rotations++;
			black = 0;
			
			sprintf(brightness_value, "%5d", curr_brightness);
			sprintf(num_rotations, "%9d", rotations);
			
			Clear_LCD();
			
			Set_Cursor(0, 1);
			Print_LCD(brightness_value);
			
			Set_Cursor(0, 0);
			Print_LCD(num_rotations);
			
		} else if (!black && (temp < BRIGHTNESS_RANGE && temp > -BRIGHTNESS_RANGE)) {
			black = 1;
		}
	}
}
*/
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
