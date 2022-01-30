/*
 * ADC_cfg.h
 *
 *  Created on: Jan 16, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef MCAL_ADC_ADC_CFG_H_
#define MCAL_ADC_ADC_CFG_H_

/**
 * Configure the Reference voltage of the ADC to one of the following
 * 		1- ADC_AREF 	: AREF, Internal Vref turned off
 * 		2- ADC_AVCC		: AVCC with external capacitor at AREF pin
 * 		3- ADC_INTENRNAL: Internal 2.56V Voltage Reference with external capacitor at AREF pin
 */
#define ADC_VREF	ADC_AVCC

//define the value of the external voltage on AREF pin in volt "if used"
#define ADC_EXT_VREF	5

/**
 * This Configuration affects the presentation of the ADC conversion result in the ADC Data Register.
 * Write ADC_LEFT_ADJUST to left adjust the result or ADC_RIGHT_ADJUST to make the result right adjusted.
 */
#define ADC_DATA_ADJUSMENT	ADC_RIGHT_ADJUST

/**
 * These configuration affects the division factor between the XTAL frequency and the input clock to the ADC.
 * and can be one of the following:
 *     -ADC_PRESCALAR_2
 *     -ADC_PRESCALAR_4
 *     -ADC_PRESCALAR_8
 *     -ADC_PRESCALAR_16
 *     -ADC_PRESCALAR_32
 *     -ADC_PRESCALAR_64
 *     -ADC_PRESCALAR_128
 */

/*
 * in this case F_CPU 8MHz 8MHz / 64 = 125 KHz 
 * NOTE : the successive approximation circuitry requires an input clock frequency between
 * 50kHz and 200kHz to get maximum resolution.
 */

#define ADC_PRESCALAR	ADC_PRESCALAR_128

#endif /* MCAL_ADC_ADC_CFG_H_ */
