/*
 * Button.c
 *
 * Created: 1/10/2022
 *  Author: Alhassan Mohsen
 */ 


#include "Button.h"

uint8_t BTN_u8Init ( BTN_t button )
{
	uint8_t u8ErrorState = STD_TYPES_OK;
	u8ErrorState= DIO_u8SetPinDirection(button.port,button.pin,DIO_INPUT_PULLUP);
	return u8ErrorState;
}

uint8_t BTN_u8IsPressed ( BTN_t button , uint8_t * pressed )
{	
	uint8_t u8BTNState;
	uint8_t u8ErrorState = STD_TYPES_OK;
	if (pressed!= NULL)
	{
		DIO_u8GetPinData(button.port,button.pin,&u8BTNState);
		if (u8BTNState == DIO_HIGH)
		{
			TIMER0_u8PollingDelay(15);
			DIO_u8GetPinData(button.port,button.pin,&u8BTNState);
			if (u8BTNState == DIO_HIGH)
			{
				*pressed = u8BTNState;
			}else
			{
				*pressed = DIO_LOW;
			}
		}else{
			*pressed = u8BTNState;
		}
		//
	}else{
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}
