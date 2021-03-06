/*
 * main.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */



#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/DIO/DIO_interface.h"

#define UART_BAUDRATE		9600

int main(void)
{

	uint8_t u8ReceivedByte;
	DIO_u8SetPortDirection(PORTA,DIO_OUTPUT);
	I2C_u8Init();
	UART_u8Init(UART_BAUDRATE);
	while (1)
	{
		I2C_u8SlaveGetByte(&u8ReceivedByte);
		DIO_u8SetPortData(PORTA,0xFF);
		UART_u8SendByte(u8ReceivedByte);
	}
}


