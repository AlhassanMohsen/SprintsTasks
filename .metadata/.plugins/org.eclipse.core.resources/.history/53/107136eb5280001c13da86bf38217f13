/*
 * ADC.c
 *
 *  Created on: Sep 8, 2018
 *      Author: hp
 */

#include "ADC_new.h"
#include "../DELAY/TIMER0.h"
void ADC_Init (void)
{
	ADCSRA_REG = 0x87;          /* Enable ADC, with freq/128  */
	ADMUX_REG = 0x40;           /* Vref: Avcc, ADC channel: 0 */
}

uint16_t ADC_Read (uint8_t channel)
{
	ADMUX_REG = 0x40 | (channel & 0x07);   /* set input channel to read */
	ADCSRA_REG |= (1<<6);               /* Start ADC conversion */
	while (!(ADCSRA_REG & (1<<4)));     /* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA_REG |= (1<<4);               /* Clear interrupt flag */
	TIMER0_u8PollingDelay(1);
	return ADC_REG;                       /* Return ADC word */
}
