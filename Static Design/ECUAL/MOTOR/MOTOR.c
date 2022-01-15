/*
 * MOTOR.c
 *
 *  Created on: Jan 11, 2022
 *      Author: Esraa
 */

#include "MOTOR_interface.h"


uint8_t MOTOR_init(MotorDef_t* MotorElement)
{
	uint8_t u8ErrorState = STD_TYPES_OK;
	PWMPin_t MotorDef = {MotorElement->port, MotorElement->ENPin};
	u8ErrorState= DIO_u8SetPinDirection(MotorElement->port,MotorElement->DirPinA,DIO_OUTPUT);
	if (u8ErrorState==STD_TYPES_OK)
	{
		u8ErrorState= DIO_u8SetPinDirection(MotorElement->port,MotorElement->DirPinB,DIO_OUTPUT);
	}
	if (u8ErrorState==STD_TYPES_OK)
	{
		u8ErrorState=DIO_u8SetPinDirection(MotorElement->port,MotorElement->ENPin,DIO_OUTPUT);
	}

	PWM_u8Init(MotorElement->ChannelNum, &MotorDef);
	return u8ErrorState;
}
uint8_t MOTOR_Move(MotorDef_t* MotorElement,uint8_t MotorSpeed,uint8_t MotorDir)
{
	uint8_t u8ErrorState = STD_TYPES_OK;

	if (MotorElement!=NULL && MotorSpeed > 0 && MotorSpeed <100)
	{
		switch (MotorDir)
		{
		case CLOCKWISE:
			DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinA, DIO_HIGH);
			DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinB, DIO_LOW);
			PWM_u8DutyCycle(MotorElement->ChannelNum,MotorSpeed);
			break;
		case ANTI_CLOCKWISE:
			DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinA, DIO_LOW);
			DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinB, DIO_HIGH);
			PWM_u8DutyCycle(MotorElement->ChannelNum,MotorSpeed);
			break;
		default:
			u8ErrorState = STD_TYPES_NOK;
			break;
		}

	}else{
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}

uint8_t MOTOR_Stop(MotorDef_t* MotorElement)
{
	uint8_t u8ErrorState = STD_TYPES_OK;
	if (MotorElement!=NULL)
	{
		DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinA, DIO_LOW);
		DIO_u8SetPinData(MotorElement->port , MotorElement->DirPinB, DIO_LOW);
	}else{
		u8ErrorState = STD_TYPES_NOK;
	}

	return u8ErrorState;
}
