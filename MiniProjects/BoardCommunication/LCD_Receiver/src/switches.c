#include <MKL25Z4.H>
#include "switches.h"
#include "gpio_defs.h"
#include "uart.h"

volatile extern unsigned send_button;
volatile extern unsigned send_button_update;

void Init_4way_Switch(void) {
  SIM->SCGC5 |=  SIM_SCGC5_PORTD_MASK; /* enable clock for port D */
	
  /* Select GPIO and enable pull-up resistors for pins connected to switches */
  PORTD->PCR[SW_0_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(10);	
  PORTD->PCR[SW_1_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(10);	
  PORTD->PCR[SW_2_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(10);	
  PORTD->PCR[SW_3_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(10);	
	
  /* Set port E bits 0-3, 7 to inputs */
  PTE->PDDR &= ~( MASK(SW_0_POS) | 
				  MASK(SW_1_POS) |
				  MASK(SW_2_POS) | 
				  MASK(SW_3_POS) );
	
	/* Enable Interrupts */
	NVIC_SetPriority(PORTD_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTD_IRQn); 
	NVIC_EnableIRQ(PORTD_IRQn);
}
void PORTD_IRQHandler(void) {  
	// clear pending interrupts
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	if ((PORTD->ISFR & MASK(SW_0_POS))) {
		send_button = 1;
		//Q_Enqueue(&uart1_transceiver.TxQ, 1);
	}
	if ((PORTD->ISFR & MASK(SW_1_POS))) {
		send_button = 2;
		//Q_Enqueue(&uart1_transceiver.TxQ, 1);
	}
	if ((PORTD->ISFR & MASK(SW_2_POS))) {
		send_button = 3;
		//Q_Enqueue(&uart1_transceiver.TxQ, 1);
	}
	if ((PORTD->ISFR & MASK(SW_3_POS))) {
		send_button = 4;
		//Q_Enqueue(&uart1_transceiver.TxQ, 1);
	}
	// clear status flags 
	PORTD->ISFR = 0xffffffff;
	send_button_update = 1;
}
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
