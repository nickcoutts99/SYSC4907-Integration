#include "uart.h"
#include <stdint.h>


Q_T TxQ, RxQ;
uint8_t CR_received = 0;

/*
uart_transceiver_t Init_UART1(uint32_t baud_rate, size_t data_bytes) {
	uart_transceiver_t transceiver;
	uint32_t divisor;
	
	// enable clock to UART and Port E
	SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;


	// select UART pins
	PORTE->PCR[0] = PORT_PCR_MUX(3);
	PORTE->PCR[1] = PORT_PCR_MUX(3);
	
	UART1->C2 &=  ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
		
	// Set baud rate to baud rate
	divisor = (uint32_t)BUS_CLOCK/(baud_rate*16);
	UART1->BDH = UART_BDH_SBR(divisor>>8);
	UART1->BDL = UART_BDL_SBR(divisor);
	
	// No parity, 9 bits, two stop bits, other settings;
	UART1->C1 = UART_C1_M_MASK | UART_C1_PE_MASK | UART_C1_PT_MASK; 
	UART1->S2 = 0;
	UART1->C3 = 0;
	
// Enable transmitter and receiver but not interrupts
	UART1->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;

	transceiver.bytes_per_data = data_bytes;
	
	NVIC_SetPriority(UART1_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(UART1_IRQn); 
	NVIC_EnableIRQ(UART1_IRQn);

	UART1->C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK;

	Q_Init(&transceiver.TxQ);
	Q_Init(&transceiver.RxQ);
	
	return transceiver;
}

uart_transceiver_t Init_UART2(uint32_t baud_rate, size_t data_bytes) {
	uart_transceiver_t transceiver;
	uint32_t divisor;
	
	// enable clock to UART and Port E
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;


	// select UART pins
	PORTE->PCR[22] = PORT_PCR_MUX(3);
	PORTE->PCR[23] = PORT_PCR_MUX(3);
	
	UART2->C2 &=  ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
		
	// Set baud rate to baud rate
	divisor = (uint32_t)BUS_CLOCK/(baud_rate*16);
	UART2->BDH = UART_BDH_SBR(divisor>>8);
	UART2->BDL = UART_BDL_SBR(divisor);
	
	// No parity, 9 bits, two stop bits, other settings;
	UART2->C1 = UART_C1_M_MASK | UART_C1_PE_MASK | UART_C1_PT_MASK; 
	UART2->S2 = 0;
	UART2->C3 = 0;
	
	UART2->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;

	transceiver.bytes_per_data = data_bytes;
	
	NVIC_SetPriority(UART2_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(UART2_IRQn); 
	NVIC_EnableIRQ(UART2_IRQn);

	UART2->C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK;

	Q_Init(&transceiver.TxQ);
	Q_Init(&transceiver.RxQ);

	return transceiver;
}
*/

