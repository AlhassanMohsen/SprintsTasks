/*
 * main.c
 *
 *  Created on: Jan 22, 2022
 *      Author: vip
 */





#include "../LIB/BIT_Math.h"
#include "../LIB/Typedef.h"
#include "../ECUAL/KEYPAD/KEYPAD_interface.h"
#include "../ECUAL/LCD/LCD.h"
#include "../MCAL/DELAY/TIMER0.h"


int main (void)
{
	uint8_t u8KeyPressed;
	uint8_t u8LastKey=255;
	LCD_u8Init();
	KEYPAD_u8Init();
	TIMER0_u8Init();
	LCD_u8SendString("The KEY pressed is: ");
	LCD_u8SetCursor(1,0);
	while (1)
	{
		TIMER0_u8PollingDelay(300);
		LCD_u8SetCursor(1,0);
		LCD_u8SendString("           ");
		LCD_u8SetCursor(1,0);
		KEYPAD_u8GetPressedKey(&u8KeyPressed);
		if(u8KeyPressed!=255)
		{
			LCD_u8SendNumber(u8KeyPressed);
			u8LastKey = u8KeyPressed;
		}
		else
		{
			LCD_u8SendNumber(u8LastKey);
		}
	}
}
