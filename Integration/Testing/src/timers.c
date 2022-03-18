#include "timers.h"
#include "MKL25Z4.h"

#define TPM1_CH (1)


void Init_PWM()
{
	//turn on clock to TPM 
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	//set clock source for tpm
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//load the counter and mod
	TPM1->MOD = PWM_MAX_COUNT;
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[13] = PORT_PCR_MUX(3);//TPM1 CH1
	PORTA->PCR[12] = PORT_PCR_MUX(3); //TPM1 CH0
		
	//set channels to center-aligned high-true PWM
	TPM1->CONTROLS[TPM1_CH].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	TPM1->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	
	//set TPM to up-down and divide by 8 prescaler and clock mode
	TPM1->SC = (TPM_SC_CPWMS_MASK | TPM_SC_CMOD(1) | TPM_SC_PS(3));
	
	//set trigger mode
	TPM1->CONF |= TPM_CONF_TRGSEL(0x8);
	//TPM2->CONF |= TPM_CONF_TRGSEL(0x8);
	
	TPM1->CONTROLS[0].CnV = PWM_MAX_COUNT;
	TPM1->CONTROLS[1].CnV = PWM_MAX_COUNT;
}


void Set_PWM_Value_Ch0(uint8_t duty_cycle) {
	uint16_t n;
	
	n = duty_cycle*PWM_MAX_COUNT/100; 
  TPM1->CONTROLS[0].CnV = n;
}
void Set_PWM_Value_Ch1(uint8_t duty_cycle) {
	uint16_t n;
	
	n = duty_cycle*PWM_MAX_COUNT/100; 
  TPM1->CONTROLS[1].CnV = n;
}
// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   
