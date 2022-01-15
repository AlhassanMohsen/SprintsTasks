/*
 * Led.c
 *
 * Created: 1/10/2022 12:27:19 AM
 *  Author: Binary Beasts
 */ 

#include "LED.h"

// function to initialize LED 
uint8_t LED_u8Init ( LED_t led )
{
	// set direction of LED's pin to OUTPUT 
	return DIO_u8SetPinDirection(led.port,led.pin,DIO_OUTPUT);
}

// function ta turn LED on
uint8_t LED_u8On ( LED_t led )
{
	// set LED's pin to HIGH 
	return DIO_u8SetPinData(led.port,led.pin,DIO_HIGH);
}

// function ta turn LED off
uint8_t LED_u8Off ( LED_t led )
{
	// set LED's pin to LOW
	return DIO_u8SetPinData(led.port,led.pin,DIO_LOW);
}

// function to toggle LED state
uint8_t LED_u8Toggle ( LED_t led )
{
	// toggle LED's pin state 
	return DIO_u8TogglePinData(led.port,led.pin);
}
