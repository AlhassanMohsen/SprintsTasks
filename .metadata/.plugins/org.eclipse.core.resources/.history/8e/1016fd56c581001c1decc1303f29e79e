/*
 * ATM.h
 *
 *  Created on: Jan 28, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef APP_ATM_H_
#define APP_ATM_H_

#include "../MCAL/UART/UART_interface.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"

typedef enum{
	ATM_START,
	ATM_PROGRAMMING_MODE,
	ATM_OPERATION_MODE,
	ATM_WRONG_MODE_INPUT,
}ATMModes_t;


void ATM_UpdateMode(void);
void ATM_CheckPassword(uint8_t* pu8CheckResult);
void ATM_AddNewAccount(void);
#endif /* APP_ATM_H_ */
