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
	u8ErrorState= DIO_u8SetPinDirection(button.port,button.pin,DIO_INPUT);
	return u8ErrorState;
}

uint8_t BTN_u8IsPressed ( BTN_t button , uint8_t * pressed )
{	
	uint8_t u8ErrorState = STD_TYPES_OK;
	uint8_t u8DebounceDetectorHigh =0 , u8DebounceDetectorLow=0, u8BTNState;
	if (pressed!= NULL)
	{
		DIO_u8GetPinData(button.port,button.pin,&u8BTNState );
		DELAY_ms(10);
	}else{
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}
