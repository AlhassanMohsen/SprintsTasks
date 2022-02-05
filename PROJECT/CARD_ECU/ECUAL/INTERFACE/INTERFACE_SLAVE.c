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
	SPI_u8Init(SPI_MASTER);
	return 1; //To be Changed
}

uint8_t INTERFACE_u8SendData(uint8_t* str){
	//if slave selected
	uint8_t StrNav;

	DIO_u8GetPinData(PORTB, PIN4, &StrNav);

	if(StrNav == 0){
		//UART_u8SendString("Sended once");
		//UART_u8SendByte(0x0D);
		SPI_u8SendString(str);
	}else
	{
		//UART_u8SendString("Not Sended");
		//UART_u8SendByte(0x0D);
	}
/*	while(str[StrNav]!='\0')
	{
		SPI_SetData(str[StrNav]);
		StrNav++;
	}
*/
	return 1; //To be Changed
}
