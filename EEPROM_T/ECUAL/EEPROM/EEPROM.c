/*
 * EEPROM.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */

#include "EEPROM_prv.h"
#include "EEPROM_cfg.h"
#include "EEPROM_interface.h"

typedef union{
	uint32_t u32Data;
	uint8_t u8Bytes[4];
}Data_t;


void EEPROM_Init(void)
{
	I2C_u8Init();
}

uint8_t EEPROM_u8WriteByteTo(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint8_t u8Data)
{
	uint8_t u8OperationAddress = (EEPROM_CONTROL_BYTE_HIGH_NIBBLE_MASK|(u8ChipAddress<<EEPROM_FIRST_CHIP_SELECT_BIT));
	uint8_t u8ByteAddressHigh = (u16ByteAddress>>8);
	uint8_t u8ByteAddressLow = u16ByteAddress;

	I2C_u8MasterSendStart();
	I2C_u8MasterSendSLA(u8OperationAddress,I2C_MASTER_WRITE);
	I2C_u8MasterSendByte(u8ByteAddressHigh);
	I2C_u8MasterSendByte(u8ByteAddressLow);
	I2C_u8MasterSendByte(u8Data);

	I2C_u8Stop();
}


uint8_t EEPROM_u8RandonReadFrom(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint8_t* u8Data)
{
	uint8_t u8OperationAddress = (EEPROM_CONTROL_BYTE_HIGH_NIBBLE_MASK|(u8ChipAddress<<EEPROM_FIRST_CHIP_SELECT_BIT));
	uint8_t u8ByteAddressHigh = (u16ByteAddress>>8);
	uint8_t u8ByteAddressLow =u16ByteAddress;


	I2C_u8MasterSendStart();
	I2C_u8MasterSendSLA(u8OperationAddress,I2C_MASTER_WRITE);
	I2C_u8MasterSendByte(u8ByteAddressHigh);
	I2C_u8MasterSendByte(u8ByteAddressLow);
	I2C_u8SendRepeatedStart();
	I2C_u8MasterSendSLA(u8OperationAddress,I2C_MASTER_READ);
	I2C_u8MasterReceiveWithNAK(u8Data);
	I2C_u8Stop();

}


uint8_t EEPROM_u8WriteStringTo(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint8_t* u8Data)
{
	uint8_t u8OperationAddress = (EEPROM_CONTROL_BYTE_HIGH_NIBBLE_MASK|(u8ChipAddress<<EEPROM_FIRST_CHIP_SELECT_BIT));
	uint8_t u8ByteAddressHigh = (u16ByteAddress>>8);
	uint8_t u8ByteAddressLow = u16ByteAddress;
	uint8_t u8BytesCounter=0;

	I2C_u8MasterSendStart();
	I2C_u8MasterSendSLA(u8OperationAddress,I2C_MASTER_WRITE);
	I2C_u8MasterSendByte(u8ByteAddressHigh);
	I2C_u8MasterSendByte(u8ByteAddressLow);
	while (u8Data[u8BytesCounter]!='\0' && u8BytesCounter!=63)
	{
		I2C_u8MasterSendByte(u8Data[u8BytesCounter]);
		u8BytesCounter++;
	}
	I2C_u8MasterSendByte('\0');

	I2C_u8Stop();

}

uint8_t EEPROM_u8ReadStringFrom(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint8_t* u8Data)
{
	uint8_t u8OperationAddress = (EEPROM_CONTROL_BYTE_HIGH_NIBBLE_MASK|(u8ChipAddress<<EEPROM_FIRST_CHIP_SELECT_BIT));
	uint8_t u8ByteAddressHigh = (u16ByteAddress>>8);
	uint8_t u8ByteAddressLow =u16ByteAddress;
	uint8_t u8BytesCounter=0;
	uint8_t u8Flush;

	I2C_u8MasterSendStart();
	I2C_u8MasterSendSLA(u8OperationAddress,I2C_MASTER_WRITE);
	I2C_u8MasterSendByte(u8ByteAddressHigh);
	I2C_u8MasterSendByte(u8ByteAddressLow);
	I2C_u8SendRepeatedStart();
	I2C_u8MasterSendSLA(u8OperationAddress,I2C_MASTER_READ);
	do{
		I2C_u8MasterReceiveWithACK(&u8Data[u8BytesCounter]);
		u8BytesCounter++;
	}while (u8Data[u8BytesCounter-1]!='\0');
	I2C_u8MasterReceiveWithNAK(&u8Flush);
	I2C_u8Stop();

}

uint8_t EEPROM_u8WriteIntTo(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint32_t u8Data)
{
/*	 uint8_t u8Byte1 = ((u8Data& 0xff000000)>>24);
	DDRB_REG=0xff;

	uint8_t u8Byte2 = ((u8Data& 0x00ff0000)>>16);
	PORTB_REG=((u8Data& 0x00ff0000)>>16);
	uint8_t u8Byte3 = ((u8Data& 0x0000ff00)>>8);
	uint8_t u8Byte4 = ((u8Data& 0x000000ff));
*/
	Data_t New;
	New.u32Data=u8Data;
	EEPROM_u8WriteByteTo(u8ChipAddress,u16ByteAddress,New.u8Bytes[3]);
	TIMER0_u8PollingDelay(10);
	EEPROM_u8WriteByteTo(u8ChipAddress,u16ByteAddress+1,New.u8Bytes[2]);
	TIMER0_u8PollingDelay(10);
	EEPROM_u8WriteByteTo(u8ChipAddress,u16ByteAddress+2,New.u8Bytes[1]);
	TIMER0_u8PollingDelay(10);
	EEPROM_u8WriteByteTo(u8ChipAddress,u16ByteAddress+3,New.u8Bytes[0]);
	TIMER0_u8PollingDelay(10);
}

uint8_t EEPROM_u8ReadIntFrom(uint8_t u8ChipAddress,uint16_t u16ByteAddress,uint32_t* u8Data)
{
	uint8_t u8Byte1;
	uint8_t u8Byte2;
	uint8_t u8Byte3;
	uint8_t u8Byte4;
	EEPROM_u8RandonReadFrom(u8ChipAddress,u16ByteAddress,&u8Byte1);
	TIMER0_u8PollingDelay(10);
	EEPROM_u8RandonReadFrom(u8ChipAddress,u16ByteAddress+1,&u8Byte2);
	TIMER0_u8PollingDelay(10);
	EEPROM_u8RandonReadFrom(u8ChipAddress,u16ByteAddress+2,&u8Byte3);
	TIMER0_u8PollingDelay(10);
	EEPROM_u8RandonReadFrom(u8ChipAddress,u16ByteAddress+3,&u8Byte4);
	TIMER0_u8PollingDelay(10);
	*u8Data = (u8Byte1<<24|u8Byte2<<16|u8Byte3<<8|u8Byte4);
}
