/*
 * PWM.h
 *
 * Created: 1/9/2022 11:06:56 PM
 *  Author: Khaled Ali
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "../../LIB/Typedef.h"
#include "../DIO/DIO_interface.h"
#include "../TIMER/TIMER.h"
#include "PWM.h"


#define MAX_VALUE 256U
#define MAX_DUTY 100U

typedef struct{
	uint8_t port;
	uint8_t pin;
}PWMPin_t;

uint8_t PWM_u8Init(CHANNEL channel,PWMPin_t* pwm);
uint8_t PWM_u8DutyCycle(CHANNEL channel, uint32_t dutyCycle);

uint8_t PWM_u8Stop(void);
#endif /* PWM_H_ */
