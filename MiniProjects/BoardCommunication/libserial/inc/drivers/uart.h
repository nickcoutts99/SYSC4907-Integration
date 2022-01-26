#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>
#include "queue.h"

// TODO preset baudrates
#define UART_BAUDRATE_300    300
#define UART_BAUDRATE_9600   9600
#define UART_BAUDRATE_115200 115200

/* A data structure to contain the configurations
 * for each UART port.
 */
typedef struct
{
	SIM_Type* sim;
	uint32_t uartSCGCMask;
	UART_Type* uartPort;
	
	uint32_t pinSCGCMask;
	PORT_Type* gpioPort;
	//uint32_t  pcrMux;
	
	//uint32_t txPin;
	//uint32_t rxPin;
	
	unsigned nvic_irq;
} uart_cfg_t;

typedef struct
{
	uint32_t uartSCGCMask;
	UART_Type* uartPort;
	
	uint32_t pinSCGCMask;
	PORT_Type* gpioPort;
	uint32_t  pcrMux;
	
	uint32_t txPin;
	uint32_t rxPin;
	
	unsigned nvic_irq;
} uart_cfg2_t;

/* Predefined transmit and receive queue for
 * the UART ports.
 */
extern Q_T uart1_txQ;
extern Q_T uart1_rxQ;
extern Q_T uart2_txQ;
extern Q_T uart2_rxQ;

/* Predefined configurations for
 * the UART ports.
 * 
 * If you need to change the default settings
 * edit the corresponding structure in the
 * source file and recompile.
 */
extern uart_cfg_t uart1_cfg;
extern uart_cfg_t uart2_cfg;

/* Macros for controlling the UART ports.
 * 
 * These are wrappers for the general set of functions.
 * Use these for a simplified interface for interacting 
 * with the UART devices
 */
#define UART1_INIT(baud_rate, nvic_priority) __uart_init (&uart1_cfg, &uart1_txQ, &uart1_rxQ, baud_rate, nvic_priority)
#define UART1_START()                        __uart_start(&uart1_cfg)
#define UART1_STOP()                         __uart_start(&uart1_cfg)
#define UART1_SEND(msg)                      __uart_send (&uart1_txQ, msg)
// NOTE the msg in the read macro is a char array and is passed by referance.
#define UART1_READ(msg)                      __uart_recv (&uart1_rxQ, msg)

#define UART2_INIT(baud_rate, nvic_priority) __uart_init(&uart2_cfg, &uart2_txQ, &uart2_rxQ, baud_rate, nvic_priority)
#define UART2_START()                        __uart_start(&uart1_cfg)
#define UART2_STOP()                         __uart_start(&uart2_cfg)
#define UART2_SEND(msg)                      __uart_send (&uart2_txQ, msg)
// NOTE the msg in the read macro is a char array and is passed by referance.
#define UART2_READ(msg)                      __uart_recv (&uart2_rxQ, msg)

/* Gerneral functions for interacting with the UART ports.
 * 
 * Only use these if you wish to have more control over the port.
 */
void __uart_init(uart_cfg_t* p_cfg, Q_T* p_tx_q, Q_T* p_rx_q, uint32_t baud_rate, uint32_t priority);
void __uart_start(uart_cfg_t* p_cfg);
void __uart_stop(uart_cfg_t* p_cfg);
void __uart_send(Q_T* p_tx_q, char* send_msg);
void __uart_read(Q_T* p_rx_q, char* received_msg);

#endif
