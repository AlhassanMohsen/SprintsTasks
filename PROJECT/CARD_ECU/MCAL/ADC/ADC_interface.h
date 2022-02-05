/*
 * ADC_interface.h
 *
 *  Created on: Jan 16, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

#include "ADC_cfg.h"
#include "ADC_ERR_Handle.h"
#include "ADC_prv.h"

typedef enum {
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL5,
	CHANNEL6,
	CHANNEL7,
	CHANNEL8
} ChannelNumber_t;

typedef enum {
	ADC_FREE_RUNNIG,
	ADC_ANALOG_COMPARATOR,
	ADC_EXT_INT,
	ADC_TIM0_CMP,
	ADC_TIM0_OVF,
	ADC_TIM1_CMP,
	ADC_TIM1_OVF,
	ADC_CAPTURE_EVENT,
	ADC_SINGLE_CONVERSION
} ADCTriggerSource_t;

typedef struct {
	uint8_t port;
	uint8_t pin;
	ADCTriggerSource_t triggerSource;
} ADCChannel_t;

uint8_t ADC_u8Init(void);
uint8_t ADC_u8StartConversion(ADCChannel_t* st_ChannelConfig);
uint8_t ADC_u8GetRead(uint16_t* u16_ADCReading);
uint8_t ADC_u8GetVolt(uint16_t* ff32_ADCVolt);
uint8_t ADC_u8EnableInterrupt(void (*fnCallBack)(void));
uint8_t ADC_u8DisableInterrupt(void);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
