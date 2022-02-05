/*
 * TERMINAL_SLAVE.h
 *
 * Created: 1/28/2022 11:05:26 PM
 *  Author: Khaled Ali
 */ 


#ifndef TERMINAL_SLAVE_H_
#define TERMINAL_SLAVE_H_


#include "../../MCAL/UART/UART_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"


typedef enum
{
	CARD_USER_MODE=1,
	CARD_PROGRAMMING_MODE
}CardMode_t;

typedef struct{
	uint8_t NAME[10];
	uint8_t PAN[12];
	uint8_t PIN[5];
	uint8_t MODE;
}Card_t;



uint8_t TERMINAL_u8Init(void);
uint8_t TERMINAL_u8Interface(Card_t* card);
uint8_t TERMINAL_u8EnableInterrupt(void (*pfnCallBack)(void));
uint8_t TERMINAL_u8DisableInterrupt(void);
#endif /* TERMINAL_SLAVE_H_ */
