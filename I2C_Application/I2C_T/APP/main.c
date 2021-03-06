/*
 * main.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */



#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../ECUAL/LED/LED.h"

int main(void)
{
	LED_t LEDT={PORTA,PIN7};
	LED_u8Init(&LEDT);
	/*///////////////////////////////////////*
	 //////////// Master Application //////*
	 *////////////////////////////////////*
	uint8_t u8ReceivedByte;
	I2C_u8Init();
	UART_u8Init(9600);
	while (1)
	{
		UART_u8ReceiveByte(&u8ReceivedByte);
		I2C_u8MasterSendByte(0x02,u8ReceivedByte);
		I2C_u8Stop();
		LED_u8On(&LEDT);
	}
}


