/*
 * main.c
 *
 *  Created on: Jan 24, 2022
 *      Author: vip
 */




#include "MCAL/UART/UART_interface.h"
#include "ECUAL/LED/LED.h"
LED_t LEDT = {PORTB,PIN7};
volatile uint8_t gu8_ATMMode=0;
void fn(void);
int main (void)
{
	LED_u8Init(&LEDT);
	uint8_t u8RecievedByte[100];

	UART_u8Init(9600);
	UART_u8EnableRecievingInterrupt(fn);
	while (1)
	{
		//LED_u8On(&LEDTest);
		//UART_u8RecieveString(u8RecievedByte);
		//LED_u8On(&LEDT);
		//UART_u8SendString(u8RecievedByte);
		//LED_u8Off(&LEDT);
		//UART_u8SendString("ADMIN");
		if (gu8_ATMMode==1)
		{
			UART_u8SendString("ADMIN \r");
			gu8_ATMMode=0;
		}else if(gu8_ATMMode==2)
		{
			UART_u8SendString("USER");
			gu8_ATMMode=0;
		}else{
			//UART_u8SendString("WRONG");
		}

	}
}

void fn(void)
{
	uint8_t au8TerminalCommand[10];
	UART_u8RecieveString(au8TerminalCommand);
	switch (au8TerminalCommand[0])
	{
	case 'A':
		gu8_ATMMode = 1;
		break;
	case 'U':
		gu8_ATMMode = 2;
		break;
	default:
		gu8_ATMMode =3;
	}
}
