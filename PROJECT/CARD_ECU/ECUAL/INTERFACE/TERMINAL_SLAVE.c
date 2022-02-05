/*
 * TERMINAL_SLAVE.c
 *
 * Created: 1/28/2022 11:05:42 PM
 *  Author: Khaled Ali
 */ 
#include "TERMINAL_SLAVE.h"



uint8_t TERMINAL_u8Init(void){
	UART_u8Init(9600);
	return 1;
}

uint8_t TERMINAL_u8Interface(Card_t* card){

	UART_u8SendString((uint8_t*) "Enter Card Holder Name: \r\n");
	UART_u8ReceiveCountedString(card->NAME,9);
	UART_u8SendString((uint8_t*) "Enter Primary Account Number: \r\n");
	UART_u8ReceiveCountedString(card->PAN,9);
	UART_u8SendByte(0x0D);
	UART_u8SendString((uint8_t*) "Enter PIN: \r\n");
	UART_u8ReceiveCountedString(card->PIN,4);
	UART_u8SendByte(0x0D);
	return 1; //To be Changed
}

uint8_t TERMINAL_u8EnableInterrupt(void (*pfnCallBack)(void)){
	UART_u8EnableRecievingInterrupt(pfnCallBack);
	return 1;
}

uint8_t TERMINAL_u8DisableInterrupt(void){
	UART_u8DisableReceivingInterrupt();
	return 1;
}
