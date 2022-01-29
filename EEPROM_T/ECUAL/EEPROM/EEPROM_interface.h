/*
 * EEPROM_interface.h
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef ECUAL_EEPROM_EEPROM_INTERFACE_H_
#define ECUAL_EEPROM_EEPROM_INTERFACE_H_

#include "../../LIB/Typedef.h"
#include "../../LIB/atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/I2C/I2C_interface.h"
#include "../../MCAL/DELAY/TIMER0.h"

void EEPROM_Init(void);
uint8_t EEPROM_u8WriteByteTo(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint8_t u8Data);
uint8_t EEPROM_u8RandonReadFrom(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint8_t* u8Data);
uint8_t EEPROM_u8WriteStringTo(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint8_t* u8Data);
uint8_t EEPROM_u8ReadStringFrom(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint8_t* u8Data);
uint8_t EEPROM_u8WriteIntTo(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint32_t u8Data);

#endif /* ECUAL_EEPROM_EEPROM_INTERFACE_H_ */
