/*
 * SPIConfig.h
 *
 *  Created on: Jan 25, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef MCAL_SPI_SPICONFIG_H_
#define MCAL_SPI_SPICONFIG_H_


/**
 *  Configure in which order the Data Bits will be transmitted to one of the following options
 *  		-SPI_LSB_FIRST
 *  		-SPI_MSB_FIRST
 */
#define SPI_DATA_ORDER		SPI_LSB_FIRST


/**
 * Configure the Rate of the SPI Transmission to one of the following options
 *           -SPI_CPU_4   : The Transmission rate equal to CPU Clock divided by 4
 *           -SPI_CPU_16  : The Transmission rate equal to CPU Clock divided by 16
 *           -SPI_CPU_64  : The Transmission rate equal to CPU Clock divided by 64
 *           -SPI_CPU_128 : The Transmission rate equal to CPU Clock divided by 128
 *           -SPI_CPU_2   : The Transmission rate equal to CPU Clock divided by 2
 *           -SPI_CPU_8   : The Transmission rate equal to CPU Clock divided by 8
 *           -SPI_CPU_32  : The Transmission rate equal to CPU Clock divided by 32
 *
 */
#define SPI_CLK_RATE		SPI_CPU_4

/**
 * Configure the SPI Data Sampling Mode to one of the following options :
 *            -SPI_SAMPLE_LEADING_RISING	:  The Leading Edge is RISING and the data is sampled on the LEADING
 *            -SPI_SAMPLE_TRAILING_FALLING	:  The Leading Edge is RISING and the data is sampled on the TRAILING
 *            -SPI_SAMPLE_LEADING_FALLING   :  The Leading Edge is FALLING and the data is sampled on the LEADING
 *            -SPI_SAMPLE_TRAILING_RISING   :  The Leading Edge is FALLING and the data is sampled on the TRAILING
 */
#define SPI_DATA_MODE		SPI_SAMPLE_LEADING_RISING



#endif /* MCAL_SPI_SPICONFIG_H_ */
