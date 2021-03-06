/*
 * main.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */



#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/UART/UART_interface.h"

#define SLAVE_ADDRESS		0x02
#define NEW_LINE_CHAR		0x0D
#define UART_BAUDRATE		9600

int main(void)
{
	uint8_t u8ReceivedByte;
	I2C_u8Init();
	UART_u8Init(UART_BAUDRATE);

	UART_u8ReceiveByte(&u8ReceivedByte);

	I2C_u8MasterSendStart();
	I2C_u8MasterSendSLA(SLAVE_ADDRESS,I2C_MASTER_WRITE);
	I2C_u8MasterSendByte(u8ReceivedByte);
	I2C_u8Stop();

	while (1)
	{
	}
}


