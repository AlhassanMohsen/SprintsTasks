/*
 * Led.c
 *
 * Created: 1/10/2022 12:27:19 AM
 *  Author: Abdelrhman Elsawy
 */ 



#include "LED.h"

uint8_t LED_u8Init ( LED_t led )
{
	return DIO_u8SetPinDirection(led.port,led.pin,DIO_OUTPUT);
}

uint8_t LED_u8On ( LED_t led )
{
	return DIO_u8SetPinData(led.port,led.pin,DIO_HIGH);
}

uint8_t LED_u8Off ( LED_t led )
{
	return DIO_u8SetPinData(led.port,led.pin,DIO_LOW);
}


uint8_t LED_u8Toggle ( LED_t led )
{
	return DIO_u8TogglePinData(led.port,led.pin);
}
