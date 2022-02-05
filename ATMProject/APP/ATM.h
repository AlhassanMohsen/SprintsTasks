/*
 * ATM.h
 *
 *  Created on: Jan 28, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef APP_ATM_H_
#define APP_ATM_H_

#include "../LIB/BIT_Math.h"
#include "../LIB/Typedef.h"
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/TIMER/TIMER.h"
#include "../MCAL/SPI/SPI.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../ECUAL/LCD/LCD.h"
#include "../ECUAL/KEYPAD/KEYPAD_interface.h"
#include "../ECUAL/MOTOR/MOTOR_interface.h"
#include "../ECUAL/BTN/Button.h"
#include "../ECUAL/TEMP_SENSOR/TEMP_interface.h"
#include "../SERVICE/SERVICE.h"
#include "../SERVICE/Strings/STR.h"


typedef enum{
	ATM_START,
	ATM_PROGRAMMING_MODE,
	ATM_OPERATION_MODE,
	ATM_WRONG_MODE_INPUT,
}ATMModes_t;

typedef enum{
	CARD_INACCESSIBLE=1,
	CARD_ACCESSIBLE
}CardState_t;

typedef struct
{
	uint8_t PAN[9];
	uint8_t PIN[4];
	uint8_t Mode;
}CardElement_t;



void ATM_APP(void);
void ATM_Init(void);

void ATM_UpdateMode(void);
void ATM_CheckPassword(uint8_t* pu8CheckResult);
void ATM_AddNewAccount(void);
void ATM_AddMaxAmount(void);
uint8_t ATM_GetPass(uint8_t * Pass_int,uint8_t* pu8PasswordCheck);
uint8_t ATM_GetAmmount( uint32_t * Ammount_int );
void ATM_GetCardData(uint8_t* pu8_DataPlace);
uint8_t ATM_GetBalance(uint32_t u32UserPAN,uint32_t* u32UserBalance, uint8_t* u8CardState);

#endif /* APP_ATM_H_ */
