/*
 * UARTConfig.h
 *
 *  Created on: Jan 24, 2022
 *      Author: vip
 */

#ifndef MCAL_UART_UARTCONFIG_H_
#define MCAL_UART_UARTCONFIG_H_


/**
 * Configure the operation mode of the UART to one of the following modes:
 * 		-UART_ASYNC_NORMAL_SPEED  : Asynchronous with the divisor of the baud rate set to 16
 * 		-UART_ASYNC_DOUBLE_SPEED  :	Asynchronous with the divisor of the baud rate set to 8 effectively doubling the transfer rate
 * 		-UART_SYNC_MODE			  :
 */
#define UART_OPERATION_MODE	UART_ASYNC_NORMAL_SPEED

/**
 * Configure the number of data bits in the UART frame to one of the following options:
 * 		-UART_9_BIT_CHARACTER
 * 		-UART_8_BIT_CHARACTER
 * 		-UART_7_BIT_CHARACTER
 * 		-UART_6_BIT_CHARACTER
 * 		-UART_5_BIT_CHARACTER
 */
#define UART_CHARACTER_SIZE		UART_8_BIT_CHARACTER

/**
 * Configure the number of stop bits in the UART frame to one of the following options:
 * 		-UART_1_STOP_BIT
 * 		-UART_2_STOP_BIT
 */
#define UART_STOP_BITS_NUMBER	UART_1_STOP_BIT



/**
 * Configure the mode of the parity check to :
 * 		-UART_PARITY_DISABLE
 * 		-UART_PARITY_ENABLE
 */
#define UART_PARITY_MODE		UART_PARITY_DISABLE

/**
 * Enter the Clock frequency of the micro-controller
 */
#define UART_F_CPU		8000000UL


#endif /* MCAL_UART_UARTCONFIG_H_ */
