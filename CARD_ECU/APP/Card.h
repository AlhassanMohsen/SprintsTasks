/*
 * Card.h
 *
 * Created: 1/28/2022 2:29:33 PM
 *  Author: Khaled Ali
 */ 


#ifndef CARD_H_
#define CARD_H_

#include "../MCAL/TIMER/TIMER.h"
#include "../MCAL/SPI/SPI.h"
#include "../MCAL/EXTI/EXTI.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../ECUAL/INTERFACE/TERMINAL_SLAVE.h"
#include "../ECUAL/INTERFACE/INTERFACE_SLAVE.h"
#include "../ECUAL/LED/LED.h"
#include "../SERVICE/Strings/STR.h"

#define  UNIQUE_PATTERN 0x10101010




typedef enum{
	PROGRAMMING=1,
	USER
	}STATE;

void Card_init(void);
void Card_App(void);
void UART_callBack(void);
#endif /* CARD_H_ */
