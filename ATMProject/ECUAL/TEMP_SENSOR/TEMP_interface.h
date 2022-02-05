/*
 * TEMP.h
 *
 *  Created on: Jan 17, 2022
 *      Author: vip
 */

#ifndef ECUAL_TEMP_SENSOR_TEMP_INTERFACE_H_
#define ECUAL_TEMP_SENSOR_TEMP_INTERFACE_H_

#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/ADC/ADC_interface.h"

#define TOTAL_READINGS_COUNT 100

typedef struct{
	uint8_t port;
	uint8_t pin;
}TEMPElement_t;

typedef enum{
	TEMP_OK=1,
	TEMP_NULL_INPUT,
	TEMP_ADC_Error,
	TEMP_UNSTABLE
}TEMP_ErrorState;

void TEMP_u8Init(void);
uint8_t TEMP_u8GetRead(TEMPElement_t* TempElement, uint16_t* f32TempReading);

#endif /* ECUAL_TEMP_SENSOR_TEMP_INTERFACE_H_ */
