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
	LED_t LEDT={PORTA,PIN7};
	LED_u8Init(&LEDT);
	/*///////////////////////////////////////*
	 //////////// EEPROM Application //////*
	 *////////////////////////////////////*
	uint8_t u8ReceivedByte[10];
	EEPROM_Init();
	EEPROM_u8WriteStringTo(0,0x0001,"Sprints");
	TIMER0_u8PollingDelay(30);
	EEPROM_u8ReadStringFrom(0,0x0001,&u8ReceivedByte);
	UART_u8Init(9600);
	while (1)
	{
		UART_u8SendString(u8ReceivedByte);
		LED_u8On(&LEDT);
	}
}


