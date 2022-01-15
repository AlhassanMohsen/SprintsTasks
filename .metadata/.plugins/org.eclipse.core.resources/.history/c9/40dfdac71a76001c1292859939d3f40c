/*
 * Button.c
 *
 * Created: 1/10/2022 12:13:12 AM
 *  Author: Abdelrhman Elsawy
 */ 


#include "Button.h"

uint8_t BTN_u8Init ( BTN_t button )
{
	return DIO_u8SetPinDirection(button.port,button.pin,DIO_INPUT);
}

uint8_t BTN_u8IsPressed ( BTN_t button , uint8_t * pressed )
{	
	uint8_t u8ErrorState = STD_TYPES_OK;
	uint8_t u8DebounceDetectorHigh =0 , u8DebounceDetectorLow=0, u8BTNState;
	if (pressed!= NULL)
	{
		DIO_u8GetPinData(button.port,button.pin,&u8BTNState );
		if (u8BTNState == STD_TYPES_NOK)
		{
			u8ErrorState = STD_TYPES_NOK;
		}else
		{
			while (1)
			{
				DIO_u8GetPinData(button.port,button.pin,&u8BTNState );
				if (u8BTNState==DIO_HIGH)
				{
					u8DebounceDetectorHigh++;
					u8DebounceDetectorLow=0;
					u8BTNState = BTN_PRESSED;

				}else if (u8BTNState==DIO_LOW)
				{
					u8DebounceDetectorHigh=0;
					u8DebounceDetectorLow++;
					u8BTNState = BTN_NOT_PRESSED;
				}

				if (u8DebounceDetectorHigh==5 || u8DebounceDetectorLow ==5)
				{
					*pressed = u8BTNState;
					break;
				}
			}
		}
	}else
		{
		u8ErrorState = STD_TYPES_NOK;
		}

	return u8ErrorState;
}
