#include "motor.h"
void Init_Drive_Motor(){
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//set to GPIO
	PIN_INA1_PORT->PCR[PIN_INA1_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	PIN_INA1_PORT->PCR[PIN_INA1_SHIFT] |= PORT_PCR_MUX(1); 
	PIN_INA1_PT->PDDR |= PIN_INA1; //output
	
	
	//set to GPIO
	PIN_INB1_PORT->PCR[PIN_INB1_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	PIN_INB1_PORT->PCR[PIN_INB1_SHIFT] |= PORT_PCR_MUX(1); 
	PIN_INB1_PT->PDDR |= PIN_INB1; //output
}
void Init_Steering_Motor(){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

	//set to GPIO
	PIN_INA2_PORT->PCR[PIN_INA2_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	PIN_INA2_PORT->PCR[PIN_INA2_SHIFT] |= PORT_PCR_MUX(1); 
	PIN_INA2_PT->PDDR |= PIN_INA2; //output
	
	
	//set to GPIO
	PIN_INB2_PORT->PCR[PIN_INB2_SHIFT] &= ~PORT_PCR_MUX_MASK;          
	PIN_INB2_PORT->PCR[PIN_INB2_SHIFT] |= PORT_PCR_MUX(1); 
	PIN_INB2_PT->PDDR |= PIN_INB2; //output
}

void Set_Drive_Stop(){
	PIN_INA1_PT->PCOR |= PIN_INA1;
	PIN_INB1_PT->PCOR |= PIN_INB1;
	Set_PWM_Value_Ch0(0);
}


void Set_Drive_Forward(uint8_t duty_cycle){
	PIN_INA1_PT->PCOR |= PIN_INA1;
	PIN_INB1_PT->PSOR |= PIN_INB1;
	Set_PWM_Value_Ch0(duty_cycle);
}

void Set_Drive_Reverse(uint8_t duty_cycle){
	PIN_INA1_PT->PSOR |= PIN_INA1;
	PIN_INB1_PT->PCOR |= PIN_INB1;
	Set_PWM_Value_Ch0(duty_cycle);
}

void Set_Steering_Stop(){
	PIN_INA2_PT->PCOR |= PIN_INA2;
	PIN_INB2_PT->PCOR |= PIN_INB2;
	Set_PWM_Value_Ch0(0);
}


void Set_Steering_Forward(uint8_t duty_cycle){
	PIN_INA2_PT->PCOR |= PIN_INA2;
	PIN_INB2_PT->PSOR |= PIN_INB2;
	Set_PWM_Value_Ch0(duty_cycle);
}

void Set_Steering_Reverse(uint8_t duty_cycle){
	PIN_INA2_PT->PSOR |= PIN_INA2;
	PIN_INB2_PT->PCOR |= PIN_INB2;
	Set_PWM_Value_Ch0(duty_cycle);
}