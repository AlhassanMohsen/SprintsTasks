/*
 * main.c
 *
 *  Created on: Jan 15, 2022
 *      Author:  Alhassan Mohsen
 */



#include "../LIB/Typedef.h"
#include "../LIB/BIT_Math.h"
#include "../MCAL/DELAY/DELAY_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/I2C/I2C_interface.h"
int main()
{
	uint8_t u8ReceivedByte;
	DIO_u8SetPortDirection(PORTA,DIO_OUTPUT);
	I2C_u8Init();

	I2C_u8SlaveGetByte(&u8ReceivedByte);
	DIO_u8SetPortData(PORTA,u8ReceivedByte);


	while (1)
	{
	}

	return 0 ;
}
