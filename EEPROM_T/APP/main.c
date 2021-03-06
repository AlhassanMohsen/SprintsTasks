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
	uint32_t u32Num;
	EEPROM_Init();
	EEPROM_u8WriteIntTo(0,0x0001,1000000000);
	TIMER0_u8PollingDelay(30);
	EEPROM_u8ReadIntFrom(0,0x0001,&u32Num);
	UART_u8Init(9600);
	UART_u8SendInt(u32Num);
	while (1)
	{

		LED_u8On(&LEDT);
	}
}


