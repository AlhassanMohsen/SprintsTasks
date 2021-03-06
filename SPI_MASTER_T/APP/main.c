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
	uint8_t Data[255];
	uint8_t AllowedCount=255;
	uint8_t Flush[100];


	SPI_u8Init(SPI_MASTER);
	UART_u8Init(9600);

	while(1)
	{
		UART_u8ReceiveCountedString(Data,&AllowedCount);
		if (AllowedCount>0)
		{
			SPI_u8SendString(Data);
		}else
		{
			UART_u8SendByte(0x0D);
			UART_u8SendString((uint8_t*) "Maximum Length Exceeded\r\n");
			//UART_u8RecieveString(Flush);
			AllowedCount=255;
		}

	}
}
