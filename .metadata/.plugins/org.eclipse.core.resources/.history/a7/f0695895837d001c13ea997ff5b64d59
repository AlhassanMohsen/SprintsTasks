/*
 * ADC.c
 *
 *  Created on: Jan 16, 2022
 *      Author: Abdelrhman Elsawy
 */

#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/atmega32.h"
#include "../DELAY/TIMER0.h"
#include "ADC_interface.h"

static void (*ADC_callBack)(void);
uint8_t ADC_u8Init(void) {
	uint8_t u8ErrorState = ADC_OK;
	if (ADC_VREF== 0 || ADC_VREF==1 || ADC_VREF == 3)
	{
		ADMUX_REG &= ~ ADC_VREF_MASK;
		ADMUX_REG |= (ADC_VREF << REFS0_BIT);
	}else
	{
		u8ErrorState = ADC_VREF_ERROR;
	}
	// Set the Data Adjustment of the ADC depending on the ADC_DATA_ADJUSMENT configured in the ADC configuration file
	if (ADC_DATA_ADJUSMENT == ADC_LEFT_ADJUST) {
	SET_BIT(ADMUX_REG, ADLAR_BIT);
	} else {
	CLR_BIT(ADMUX_REG, ADLAR_BIT);
	}

	//Set the prescaler of the ADC depending on the ADC_PRESCALAR configured in the ADC configuration file
	if (ADC_PRESCALAR>0 && ADC_PRESCALAR<8)
	{
		//ADCSRA_REG &= ADC_PRESCALAR_MASK;
		ADMUX_REG &= ~ ADC_PRESCALAR_MASK;
		ADMUX_REG |= (ADC_PRESCALAR << ADC_PRESCALAR_BITS);
	}else
	{
		u8ErrorState = ADC_WRONG_PRESCALAR;
	}

	return u8ErrorState;
}

uint8_t ADC_u8StartConversion(ADCChannel_t* st_ChannelConfig) {
	uint8_t u8ErrorState = ADC_OK;

	if (st_ChannelConfig != NULL) {
		// Choose the ADC Channel to convert from
		ADMUX_REG &= ~ ADC_MUX_MASK;
		ADMUX_REG |= (st_ChannelConfig->pin << ADC_MUX_BITS);

		//After configuring the conversion enable the ADC to start the conversion process
		SET_BIT(ADCSRA_REG, ADEN_BIT);
		//Set the conversion mode and trigger source
		if (st_ChannelConfig->triggerSource == ADC_SINGLE_CONVERSION) {
			// if the conversion mode is single conversion disable the auto trigger then give the start signal
			//CLR_BIT(ADCSRA_REG, ADATE_BIT);
			SET_BIT(ADCSRA_REG, ADSC_BIT);
		} else {
			//if the conversion is not single then enable the Auto trigger mode
			SET_BIT(ADCSRA_REG, ADATE_BIT);
			// After Enabling the auto trigger mode Set the trigger source
			SFIOR_REG &= ~ ADC_TRIGGER_SOURCE_MASK;
			SFIOR_REG |= (st_ChannelConfig->triggerSource << ADTS0_BIT);
			//if the trigger source is the ending of the current conversion (free running) then you need to start the first conversion manually
			if (st_ChannelConfig->triggerSource == ADC_FREE_RUNNIG) {
				SET_BIT(ADCSRA_REG, ADSC_BIT);
			} else {
				//NOP
			}
		}

	} else {

		u8ErrorState = ADC_NULL_INPUT;
	}

	return u8ErrorState;
}


uint8_t ADC_u8GetRead(uint16_t* u16_ADCReading) {

	uint8_t u8ErrorState = ADC_OK;

	if (u16_ADCReading != NULL) // Check if the pointer is pointing to NULL or not
	{
		// wait until the current conversion is finished

		while ( GET_BIT(ADCSRA_REG,ADIF_BIT) != 1);
		//first check for the data adjustment then Get the data from the ADC data registers
		if (GET_BIT(ADMUX_REG,ADLAR_BIT)==1)
		{
			//if the data is left ADJUSTED then
			*u16_ADCReading=(ADCL_REG>>6)|(ADCH_REG<<2);
		}else
		{
			//if the data is right ADJUSTED then
			*u16_ADCReading = ADCL_REG | ( ADCH_REG << 8);
		}
		// Clear the flag after reading
		CLR_BIT(ADCSRA_REG, ADIF);
	}
	else
	{
		u8ErrorState = ADC_NULL_INPUT;
	}
	return u8ErrorState;
}

uint8_t ADC_u8GetVolt(uint16_t* f32_ADCVolt) {

	uint8_t u8ErrorState = ADC_OK;
	uint16_t u16_ADCReading = 0;

	if (f32_ADCVolt !=NULL)
	{
		//Get the ADC data to convert to voltage
		if (ADC_u8GetRead(&u16_ADCReading) == ADC_OK)
		{
			// if the data is fetched correctly then calculate the volt using the equation volt = ADCread * (Vref/resolution)
			*f32_ADCVolt = ((uint16_t)u16_ADCReading * (ADC_MAX_VOLT / ADC_RESOLUTION));
			//*f32_ADCVolt = u16_ADCReading;
		}
		else
		{
			u8ErrorState = ADC_GetVolt_Error;
		}
	}
	else
	{
		u8ErrorState = ADC_NULL_INPUT;
	}

	return u8ErrorState;
}

uint8_t ADC_u8EnableInterrupt(void (*fnCallBack)(void)) {

	uint8_t u8ErrorState = ADC_OK;
	if (fnCallBack != NULL) // Check that the pointer is not pointing to NULL
	{
		//Set the Call Back Function for the Interrupt
		ADC_callBack = fnCallBack;
		//Enable Global Interrupt
		SET_BIT(SREG_REG, I_BIT);
		//Enable ADC Interrupt
		SET_BIT(ADCSRA_REG, ADIE);

		//Check that change took place
		if ((GET_BIT(SREG_REG, I_BIT) == 0) || (GET_BIT(ADCSRA_REG,ADIE) == 0))
		{
			u8ErrorState = ADC_EnableInterrupt_Error;
		}else
		{
			//NOP
		}

	}
	else
	{
		u8ErrorState = ADC_NULL_INPUT;
	}
	return u8ErrorState;
}

uint8_t ADC_u8DisableInterrupt(void) {

	uint8_t u8ErrorState = ADC_OK;

	//Disable ADC Interrupt
	CLR_BIT(ADCSRA_REG, ADIE);

	//Check that change took place
	if ( GET_BIT(ADCSRA_REG,ADIE) != 0)
	{
		//if the interrupt is not disabled then return Error
		u8ErrorState = ADC_DisableInterrupt_Error;
	}else
	{
		//NOP
	}

	return u8ErrorState;
}

void __vector_16(void) {
	if (ADC_callBack != NULL) {
		ADC_callBack();
	}
}
