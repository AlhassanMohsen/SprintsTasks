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
	uint8_t Data[100];
	SPI_u8Init(SPI_MASTER);
	UART_u8Init(9600);
	while(1)
	{
		UART_u8RecieveString(Data);
		SPI_u8SendString(Data);

	}
}
