/*
 * main.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */



#include "../MCAL/UART/UART_interface.h"
#include "../ECUAL/LED/LED.h"
#include "../Service/Strings/STR.h"

int main(void)
{
	uint8_t u8CommandReceived[10];
	LED_t LEDGreen={PORTA,PIN6};
	LED_t LEDYellow={PORTA,PIN3};
	LED_t LEDRed={PORTA,PIN0};

	LED_u8Init(&LEDGreen);
	LED_u8Init(&LEDYellow);
	LED_u8Init(&LEDRed);
	UART_u8Init(9600);


	while (1)
	{

		UART_u8RecieveString(u8CommandReceived);

		if (STR_CMP(u8CommandReceived,(uint8_t*)"START"))
		{
			LED_u8On(&LEDGreen);
			LED_u8Off(&LEDRed);
			LED_u8Off(&LEDYellow);
			UART_u8SendString((uint8_t*)"Green LED is on\r\n");
		}else if (STR_CMP(u8CommandReceived,(uint8_t*)"WAIT"))
		{
			LED_u8Off(&LEDGreen);
			LED_u8Off(&LEDRed);
			LED_u8On(&LEDYellow);
			UART_u8SendString((uint8_t*)"Yellow LED is on\r\n");
		}else if(STR_CMP(u8CommandReceived,(uint8_t*)"STOP"))
		{
			LED_u8Off(&LEDGreen);
			LED_u8On(&LEDRed);
			LED_u8Off(&LEDYellow);
			UART_u8SendString((uint8_t*)"RED LED is on\r\n");
		}else
		{
			UART_u8SendString((uint8_t*)"Wrong Input\r\n");
		}
	}
}


