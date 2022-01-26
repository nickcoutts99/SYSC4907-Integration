#include "timers.h"

volatile unsigned PIT_IR_sample_count = 0;
volatile unsigned IR_brightness = 0;
volatile unsigned n_IR_samples = 0;
volatile unsigned IR_led_state = 0;
volatile unsigned IR_diff = 0;

void Init_PIT(unsigned period_us)
{
	// Enable clock to PIT module
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

	// Enable module, freeze timers in debug mode
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_FRZ_MASK;

	// Initialize PIT0 to count down from argument
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(period_us * 24); // 24 MHz clock frequency

	// No chaining
	PIT->CHANNEL[0].TCTRL &= PIT_TCTRL_CHN_MASK;

	// Generate interrupts
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

	/* Enable Interrupts */
	NVIC_SetPriority(PIT_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);
}

void Start_PIT(void)
{
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void Stop_PIT(void)
{
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}

void PIT_IRQHandler(void)
{
	// unsigned short out_data = 0;

	// clear pending IRQ
	NVIC_ClearPendingIRQ(PIT_IRQn);

	// check to see which channel triggered interrupt
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
	{
		// clear status flag for timer channel 0
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;

		// Measure IR
		IR_brightness = (unsigned)Measure_IR();
		IR_diff = (2 * IR_led_state - 1) * IR_brightness; // adds on brightness and subtracts off brightness
		n_IR_samples++;
		IR_led_state ^= 1;
	}
	else if (PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK)
	{
		// clear status flag for timer channel 1
		PIT->CHANNEL[1].TFLG &= PIT_TFLG_TIF_MASK;
	}
}
