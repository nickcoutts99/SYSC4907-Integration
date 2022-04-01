#include "GPIO_defs.h"
#include "LEDs.h"
#include "motor.h"
volatile extern unsigned irStopSignal;

void Init_GPIO(){
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTD_MASK;
	
	ULTRASONIC_READING_PORT->PCR[ULTRASONIC_READING_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	ULTRASONIC_READING_PORT->PCR[ULTRASONIC_READING_SHIFT] |=  PORT_PCR_MUX(1) | PORT_PCR_IRQC(12); 
	ULTRASONIC_READING_PT->PDDR &= ~MASK(ULTRASONIC_READING_SHIFT); //input
	
	IR_STOP_SIGNAL_PORT->PCR[IR_STOP_SIGNAL_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	IR_STOP_SIGNAL_PORT->PCR[IR_STOP_SIGNAL_SHIFT] |=  PORT_PCR_MUX(1) | PORT_PCR_IRQC(12); 
	IR_STOP_SIGNAL_PT->PDDR &= ~MASK(IR_STOP_SIGNAL_SHIFT); //input
	
	NVIC_SetPriority(PORTA_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);
	/*
	NVIC_SetPriority(PORTD_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTD_IRQn); 
	NVIC_EnableIRQ(PORTD_IRQn);*/
	
}

int check_ultrasonic_low(){
	return (~(ULTRASONIC_READING_PORT->ISFR) & MASK(ULTRASONIC_READING_SHIFT));
}

void PORTA_IRQHandler(void) {
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	
	if(PORTA->ISFR & MASK(ULTRASONIC_READING_SHIFT)) { // Ultrasonic sensor has sent a high signal, meaning something is in front of vehicle
		Control_RGB_LEDs(1,0,0);
		Set_Stop();
	}
	PORTA->ISFR = 0xffffffff;	
}

void PORTD_IRQHandler(void) {
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	if(PORTD->ISFR & MASK(IR_STOP_SIGNAL_SHIFT)) {
		Control_RGB_LEDs(1,1,1);
		irStopSignal = 1;
	}
	NVIC_DisableIRQ(PORTD_IRQn);
	PORTD->ISFR = 0xffffffff;
	
}
