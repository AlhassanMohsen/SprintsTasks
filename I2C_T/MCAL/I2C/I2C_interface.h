/*
 * I2C_interface.h
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef MCAL_I2C_I2C_INTERFACE_H_
#define MCAL_I2C_I2C_INTERFACE_H_


#include "../../LIB/BIT_Math.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/Typedef.h"

/*
 * status codes that do not correspond to a defined TWI state
 */
#define I2C_BUS_ERROR							0x00  ///status codes that do not correspond to a defined TWI state,
#define I2C_NO_INFO								0xF8 ///indicates that no relevant information is available because the TWINT Flag is not set.
/*
 * Define the possible states of the I2C peripheral in Master Transmitter(MT) mode
 */
#define I2C_MT_START_TRANSMITTED				0x08
#define I2C_MT_REPEATED_START_TRANSMITTED		0x10
#define I2C_MT_SLAVE_WRITE_TRANSMITTED_ACK		0x18
#define I2C_MT_SLAVE_WRITE_TRANSMITTED_NACK		0x20
#define I2C_MT_DATA_TRANSMITTED_ACK				0x28
#define I2C_MT_DATA_TRANSMITTED_NACK			0x30
#define I2C_MT_ARBITRATION_LOST					0x38
/*
 * Define the possible states of the I2C peripheral in Master Receiver(MR) mode
 */
#define I2C_MR_SLAVE_ADDRESS_TRANSMITTED_ACK	0x40
#define I2C_MR_SLAVE_ADDRESS_TRANSMITTED_NACK	0x48
#define I2C_MR_DATA_RECEIVED_ACK				0x50
#define I2C_MR_DATA_RECEIVED_NACK				0x58
/*
 * Define the possible states of the I2C peripheral in Slave Receiver(SR) mode
 */
#define I2C_SR_OWN_ADDRESS_CALLED				0x60
#define I2C_SR_ARBITRATION_LOST_OWN_ADDRESS		0x68
#define I2C_SR_GENERAL_CALL						0x70
#define I2C_SR_ARBITRATION_LOST_GENERAL_CALL	0x78
#define I2C_SR_DATA_RECIEVED					0x80
#define I2C_SR_LAST_BYTE_RECIEVED				0x88
#define I2C_SR_GENERAL_DATA_RECEIVED			0x90
#define I2C_SR_GENERAL_LAST_BYTE_RECEIVED		0x98
#define I2C_SR_STOP_CONDITION					0xA0
/*
 * Define the possible states of the I2C peripheral in Slave Transmitter(ST) mode
 */
#define I2C_ST_OWN_ADDRESS_CALLED				0xA8
#define I2C_ST_ARBITRATION_LOST_OWN_ADDRESS		0xB0
#define I2C_ST_DATA_TRANSMITTED					0xB8
#define I2C_ST_LAST_BYTE_TRANSMITTED			0xC0
#define I2C_ST_DATA_NOT_AVAILABLE				0xC8

typedef enum {
	I2C_OK=1,
	I2C_START_ERROR,
	I2C_WRONG_STATUS,
	I2C_WRONG_ADDRESS,
	I2C_START_WRONG_PLACE,
	I2C_ILLEGAL_START,
	I2C_SLAVE_NOT_AVLBL,
}I2CErrorState_t;

typedef enum {
	I2C_MASTER_WRITE,
	I2C_MASTER_READ
}I2CMasterOperation_t;


uint8_t I2C_u8Init();
uint8_t I2C_u8GetStatus(void);
uint8_t I2C_u8MasterSendSLA(uint8_t u8SlaveAddress,uint8_t u8MasterOperation);
uint8_t I2C_u8MasterSendByte(uint8_t u8Data);
uint8_t I2C_u8MasterSendStart(void);
uint8_t I2C_u8MasterReceiveWithNAK(uint8_t* pu8Data);
uint8_t I2C_u8MasterReceiveWithACK(uint8_t* pu8Data);
uint8_t I2C_u8SendRepeatedStart(void);
uint8_t I2C_u8Stop(void);
uint8_t I2C_u8SlaveGetByte(uint8_t* pu8Reading);


#endif /* MCAL_I2C_I2C_INTERFACE_H_ */
