/*
 * SPI_interface.h
 *
 *  Created on: Jan 25, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#include "../../LIB/BIT_Math.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/Typedef.h"
#include "SPI_ERR_HANDLE.h"

/**
 * @enum Define the possible states of the SPI Peripheral
 */
typedef enum {
	SPI_NOT_INITIALIZED,//!< The Peripheral is not initialized and can't be used
	SPI_MASTER,         //!< The peripheral is initialized in Master mode
	SPI_SLAVE           //!< The peripheral is initialized in slave mode
}SPIMode_t;


typedef union{
	uint32_t num;
	uint8_t u8Bytes[4];
}IntData_t;
/**
 * @fn uint8_t SPI_u8Init(SPIMode_t u8SPIMode)
 * @brief This function is used to initialize the SPI peripheral in the passed mode
 * @param u8SPIMode indicates the desired mode of the SPI
 * @pre This function require
 * 			- the configurations in the peripheral configuration file is configured with allowed options
 * 			- the u8SPIMode should take only two possibilities  SPI_MASTER or SPI_SLAVE
 * @return number between 1-255 indicates the error states of the function
 */
uint8_t SPI_u8Init(SPIMode_t u8SPIMode);

/**
 * @fn uint8_t SPI_u8ReceiveByte(uint8_t* u8Data)
 * @brief This function is used to Receive a byte from the SPI peripheral
 * @param pu8Data a pointer to a memory place to save the reading in.
 * @pre This function require
 * 			- The SPI to be initialized
 * 			- the pu8Data pointer can not points to NULL
 * @return number between 1-255 indicates the error states of the function
 */
uint8_t SPI_u8ReceiveByte(uint8_t* pu8Data);

/**
 * @fn uint8_t SPI_u8SendByte(uint8_t u8Data)
 * @brief This function is used to Send a byte using the SPI peripheral
 * @param u8Data a 8 bit data to be sent.
 * @pre This function require
 * 			- The SPI to be initialized
 * @return number between 1-255 indicates the error states of the function
 */
uint8_t SPI_u8SendByte(uint8_t u8Data);

/**
 * @fn uint8_t SPI_u8SendString(uint8_t* pu8Data)
 * @brief This function is used to Send a String using the SPI peripheral
 * @param pu8Data a pointer to an array of 8 bit data to be sent.
 * @pre This function require
 * 			- The SPI to be initialized
 * 			- the pu8Data pointer can not points to NULL
 * @return number between 1-255 indicates the error states of the function
 */
uint8_t SPI_u8SendString(uint8_t* pu8Data);

/**
 * @fn uint8_t SPI_u8ReceiveString(uint8_t* pu8Data)
 * @brief This function is used to Receive a String using the SPI peripheral
 * @param pu8Data a pointer to an array of characters to save the readings in.
 * @pre This function require
 * 			- The SPI to be initialized
 * 			- the pu8Data pointer can not points to NULL
 * @return number between 1-255 indicates the error states of the function
 */
uint8_t SPI_u8ReceiveString(uint8_t* pu8Data);


/**
 * @fn uint8_t SPI_u8EnableInterrupt(void (*pfnCallBack)(void))
 * @brief This function is called to enable the SPI Transmit complete Interrupt
 * @pre - the SPI must be initialized
 * 		- the pointer to function not pointing to NULL
 * @param pfnCallBack this is a pointer to function that will be called when the interrupt is fired
 * @return return a number from 1-255 representing the error state of the Function and it can be
 */
uint8_t SPI_u8EnableInterrupt(void (*pfnCallBack)(void));

/**
 * @fn void SPI_u8DisableInterrupt(void)
 * @brief Used to disable the SPI Interrupt
 */
void SPI_u8DisableInterrupt(void);

/**
 * @fn void SPI_u8Deinit(void)
 * @brief This function is called to Stop the SPI Peripheral and De-initialize it
 */
void SPI_u8Deinit(void);

#endif /* MCAL_SPI_SPI_H_ */
