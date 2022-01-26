#include "timers.h"
#include "MKL25Z4.h"
#include "LEDs.h"

volatile unsigned PIT_interrupt_counter = 0;

void Init_PIT(unsigned period_us) {
	// Enable clock to PIT module
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	// Enable module, freeze timers in debug mode
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	
	// Initialize PIT0 to count down from argument 
	// 4800 = 0x12BF -> 24 MHz clock = 5000 interrupts per second
	// This is used for both sending pings against the wheel and
	// tracking time per rotation.
	PIT->CHANNEL[0].LDVAL = 0x12C0; // 24 MHz clock frequency

	// 5000 * 24 * 60 * 60 * 7 = 3,024,000,000
	// This equates to one interrupt per week (ideally should never occur)
	// Subtract one due to PIT requirements.
	// 3,023,999,999 = 0xB43E93FF
	PIT->CHANNEL[1].LDVAL = 0xB43E93FF;

	// Disable chaining on timer 0, as there is no lower timer to chain to.
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_CHN_MASK;
	// Chain the higher timer to the lower one.
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_CHN_MASK;
	
	// Disable interrupts
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TIE_MASK;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;

	/* Enable Interrupts */
	NVIC_SetPriority(PIT_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PIT_IRQn); 
	NVIC_EnableIRQ(PIT_IRQn);	
}


void Start_PIT(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void Stop_PIT(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}

void PIT_IRQHandler() {
	unsigned short out_data=0;
	
	//clear pending IRQ
	NVIC_ClearPendingIRQ(PIT_IRQn);
	
	// check to see which channel triggered interrupt 
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		// clear status flag for timer channel 0
		PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
		
		// TODO handle this case. Need to send a ping against the wheel.
		// This should occur 5000 times every second.	
		
	} else if (PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK) {
		// clear status flag for timer channel 1
		PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
		// One week has passed without a rotation occurring.
		// Indicates a bug has likely occurred.
		
		// TODO how do we want to handle this case?
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
