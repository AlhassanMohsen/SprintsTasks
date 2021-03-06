/*
 * main.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */



#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../Service/Strings/STR.h"


#define SLAVE_ADDRESS		0x02
#define NEW_LINE_CHAR		0x0D
#define UART_BAUDRATE		9600
#define EEPROM_ADDRESS		0x00

int main(void)
{
	uint8_t au8Command[10];
	uint8_t au8EEPROMAddress[18];
	uint8_t au8EEPROMData[100];
	uint16_t EEPROM_Data_Address;

	I2C_u8Init();
	UART_u8Init(UART_BAUDRATE);
	while (1)
	{
		UART_u8SendString("Enter Your Command: ");
		UART_u8RecieveString(au8Command);

		if(STR_CMP(au8Command,(uint8_t*)"WRITE"))
		{
			UART_u8SendString("Enter EEPROM Address\r\n");
			UART_u8ReceiveCountedString(au8EEPROMAddress,16);
			EEPROM_Data_Address= STR_BinToInt(au8EEPROMAddress);
			UART_u8SendByte(0x0D);
			UART_u8SendString("OK Address is: ");
			UART_u8SendInt(EEPROM_Data_Address);
			UART_u8SendByte(0x0D);
			UART_u8SendString("Enter EEPROM Data\r\n");
			UART_u8RecieveString(au8EEPROMData);
			UART_u8SendString("OK Data is: ");
			UART_u8SendString(au8EEPROMData);
			UART_u8SendByte(0x0D);
			EEPROM_u8WriteStringTo(EEPROM_ADDRESS,EEPROM_Data_Address,au8EEPROMData);
		}else if (STR_CMP(au8Command,(uint8_t*)"READ"))
		{
			UART_u8SendString("Enter EEPROM Address\r\n");
			UART_u8ReceiveCountedString(au8EEPROMAddress,16);
			EEPROM_Data_Address= STR_BinToInt(au8EEPROMAddress);
			UART_u8SendByte(0x0D);
			UART_u8SendString("OK Address is: ");
			UART_u8SendInt(EEPROM_Data_Address);
			UART_u8SendByte(0x0D);
			EEPROM_u8ReadStringFrom(EEPROM_ADDRESS,EEPROM_Data_Address,au8EEPROMData);
			UART_u8SendString("The Data Stored is: ");
			UART_u8SendString(au8EEPROMData);
			UART_u8SendByte(0xD);
		}else
		{
			UART_u8SendString("Wrong Input");
		}
		I2C_u8Stop();
	}
}


