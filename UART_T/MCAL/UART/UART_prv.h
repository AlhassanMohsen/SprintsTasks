/*
 * UART_prv.h
 *
 *  Created on: Jan 24, 2022
 *      Author: vip
 */

#ifndef MCAL_UART_UART_PRV_H_
#define MCAL_UART_UART_PRV_H_

/**
 * Define the Possible modes of the UART peripherals
 */
#define UART_ASYNC_NORMAL_SPEED 0
#define UART_ASYNC_DOUBLE_SPEED 1
#define UART_SYNC_MODE			2

/**
 * Define the Possible Options for the UART_CHARACTER_SIZE configuration
 */
#define UART_9_BIT_CHARACTER	0
#define UART_8_BIT_CHARACTER	1
#define UART_7_BIT_CHARACTER	2
#define UART_6_BIT_CHARACTER	3
#define UART_5_BIT_CHARACTER	4


/**
 * Define the Possible Options for the UART_PARITY_MODE configuration
 */
#define UART_DISABLE_PARITY		0
#define UART_EVEN_PARITY		2
#define UART_ODD_PARITY			3

/**
 * Define the Possible Options for the UART_1_STOP_BIT configuration
 */
#define UART_1_STOP_BIT			0
#define UART_2_STOP_BIT			0


/**
 * Define the Possible States of the UART peripheral
 */
#define UART_NOT_INTIALIZED		0
#define UART_INITIALIZED		1


void __vector_13(void) __attribute__ ((signal, used));
void __vector_14(void) __attribute__ ((signal, used));
void __vector_15(void) __attribute__ ((signal, used));


#endif /* MCAL_UART_UART_PRV_H_ */
