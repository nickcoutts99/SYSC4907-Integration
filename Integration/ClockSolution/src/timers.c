#include "timers.h"
#include "LEDs.h"
#include "delay.h"
//#include "ultrasonic.h"
#include <stdlib.h>

volatile int overflow = 0;
extern TRIG_TYPE* pit_trig;

void Init_PIT(unsigned period) {
	// Enable clock to PIT module
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	// Enable module, freeze timers in debug mode
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	
	// Initialize PIT0 to count down from argument 
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(period);

	// No chaining
	PIT->CHANNEL[0].TCTRL &= PIT_TCTRL_CHN_MASK;
	
	// Generate interrupts
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

	/* Enable Interrupts */
	NVIC_SetPriority(PIT_IRQn, 64); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PIT_IRQn); 
	NVIC_EnableIRQ(PIT_IRQn);	
}

void Stop_PIT(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}


void PIT_IRQHandler() {
	//clear pending IRQ
	NVIC_ClearPendingIRQ(PIT_IRQn);
	
	// check to see which channel triggered interrupt 
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		// clear status flag for timer channel 0
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;

		pit_trig->trigPortGPIO->PCOR |= (1 << ((int) pit_trig->trigPin));
		
	} else if (PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK) {
		// clear status flag for timer channel 1
		PIT->CHANNEL[1].TFLG &= PIT_TFLG_TIF_MASK;
	} 
}

// ================================================================================
// TPM IRQ and init here:w

// ================================================================================

void TPM0_IRQHandler(void) {
	
	NVIC_ClearPendingIRQ(TPM0_IRQn);

	ULTRASONIC_SENSOR* currUltrasonic = NULL;
	
	if(TPM0->STATUS & TPM_STATUS_CH0F_MASK){
		currUltrasonic = &ultrasonic_front;
	}
	
	else if(TPM0->STATUS & TPM_STATUS_CH1F_MASK){
		currUltrasonic = &ultrasonic_frontleft;
	}
	else if(TPM0->STATUS & TPM_STATUS_CH2F_MASK){
		currUltrasonic = &ultrasonic_frontright;
	}
	else if(TPM0->STATUS & TPM_STATUS_CH3F_MASK){
		currUltrasonic = &ultrasonic_back;
	}
	else if(TPM0->STATUS & TPM_STATUS_CH4F_MASK){
		currUltrasonic = &ultrasonic_backleft;
	}
	else if(TPM0->STATUS & TPM_STATUS_CH5F_MASK){
		currUltrasonic = &ultrasonic_backright;
	}
	
	//Keep track of overflow for time elapsed
	if(TPM0->STATUS & TPM_STATUS_TOF_MASK){
		
		//clear timer overflow flag and increment overflow counter
		TPM0->SC |= TPM_SC_TOF_MASK;
		overflow++;
	}
	
	//Rising edge or falling edge has occured, measurement has either started or completed
	if(currUltrasonic != NULL) {
		
		//Clear channel flag
		TPM0->CONTROLS[currUltrasonic->index].CnSC |= TPM_CnSC_CHF_MASK;
		
		//When it's rising edge start measuring
		if(!(currUltrasonic->isEchoFalling)) {

			//Signal to start measurement and set counter value to 0
			currUltrasonic->isEchoFalling = 1;
			TPM0->CONTROLS[currUltrasonic->index].CnV = 0;
		}
		
		//When it's falling edge capture time elapsed
		else {
			// Get the time elapsed
			currUltrasonic->ticksElapsed = TPM0->CONTROLS[currUltrasonic->index].CnV + overflow*PWM_MAX_COUNT;
			
			//Set the flag that the measurement is complete
			currUltrasonic->measureFlag = 1;
			
			currUltrasonic->isEchoFalling = 0;
			
			//Disable TPM
			//TPM0->SC &= ~(TPM_SC_CMOD_MASK);
		}
	}
}

void Init_TPM(ULTRASONIC_SENSOR* ultrasonic_cfg)
{
	//turn on clock to TPM 
	SIM->SCGC6 |= ultrasonic_cfg->ultrasonicEchoSCGCMask;
	
	//set clock source for tpm
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//load the counter and mod
	TPM0->MOD = PWM_MAX_COUNT;
	
	// This may be optional for input capture mode
	TPM0->CNT = 0;
	
	//Clear channel and set it as input capture mode with interrupts enabled for that channel
	TPM0->CONTROLS[ultrasonic_cfg->index].CnSC = 0;
	TPM0->CONTROLS[ultrasonic_cfg->index].CnSC = TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK;
	
	//Reload value after trigger
	TPM0->CONF |= TPM_CONF_CROT_MASK;
	//TPM0->CONF |= TPM_CONF_CSOT_MASK;
	
	TPM0->SC = (TPM_SC_CMOD(1) | TPM_SC_PS(3));
	
	// This may be optional for input capture mode
	TPM0->CONTROLS[ultrasonic_cfg->index].CnV = 0;	
}

void Init_TPM_IRQ() {
	//enable irq
	NVIC_SetPriority(TPM0_IRQn, 128);
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   