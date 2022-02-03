#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>
#include "queue.h"

#define UART_BAUDRATE 300

typedef struct 
{
	size_t bytes_per_data;
	volatile Q_T TxQ;
	volatile Q_T RxQ;
} uart_transceiver_t;

volatile extern uart_transceiver_t uart1_transceiver;
volatile extern uart_transceiver_t uart2_transceiver;

#define UART_OVERSAMPLE (16)
#define BUS_CLOCK 			(24e6)

//uart_transeiver_t Init_UART1(uint32_t baud_rate, size_t data_bytes);
//uart_transeiver_t Init_UART2(uint32_t baud_rate, size_t data_bytes);

void Init_UART1(uint32_t baud_rate, size_t data_bytes, uart_transceiver_t *transceiver);
void Init_UART2(uint32_t baud_rate, size_t data_bytes, uart_transceiver_t *transceiver);

// poling
void UART1_Transmit_Poll(uint8_t data);
void UART2_Transmit_Poll(uint8_t data);

uint8_t UART1_Receive_Poll(void);
uint8_t UART2_Receive_Poll(void);

// interrupts
void send_data(uart_transceiver_t *transeiver, void* data);
uint32_t Get_Num_Rx_Chars_Available(void);
uint32_t get_data(uart_transceiver_t* transeiver);

extern Q_T TxQ, RxQ;
extern uint8_t CR_received;

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
