/*
 * main.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Alhassan Mohsen
 */


#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/UART/UART_interface.h"

#define UART_BAUDRATE	9600
#define DATA_LENGTH	255
int main(void)
{
	uint8_t Data[DATA_LENGTH];
	
	SPI_u8Init(SPI_MASTER;
	UART_u8Init(UART_BAUDRATE);
	
	while(1)
	{
		UART_u8RecieveString(Data);
		SPI_u8SendString(Data);

	}
}
