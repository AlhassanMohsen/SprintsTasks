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
#include "../ECUAL/BTN/Button.h"

#define PRESSED 	1
#define NOT_PRESSED 0


int main()
{
	uint8_t  u8KeyPressed;
	uint8_t u8PreviousKey=NOT_PRESSED;
	LED_t st_TestLed = {PORTB,PIN4};
	BTN_t st_TestBTN = {PORTB,PIN2};
	BTN_u8Init(st_TestBTN);
	LED_u8Init(st_TestLed);

	while (1)
	{
		BTN_u8IsPressed(st_TestBTN,&u8KeyPressed);
		if (u8KeyPressed == PRESSED && u8PreviousKey == NOT_PRESSED)
		{
			u8PreviousKey = PRESSED;
			LED_u8Toggle(st_TestLed);
		}else if (u8KeyPressed == NOT_PRESSED){
			u8PreviousKey = NOT_PRESSED;
		}else {
			//NOP
		}
	}

	return 0 ;
}
