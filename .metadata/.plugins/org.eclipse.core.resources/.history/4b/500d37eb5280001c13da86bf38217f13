/*
 * ADC_prv.h
 *
 *  Created on: Jan 16, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef MCAL_ADC_ADC_PRV_H_
#define MCAL_ADC_ADC_PRV_H_

/*
 * The Different Possibilities to the Vref of the ADC
 */
#define ADC_AREF		0
#define ADC_AVCC		1
#define ADC_INTENRNAL	3

/*
 * Define The Different Possibilities to the data adjustment of the ADC
 */
#define ADC_RIGHT_ADJUST 0
#define ADC_LEFT_ADJUST	 1

#define ADC_PRESCALAR_2		1
#define ADC_PRESCALAR_4		2
#define ADC_PRESCALAR_8		3
#define ADC_PRESCALAR_16	4
#define ADC_PRESCALAR_32	5
#define ADC_PRESCALAR_64	6
#define ADC_PRESCALAR_128	7

/*
 * Define The bits of each register 
 */

/*ADCSRA_REG bits */
#define ADEN		7
#define ADSC		6
#define ADATE		5
#define ADIF		4
#define ADIE		3
#define ADPS2		2
#define ADPS1		1
#define ADPS0		0

/*ADMUX_REG bits*/
#define REFS1		7
#define REFS0		6
#define ADLAR		5
#define MUX4		4
#define MUX3		3
#define MUX2		2
#define MUX1		1
#define MUX0		0

// trigger source select bits  
#define ADTS0		5
#define ADTS1		6
#define ADTS2		7

// define max ADC reading 
#define ADC_RESOLUTION		1024

/*
 * Mask for accessing reference voltage bits
 */

#define ADC_VREF_BITS	6

#define ADC_VREF_MASK (3<<6)

/*
 * Mask for accessing the Prescaler bits
 */

#define ADC_PRESCALAR_BITS	0

#define ADC_PRESCALAR_MASK (7<<0)

/*
 * Mask for accessing the MUX bits
 */

#define ADC_MUX_BITS	0

#define ADC_MUX_MASK (31<<0)

/*
 * Mask for accessing the trigger source bits
 */
#define ADC_TRIGGER_SOURCE_MASK (7<<5)


/*
 * Setting the MAX Voltage used by the ADC depending of the reference Voltage
 */
#if ADC_VREF ==  ADC_AVCC
#define ADC_MAX_VOLT 5000
#elif ADC_VREG == ADC_INTENRNAL
#define ADC_MAX_VOLT 2.56
#elif ADC_VREG == ADC_AREF
#define ADC_MAX_VOLT ADC_EXT_VREF
#endif

// Declaring the ISR of the ADC Interrupt
void __vector_16(void) __attribute__ ((signal, used));


#endif /* MCAL_ADC_ADC_PRV_H_ */
