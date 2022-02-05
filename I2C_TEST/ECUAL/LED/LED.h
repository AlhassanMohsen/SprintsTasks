/*
 *  Led.h
 *
 *  Created: 1/10/2022 12:24:12 AM
 *  Author: Binary Beasts 
 */

#ifndef LED_H_
#define LED_H_

#include "../../LIB/Typedef.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/DIO/DIO_interface.h"

// struct to Configure LED connection  
typedef struct {
	uint8_t port;
	uint8_t pin;
} LED_t;

// function to initialize LED 
uint8_t LED_u8Init(LED_t* led);

// function ta turn LED on
uint8_t LED_u8On(LED_t* led);

// function to turn LED off
uint8_t LED_u8Off(LED_t* led);

// function to toggle LED state
uint8_t LED_u8Toggle(LED_t* led);

#endif /* LED_H_ */
