/*
 * main.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Alhassan Mohsen
 */


#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/UART/UART_interface.h"


int main(void)
{
	uint8_t Data[254];
	SPI_u8Init(SPI_SLAVE);
	UART_u8Init(9600);

	while(1)
	{
		SPI_u8ReceiveString(Data);
		UART_u8SendString(Data);
		UART_u8SendByte(0x0D);
	}
}
