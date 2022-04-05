#include <MKL25Z4.H>
#include "LEDs.h"
#define VREF (3.3)
#define R1 (1e6)
#define R2 (1e6)
#define SCALE_FACTOR ((R1+R2)/(R2))
#define MINVoltage (##)
#define MAXVoltage (##)
#define Range (80)
#define VoltSloap ((MaxVoltage-MinVoltage)/ Range)
void Init_ADC(void) {
	
	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT); 
	ADC0->SC3 &= ~(1UL << ADC_SC3_AVGE_MASK);//double check this
	ADC0->CFG1 = 0x0C; // Select 16 bit resolution
	ADC0->SC2 = 0;
	ADC0->CFG2|= 0x3;
}

double Get_Position(){
	volatile double res=0;
	volatile double voltage, angle;
	ADC0->SC1[0] = 0x00; // start conversion on channel 0 PTE20
	
	while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		;
	res = ADC0->R[0];
	voltage = VREF*(res/0xffff);
	//angle = (voltage * VoltSlope) - (Range/2);
	return voltage;
	//return angle;
}

