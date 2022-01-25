/*
 * UART_interface.h
 *
 *  Created on: Jan 24, 2022
 *      Author: vip
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#include "../../LIB/BIT_Math.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/Typedef.h"


typedef enum {
	UART_OK=1,
	WRONG_OPERATION_MODE_CFG,
	WRONG_CHARACTER_SIZE_CFG,
	WRONG_PARITY_CFG,
	WRONG_STOP_BITS_CFG,
	WRONG_BAUD_RATE,
	UART_NULL_INPUT
}UARTErrorState_t;

uint8_t UART_u8Init(uint32_t UART_u32BaudRate);
uint8_t UART_u8SendByte(uint8_t u8Data);
uint8_t UART_u8RecieveByte(uint8_t* pu8RecievedData);
uint8_t UART_u8EnableRecievingInterrupt(void (*pfnCallBack)(void));
uint8_t UART_u8EnableSendingInterrupt(void (*pfnCallBack)(void));
uint8_t UART_u8DisableRecievingInterrupt(void);
uint8_t UART_u8DisableSendingInterrupt(void);
uint8_t UART_u8Deinit(void);


#endif /* MCAL_UART_UART_INTERFACE_H_ */