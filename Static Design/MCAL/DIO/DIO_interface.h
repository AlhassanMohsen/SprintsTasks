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

#define DIO_HIGH		1
#define DIO_LOW			0
#define DIO_PORT_HIGH 0xFF
#define DIO_PORT_LOW  0x00


#if BUILD_TARGET == ATMEGA32

#define DIO_PINS_NUMBER		8
#define DIO_PORTS_NUMBER	4

typedef enum{
	PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7
}DIOPin_t;

typedef enum{
	PORTA,PORTB,PORTC,PORTD
}DIOPort_t;

typedef enum{
	DIO_INPUT,DIO_INPUT_PULLUP,DIO_OUTPUT
}DIODir_t;

#endif

uint8_t DIO_u8SetPinDirection (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,DIODir_t u8_PinDir);
uint8_t DIO_u8SetPinData     (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,DIODir_t u8_PinData);
uint8_t DIO_u8GetPinData     (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,uint8_t* pu8_ReturnVar);
uint8_t DIO_u8SetPortDirection(DIOPort_t u8_PortName,DIODir_t u8_Dir);
uint8_t DIO_u8SetPortData    (DIOPort_t u8_PortName,DIODir_t u8_Data);
uint8_t DIO_u8GetPortData    (DIOPort_t u8_PortName,uint8_t* pu8_ReturnVar);
uint8_t DIO_u8TogglePinData  (DIOPort_t u8_PortName,DIOPin_t u8_PinNum);



#endif /* MCAL_DIO_INTERFACE_H_ */
