/*
 * DIO.h
 *
 *  Created on: Jan 8, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef MCAL_DIO_INTERFACE_H_
#define MCAL_DIO_INTERFACE_H_
#ifndef BUILD_TARGET
#define BUILD_TARGET	ATMEGA32
#endif

#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/atmega32.h"

#define DIO_HIGH		1
#define DIO_LOW			0
#define DIO_PORT_HIGH 0xFF
#define DIO_PORT_LOW  0x00


#if BUILD_TARGET == ATMEGA32

#define DIO_PINS_NUMBER		8
#define DIO_PORTS_NUMBER	4

/**
 * @enum DIOPin_t
 * Defines the allowed values to PINS inputs
 */
typedef enum{
	PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7
}DIOPin_t;

/**
 * @enum DIOPort_t
 * Defines the allowed values to Ports inputs
 */
typedef enum{
	PORTA,PORTB,PORTC,PORTD
}DIOPort_t;

/**
 * @enum DIODir_t
 * Defines the allowed values for Direction
 */
typedef enum{
	DIO_INPUT,DIO_INPUT_PULLUP,DIO_OUTPUT
}DIODir_t;

/**
 * @enum
 * Defines the Possible Error States in the DIO Driver
 */
typedef enum{
	DIO_OK=1,       //!< DIO_OK
	WRONG_VALUE=251,//!< WRONG_VALUE
	NULL_PTR,       //!< NULL_PTR
	WRONG_DIR,      //!< WRONG_DIR
	WRONG_PORT,     //!< WRONG_PORT
	WRONG_PIN       //!< WRONG_PIN
}DIO_ErrorState_t;

#endif

// function to set direction of pin 
DIO_ErrorState_t DIO_u8SetPinDirection (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,DIODir_t u8_PinDir);

// function to assign value to pin 
DIO_ErrorState_t DIO_u8SetPinData (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,uint8_t u8_PinData);

// function to read value on pin 
DIO_ErrorState_t DIO_u8GetPinData (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,uint8_t* pu8_ReturnVar);

// function to set direction of port
DIO_ErrorState_t DIO_u8SetPortDirection(DIOPort_t u8_PortName,DIODir_t u8_Dir);

// function to assign value to port
DIO_ErrorState_t DIO_u8SetPortData (DIOPort_t u8_PortName,uint8_t u8_Data);

// function to read value on port
DIO_ErrorState_t DIO_u8GetPortData (DIOPort_t u8_PortName,uint8_t* pu8_ReturnVar);

// function to toggle pin state 
DIO_ErrorState_t DIO_u8TogglePinData (DIOPort_t u8_PortName,DIOPin_t u8_PinNum);



#endif /* MCAL_DIO_INTERFACE_H_ */
