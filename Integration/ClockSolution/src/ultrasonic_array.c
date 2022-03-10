#include "ultrasonic_array.h"
#include <stdio.h>

volatile extern int overflow;
TRIG_TYPE* pit_trig;

TRIG_TYPE curr_trig = {
	.ultrasonicTrigSCGCMask = SIM_SCGC5_PORTA_MASK,
	.trigPort = PORTA,
	.trigPortGPIO = PTA,
	.trigPin = 17
};

ULTRASONIC_SENSOR ultrasonic_front = {
	.index = 0,
	.measurementSum = 0,
	.measureFlag = 0,
	.isEchoFalling = 0,
	
	//Trigger: PTA 17
	.trigger.ultrasonicTrigSCGCMask = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTD_MASK,
	.trigger.trigPort = PORTA,
	.trigger.trigPortGPIO = PTA,
	.trigger.trigPin = 17,
	
	//Echo: PTD 0
	.ultrasonicEchoSCGCMask = SIM_SCGC6_TPM0_MASK,
	.echoPort = PORTD,
	.echoPin = 0,
	.echoTPMMux = 4,
};

ULTRASONIC_SENSOR ultrasonic_frontleft = {
	.index = 1,
	.measurementSum = 0,
	.measureFlag = 0,
	.isEchoFalling = 0,
	
	//Trigger: PTA 16
	.trigger.ultrasonicTrigSCGCMask = SIM_SCGC5_PORTA_MASK  | SIM_SCGC5_PORTC_MASK,
	.trigger.trigPort = PORTA,
	.trigger.trigPortGPIO = PTA,
	.trigger.trigPin = 16,
	
	//Echo: PTC 2
	.ultrasonicEchoSCGCMask = SIM_SCGC6_TPM0_MASK,
	.echoPort = PORTC,
	.echoPin = 2,
	.echoTPMMux = 4,
};

ULTRASONIC_SENSOR ultrasonic_frontright = {
	.index = 2,
	.measurementSum = 0,
	.measureFlag = 0,
	.isEchoFalling = 0,
	
	//Trigger: PTC 17
	.trigger.ultrasonicTrigSCGCMask = SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK,
	.trigger.trigPort = PORTC,
	.trigger.trigPortGPIO = PTC,
	.trigger.trigPin = 17,
	
	//Echo: PTD 2
	.ultrasonicEchoSCGCMask = SIM_SCGC6_TPM0_MASK,
	.echoPort = PORTD,
	.echoPin = 2,
	.echoTPMMux = 4,
};

ULTRASONIC_SENSOR ultrasonic_back = {
	.index = 3,
	.measurementSum = 0,
	.measureFlag = 0,
	.isEchoFalling = 0,
	
	//Trigger: PTC 16
	.trigger.ultrasonicTrigSCGCMask = SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK,
	.trigger.trigPort = PORTC,
	.trigger.trigPortGPIO = PTC,
	.trigger.trigPin = 16,
	
	//Echo: PTD 3
	.ultrasonicEchoSCGCMask = SIM_SCGC6_TPM0_MASK,
	.echoPort = PORTD,
	.echoPin = 3,
	.echoTPMMux = 4,
};

ULTRASONIC_SENSOR ultrasonic_backleft = {
	.index = 4,
	.measurementSum = 0,
	.measureFlag = 0,
	.isEchoFalling = 0,
	
	//Trigger: PTC 13
	.trigger.ultrasonicTrigSCGCMask = SIM_SCGC5_PORTC_MASK,
	.trigger.trigPort = PORTC,
	.trigger.trigPortGPIO = PTC,
	.trigger.trigPin = 13,
	
	//Echo: PTC 8
	.ultrasonicEchoSCGCMask = SIM_SCGC6_TPM0_MASK,
	.echoPort = PORTC,
	.echoPin = 8,
	.echoTPMMux = 3,
};

ULTRASONIC_SENSOR ultrasonic_backright = {
	.index = 5,
	.measurementSum = 0,
	.measureFlag = 0,
	.isEchoFalling = 0,
	
	//Trigger: PTC 12
	.trigger.ultrasonicTrigSCGCMask = SIM_SCGC5_PORTC_MASK,
	.trigger.trigPort = PORTC,
	.trigger.trigPortGPIO = PTC,
	.trigger.trigPin = 12,
	
	//Echo: PTC 9
	.ultrasonicEchoSCGCMask = SIM_SCGC6_TPM0_MASK,
	.echoPort = PORTC,
	.echoPin = 9,
	.echoTPMMux = 3,
};

void Ultrasonic_Init(ULTRASONIC_SENSOR* ultrasonic_cfg) {
	
	SIM->SCGC5 |= ultrasonic_cfg->trigger.ultrasonicTrigSCGCMask | SIM_SCGC5_PORTD_MASK;

	//set to GPIO
	ultrasonic_cfg->trigger.trigPort->PCR[ultrasonic_cfg->trigger.trigPin] &= ~PORT_PCR_MUX_MASK;          
	ultrasonic_cfg->trigger.trigPort->PCR[ultrasonic_cfg->trigger.trigPin] |= PORT_PCR_MUX(1); 
	ultrasonic_cfg->trigger.trigPortGPIO->PDDR |=  (1 << ((int) ultrasonic_cfg->trigger.trigPin)); //output
	
	//Set pin multiplexer to TPM channel modes on echo pins 
	printf("%d", ultrasonic_cfg->echoPin);
	ultrasonic_cfg->echoPort->PCR[ultrasonic_cfg->echoPin] &= ~PORT_PCR_MUX_MASK;    
	ultrasonic_cfg->echoPort->PCR[ultrasonic_cfg->echoPin] |= PORT_PCR_MUX(ultrasonic_cfg->echoTPMMux);
}

void Generate_Trigger(ULTRASONIC_SENSOR* ultrasonic_cfg){
	//Generate triggers at the front sensors
	curr_trig = ultrasonic_cfg->trigger;
	pit_trig = &(ultrasonic_cfg->trigger);
	curr_trig.trigPortGPIO->PSOR |= (1 << ((int) curr_trig.trigPin));
	Start_PIT();
	TPM0->SC |= TPM_SC_CMOD(1);
}


void Start_PIT(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void Measure_Reading(ULTRASONIC_SENSOR* ultrasonic_cfg) {
	
	//Speed of sound in cm/ms
	float speedOfSound = 34.3;
	double timeElapsed = 0;
	float measurement = 0;
	//Poll until we receive the measuring flag
	while(!(ultrasonic_cfg->measureFlag)){
		
	}
	
	//reset overflow counter
	overflow = 0;
	
	//convert ticks to miliseconds
	timeElapsed = ultrasonic_cfg->ticksElapsed / 50000.0 * PRESCALE_FACTOR;
	
	//Distance (cm) = (Time of Entire Pulse (ms) / 2) * speed of sound (cm/ms)
	measurement = (timeElapsed * speedOfSound) / 2; 
	Q_Enqueue(&(ultrasonic_cfg->samples), measurement);
	
	//Add current time to running total
	ultrasonic_cfg->measurementSum += measurement;
	
	//reset ticks elapsed
	ultrasonic_cfg->ticksElapsed = 0;
	ultrasonic_cfg->measureFlag = 0;
	
}
