/*
 * ATM_prv.h
 *
 *  Created on: Jan 28, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef APP_ATM_PRV_H_
#define APP_ATM_PRV_H_

#define ATM_PASSWORD_LOCATION		0x01
#define ATM_MAX_AMOUNT_LOCATION		0x90
#define ATM_EEPROM_PTR				0x07
#define ATM_EEPROM_FIRST_TIME_ADDRESS	0xff
#define ATM_EEPROM_FIRST_TIME_DATA	0xAA

#define ATM_DATA_START_ADDRESS		0x08
#define ATM_DATA_END_ADDRESS		0x80
#define ATM_EEPROM_ADDRESS			0x00

#define ATM_ADMIN_PASSWORD			"1234"

#define ATM_PASSWORD_OK		1
#define ATM_PASSWORD_NOK		0

#define PROTEUS				1
#define PROJECT_PLATFORM  PROTEUS

#if PROJECT_PLATFORM == PROTEUS
#define ATM_TERMINAL_ENDLINE		0x0D

#define ATM_UART_BAUDRATE			9600

#define ATM_ADMIN_ADD_CUSTOMER		'1'
#define ATM_ADMIN_MAX_AMOUNT		'2'
#define ATM_ADMIN_EXIT				'3'

#define ATM_LCD_SECOND_ROW			1,0
#define ATM_LCD_DISPLAY_TIME		5000


#define ATM_INSERT_CARD				1
#define ATM_GET_TEMP				2

#define ATM_PASS_RIGHT				1
#define ATM_PASS_WRONG				0

#else
#define ATM_TERMINAL_ENDLINE		0x00
#endif


#endif /* APP_ATM_PRV_H_ */
