/*
 * main.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */



#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/UART/UART_interface.h"

#define UART_BAUDRATE		9600

int main(void)
{

	uint8_t u8ReceivedByte;
	I2C_u8Init();
	UART_u8Init(UART_BAUDRATE);
	while (1)
	{
		I2C_u8SlaveGetByte(&u8ReceivedByte);
		UART_u8SendByte(u8ReceivedByte);
	}
}


