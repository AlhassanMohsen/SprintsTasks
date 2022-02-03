/*
 * main.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */



#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../ECUAL/LED/LED.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/DELAY/TIMER0.h"
int main(void)
{
	uint32_t Test;
	ATM_Init();
	ATM_APP();
	UART_u8Init(9600);
	UART_u8ReceiveInt(&Test);
	UART_u8SendInt(Test);

	LED_t LEDT={PORTA,PIN7};
	LED_u8Init(&LEDT);
	/*///////////////////////////////////////*
	 //////////// EEPROM Application //////*
	 *////////////////////////////////////*
	uint32_t u32Num;

	UART_u8Init(9600);
	UART_u8ReceiveInt(&Test);
	UART_u8SendInt(Test);


	while (1)
	{

		LED_u8On(&LEDT);
	}

}

