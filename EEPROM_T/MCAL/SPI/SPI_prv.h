/*
 * SPI_prv.h
 *
 *  Created on: Jan 25, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef MCAL_SPI_SPI_PRV_H_
#define MCAL_SPI_SPI_PRV_H_

/**
 * Define the Data order possible modes
 */
#define SPI_LSB_FIRST	0
#define SPI_MSB_FIRST	1


/**
 * Define the Different Possibilities of the SPI Clock Rate
 */
#define SPI_CPU_4		0
#define SPI_CPU_16		1
#define SPI_CPU_64		2
#define SPI_CPU_128		3
#define SPI_CPU_2		4
#define SPI_CPU_8		5
#define SPI_CPU_32		6

/**
 * Define the Different Possibilities of the Sample modes of the SPI
 */
#define SPI_SAMPLE_LEADING_RISING		0
#define SPI_SAMPLE_TRAILING_FALLING		1
#define SPI_SAMPLE_LEADING_FALLING		2
#define SPI_SAMPLE_TRAILING_RISING		3


/**
 * @brief the SPI Interrupt ISR
 */
void __vector_12(void);

#endif /* MCAL_SPI_SPI_PRV_H_ */
