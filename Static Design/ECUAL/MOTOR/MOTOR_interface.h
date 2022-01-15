/*
 * MOTOR_interface.h
 *
 *  Created on: Jan 11, 2022
 *      Author: Esraa
 */

#ifndef ECUAL_MOTOR_MOTOR_INTERFACE_H_
#define ECUAL_MOTOR_MOTOR_INTERFACE_H_

#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/PWM/PWM.h"

typedef struct{
	uint8_t port;
	uint8_t DirPinA;
	uint8_t DirPinB;
	uint8_t ENPin;
	uint8_t ChannelNum;
}MotorDef_t;

typedef enum{
	 CLOCKWISE,
	 ANTI_CLOCKWISE
}MotorDir_t;

uint8_t MOTOR_init(MotorDef_t* MotorElement);
uint8_t MOTOR_Move(MotorDef_t* MotorElement,uint8_t MotorSpeed,uint8_t MotorDir);
uint8_t MOTOR_Stop(MotorDef_t* MotorElement);

#endif /* ECUAL_MOTOR_MOTOR_INTERFACE_H_ */
