#include "ultrasonic.h"

volatile extern int measureFlag;
extern volatile int ticksElapsed;
volatile extern int overflow;

void Init_Ultrasonic(void)
{
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//set to GPIO
	PIN_TRIG_PORT->PCR[PIN_TRIG_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	PIN_TRIG_PORT->PCR[PIN_TRIG_SHIFT] |= PORT_PCR_MUX(1); 
	PIN_TRIG_PT->PDDR |= PIN_TRIG; //output
	
	//Set pin multiplexer to TPM2_CH4 mode and enable 
	PIN_ECHO_PORT->PCR[PIN_ECHO_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	PIN_ECHO_PORT->PCR[PIN_ECHO_SHIFT] = PORT_PCR_MUX(4);

	
}

//void Generate_Trigger(){
//	PIN_TRIG_PT->PSOR |= PIN_TRIG;
//	Start_PIT();
//	TPM0->SC |= TPM_SC_CMOD(1);
//}

//void Measure_Reading(float* measurement) {
//	
//	//Speed of sound in cm/ms
//	float speedOfSound = 34.3;
//	double timeElapsed = 0;
//	//Poll until we receive the measuring flag
//	while(!measureFlag){
//		//printf("%lu", (unsigned long)TPM2_C3V);
//	}
//	
//	
//	//reset overflow counter
//	overflow = 0;
//	//convert ticks to miliseconds
//	timeElapsed = ticksElapsed / 50000.0 * 8;
//	
//	//Distance (cm) = (Time of Entire Pulse (ms) / 2) * speed of sound (cm/ms)
//	*measurement = (timeElapsed* speedOfSound) / 2;
//	
//	//reset ticks elapsed
//	ticksElapsed = 0;
//	measureFlag = 0;
//}
