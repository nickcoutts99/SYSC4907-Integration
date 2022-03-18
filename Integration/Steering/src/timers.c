#include "timers.h"
#include "MKL25Z4.h"

volatile unsigned PIT_interrupt_counter = 0;
volatile unsigned LCD_update_requested = 0;

volatile unsigned timeout = 0;
#define TPM1_CH (1)

void Init_PITs(unsigned period, unsigned timeout_period) {
	// Enable clock to PIT module
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	// Enable module, freeze timers in debug mode
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	
	// Initialize PIT0 to count down from argument 
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(period);
	PIT->CHANNEL[1].LDVAL = PIT_LDVAL_TSV(timeout_period);

	// No chaining
	PIT->CHANNEL[0].TCTRL &= PIT_TCTRL_CHN_MASK;
	PIT->CHANNEL[1].TCTRL &= PIT_TCTRL_CHN_MASK;
	
	// Generate interrupts
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;

	/* Enable Interrupts */
	NVIC_SetPriority(PIT_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PIT_IRQn); 
	NVIC_EnableIRQ(PIT_IRQn);	
}

int Get_RPM_PIT_Val(){
	return PIT->CHANNEL[0].CVAL;
}


void Start_PITs(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void Stop_PITs(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[1].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}


void PIT_IRQHandler() {

	//clear pending IRQ
	NVIC_ClearPendingIRQ(PIT_IRQn);
	
	// check to see which channel triggered interrupt 
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		// clear status flag for timer channel 0
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		
				
	} else if (PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK) {
		// clear status flag for timer channel 1
		PIT->CHANNEL[1].TFLG &= PIT_TFLG_TIF_MASK;
		timeout = 1;
		
	} 
}

void Init_PWM()
{
	//turn on clock to TPM 
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	//set clock source for tpm
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//load the counter and mod
	TPM1->MOD = PWM_MAX_COUNT;
	//TPM2->MOD = 65535;
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[13] = PORT_PCR_MUX(3);
		
	//set channels to center-aligned high-true PWM
	TPM1->CONTROLS[TPM1_CH].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	//TPM1->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	
	//TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	//set TPM to up-down and divide by 8 prescaler and clock mode
	TPM1->SC = (TPM_SC_CPWMS_MASK | TPM_SC_CMOD(1) | TPM_SC_PS(3));
	//TPM2->SC = (TPM_SC_CMOD(1) | TPM_SC_PS(1));
	//set trigger mode
	TPM1->CONF |= TPM_CONF_TRGSEL(0x8);
	//TPM2->CONF |= TPM_CONF_TRGSEL(0x8);
	
	TPM1->CONTROLS[TPM1_CH].CnV = PWM_MAX_COUNT;
}


void Set_PWM_Value_Ch0(uint8_t duty_cycle) {
	uint16_t n;
	
	n = duty_cycle*PWM_MAX_COUNT/100; 
  TPM1->CONTROLS[TPM1_CH].CnV = n;
}
// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   
