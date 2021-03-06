/*
 * main.c
 *
 *  Created on: Jan 15, 2022
 *      Author:  Alhassan Mohsen
 */



#include "../LIB/Typedef.h"
#include "../LIB/BIT_Math.h"
#include "../MCAL/DELAY/DELAY_interface.h"
#include "../ECUAL/LED/LED.h"

int main()
{
	LED_t st_TestLed = {PORTA,PIN4};
	LED_u8Init(st_TestLed);

	while (1)
	{
		LED_u8On(st_TestLed);
		DELAY_ms(300);
		LED_u8Off(st_TestLed);
		DELAY_ms(500);
	}

	return 0 ;
}
