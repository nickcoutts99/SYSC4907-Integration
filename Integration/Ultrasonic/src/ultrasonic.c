#include "ultrasonic.h"

volatile extern int measureFlag;
volatile extern int timeoutFlag;
extern volatile int ticksElapsed;
volatile extern int overflow;

//Speed of sound in cm/ms
float speedOfSound = 34.3;
float ticksToMilliseconds = 50000.0/8;

void Init_Ultrasonic(void)
{
  	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTE_MASK;

	//set to GPIO
	PIN_TRIG_PORT->PCR[PIN_TRIG_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	PIN_TRIG_PORT->PCR[PIN_TRIG_SHIFT] |= PORT_PCR_MUX(1); 
	PIN_TRIG_PT->PDDR |= PIN_TRIG; //output
	
	//Set pin multiplexer to TPM2_CH4 mode and enable 
	PIN_ECHO_PORT->PCR[PIN_ECHO_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	PIN_ECHO_PORT->PCR[PIN_ECHO_SHIFT] = PORT_PCR_MUX(4);

	
}

void Generate_Trigger(){
	PIN_TRIG_PT->PSOR |= PIN_TRIG;
	Start_PIT1();
	TPM0->SC |= TPM_SC_CMOD(1);
}

void Measure_Reading(float* measurement) {
	
	
	Start_PIT2();//start the timeout timer
	double timeElapsed = 0;
	//Poll until we receive the measuring flag
	while(!measureFlag){
		if(timeoutFlag){return;}
	}
	
	
	//reset overflow counter
	overflow = 0;
	//convert ticks to miliseconds
	timeElapsed = ticksElapsed / ticksToMilliseconds;
	
	//Distance (cm) = (Time of Entire Pulse (ms) / 2) * speed of sound (cm/ms)
	*measurement = (timeElapsed* speedOfSound) / 2;
	
	//reset ticks elapsed
	ticksElapsed = 0;
	measureFlag = 0;
}