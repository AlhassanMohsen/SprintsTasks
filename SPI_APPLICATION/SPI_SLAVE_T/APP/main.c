/*
 * main.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Alhassan Mohsen
 */


#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/UART/UART_interface.h"
#define DATA_LENGTH	254
#define UART_BAUDRATE	9600

int main(void)
{
	uint8_t Data[DATA_LENGTH];
	SPI_u8Init(SPI_SLAVE);
	UART_u8Init(UART_BAUDRATE);

	while(1)
	{
		SPI_u8ReceiveString(Data);
		UART_u8SendString(Data);
	}
}
