/*
 * KEYPAD_interface.h
 *
 *  Created on: Jan 11, 2022
 *      Author: Esraa
 */

#ifndef ECUAL_KEYPAD_KEYPAD_INTERFACE_H_
#define ECUAL_KEYPAD_KEYPAD_INTERFACE_H_

#include "../../LIB/Typedef.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/DIO/DIO_interface.h"

#define KEYPAD_NO_PRESSED_KEY  0xFF


//a function that initialize the keypad pins and get it ready to be used
uint8_t KEYPAD_u8Init(void);

// a function that get the pressed key on the keypad
uint8_t KEYPAD_u8GetPressedKey(uint8_t* KeyPressed);

#endif /* ECUAL_KEYPAD_KEYPAD_INTERFACE_H_ */
