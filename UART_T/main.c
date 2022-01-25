/*
 * main.c
 *
 *  Created on: Jan 24, 2022
 *      Author: vip
 */




#include "MCAL/UART/UART_interface.h"
#include "ECUAL/LED/LED.h"
LED_t LEDTest = {PORTB,PIN7};

void fn(void);
int main (void)
{
	LED_u8Init(&LEDTest);
	uint8_t u8RecievedByte;
	UART_u8Init(9600);
	UART_u8EnableSendingInterrupt(fn);
	while (1)
	{
		LED_u8On(&LEDTest);
		UART_u8RecieveByte(&u8RecievedByte);
		UART_u8SendByte(u8RecievedByte);
	}
}

void fn(void)
{
	LED_u8Off(&LEDTest);
}