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
	 //////////// Slave Application //////*
	 *////////////////////////////////////*
	uint8_t u8ReceivedByte;
	I2C_u8Init();
	UART_u8Init(9600);
	while (1)
	{
		I2C_u8SlaveGetByte(&u8ReceivedByte);
		LED_u8On(&LEDT);
		UART_u8SendByte(u8ReceivedByte);
	}
}


