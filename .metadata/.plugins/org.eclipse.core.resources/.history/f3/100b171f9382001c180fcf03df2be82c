/*
 * INTERFACE_SLAVE.c
 *
 * Created: 1/28/2022 11:19:38 PM
 *  Author: Khaled Ali
 */ 
#include "INTERFACE_SLAVE.h"


uint8_t INTERFACE_u8Init(void){
	DIO_u8SetPinDirection(PORTB, PIN4, DIO_INPUT);
	DIO_u8SetPinDirection(PORTB, PIN5, DIO_INPUT);
	DIO_u8SetPinDirection(PORTB, PIN6, DIO_OUTPUT);
	DIO_u8SetPinDirection(PORTB, PIN7, DIO_INPUT);
	SPI_u8Init();
	return 1; //To be Changed
}

uint8_t INTERFACE_u8SendData(uint8_t* str){
	uint8_t slave_select;
	DIO_u8GetPinData(PORTB, PIN4, &slave_select);
	//if slave selected
	if(slave_select == DIO_LOW){
		SPI_u8SendString(str);
	}
	return 1; //To be Changed
}