void Init_UART1(uint32_t baud_rate, size_t data_bytes, uart_transceiver_t *transceiver) {
	uint32_t divisor;
	
	// enable clock to UART and Port E
	SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;


	// select UART pins
	PORTE->PCR[0] = PORT_PCR_MUX(3);
	PORTE->PCR[1] = PORT_PCR_MUX(3);
	
	UART1->C2 &=  ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
		
	// Set baud rate to baud rate
	divisor = (uint32_t)BUS_CLOCK/(baud_rate*16);
	UART1->BDH = UART_BDH_SBR(divisor>>8);
	UART1->BDL = UART_BDL_SBR(divisor);
	
	// No parity, 9 bits, two stop bits, other settings;
	UART1->C1 = UART_C1_M_MASK | UART_C1_PE_MASK | UART_C1_PT_MASK; 
	UART1->S2 = 0;
	UART1->C3 = 0;
	
// Enable transmitter and receiver but not interrupts
	UART1->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;

	transceiver->bytes_per_data = data_bytes;
	
	NVIC_SetPriority(UART1_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(UART1_IRQn); 
	NVIC_EnableIRQ(UART1_IRQn);

	UART1->C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK;

	transceiver->bytes_per_data = data_bytes;

	Q_Init(&transceiver->TxQ);
	Q_Init(&transceiver->RxQ);
}

void Init_UART2(uint32_t baud_rate, size_t data_bytes, uart_transceiver_t *transceiver) {
	uint32_t divisor;
	
	// enable clock to UART and Port E
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;


	// select UART pins
	PORTE->PCR[22] = PORT_PCR_MUX(3);
	PORTE->PCR[23] = PORT_PCR_MUX(3);
	
	UART2->C2 &=  ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
		
	// Set baud rate to baud rate
	divisor = (uint32_t)BUS_CLOCK/(baud_rate*16);
	UART2->BDH = UART_BDH_SBR(divisor>>8);
	UART2->BDL = UART_BDL_SBR(divisor);
	
	// No parity, 9 bits, two stop bits, other settings;
	UART2->C1 = UART_C1_M_MASK | UART_C1_PE_MASK | UART_C1_PT_MASK; 
	UART2->S2 = 0;
	UART2->C3 = 0;
	
	UART2->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;

	transceiver->bytes_per_data = data_bytes;
	
	NVIC_SetPriority(UART2_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(UART2_IRQn); 
	NVIC_EnableIRQ(UART2_IRQn);

	UART2->C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK;

	transceiver->bytes_per_data = data_bytes;

	Q_Init(&transceiver->TxQ);
	Q_Init(&transceiver->RxQ);

}

void UART1_Transmit_Poll(uint8_t data) {
		while (!(UART1->S1 & UART_S1_TDRE_MASK))
			;
		UART1->D = data;
}	

uint8_t UART1_Receive_Poll(void) {
		while (!(UART1->S1 & UART_S1_RDRF_MASK))
			;
		return UART1->D;
}	

void UART2_Transmit_Poll(uint8_t data) {
		while (!(UART1->S1 & UART_S1_TDRE_MASK))
			;
		UART1->D = data;
}	

uint8_t UART2_Receive_Poll(void) {
		while (!(UART1->S1 & UART_S1_RDRF_MASK))
			;
		return UART1->D;
}	

void UART1_IRQHandler(void) {
	uint8_t c;
	NVIC_ClearPendingIRQ(UART1_IRQn);
	if (UART1->S1 & UART_S1_TDRE_MASK) {
		// can send another character
		if (!Q_Empty(&uart1_transceiver.TxQ)) {
			UART1->D = Q_Dequeue(&uart1_transceiver.TxQ);
		} else {
			// queue is empty so disable transmitter
			UART1->C2 &= ~UART_C2_TIE_MASK;
		}
	}
	if (UART1->S1 & UART_S1_RDRF_MASK) {
		// received a character
		if (!Q_Full(&uart1_transceiver.RxQ)) {
			c = UART1->D;
			Q_Enqueue(&uart1_transceiver.RxQ, c);
			if (c == '\r') {
				CR_received++;
			}
		} else {
			// error - queue full.
			while (1)
				;
		}
	}
	if (UART1->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | 
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// handle the error
			// clear the flag
			/*
			UART1->S1 = UART_S1_OR_MASK | UART_S1_NF_MASK | 
				UART_S1_FE_MASK | UART_S1_PF_MASK;
		 */
		}
}

void UART2_IRQHandler(void) {
	uint8_t c;
	NVIC_ClearPendingIRQ(UART2_IRQn);
	if (UART2->S1 & UART_S1_TDRE_MASK) {
		// can send another character
		if (!Q_Empty(&uart2_transceiver.TxQ)) {
			UART2->D = Q_Dequeue(&uart2_transceiver.TxQ);
		} else {
			// queue is empty so disable transmitter
			UART2->C2 &= ~UART_C2_TIE_MASK;
		}
	}
	if (UART2->S1 & UART_S1_RDRF_MASK) {
		// received a character
		if (!Q_Full(&uart2_transceiver.RxQ)) {
			c = UART2->D;
			Q_Enqueue(&uart2_transceiver.RxQ, c);
			if (c == '\r') {
				CR_received++;
			}
		} else {
			// error - queue full.
			while (1)
				;
		}
	}
	if (UART2->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | 
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// handle the error
			// clear the flag
			/*
			UART2->S1 = UART_S1_OR_MASK | UART_S1_NF_MASK | 
				UART_S1_FE_MASK | UART_S1_PF_MASK;
		 */
		}
}

/*
 * Replacement for send_sting data. Used to send at most 32 bits (4 bytes) of data.
 *
 * args:
 * 	*data ---- void pointer to the data you want to send. 
 * 	                Allows any data type to be passed into the function. 
 * 	*transceiver  ---- structure containing the number of bytes to send/receive and tx/rx queues.
 */
void send_data(uart_transceiver_t *transceiver, void* data)
{
	uint32_t transmit_data = *(uint32_t*) data;
	
	// send n_bytes
	for (int byte_idx = (int)transceiver->bytes_per_data - 1; byte_idx >= 0; byte_idx--)
	{
		// Wait while Queue is full.
		while(Q_Full(&transceiver->TxQ));

		Q_Enqueue(&transceiver->TxQ, (uint8_t)(transmit_data >> 8*byte_idx));
	}

	// Start transmitter if it isn't already running
	if (!(UART1->C2 & UART_C2_TIE_MASK)) {
		UART1->C2 |= UART_C2_TIE_MASK;
	}
}

uint32_t Get_Num_Rx_Chars_Available(void) {
	return Q_Size(&RxQ);
}

uint32_t get_data(uart_transceiver_t* transceiver)
{
	uint32_t received_data = 0;

	for (int byte_idx = (int)transceiver->bytes_per_data - 1; byte_idx >= 0; byte_idx++)
	{
		// Wait while Queue is empty.
		while (Q_Empty(&transceiver->RxQ));

		// Retreive databytes from the queue
		uint8_t byte = Q_Dequeue(&transceiver->RxQ);
		received_data |= (uint32_t)(byte << 8 * byte_idx);
	}

	return received_data;
}
