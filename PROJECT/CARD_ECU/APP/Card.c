/*
 * Card.c
 *
 * Created: 1/28/2022 2:29:22 PM
 *  Author: Khaled Ali
 */ 

#include "Card_prv.h"
#include "Card.h"

STATE u8State=USER;
Card_t card;
uint8_t *HoldeName;
uint8_t *PAN;
uint8_t *PIN;
uint8_t volatile counter=0;

void Card_init()
{
	uint8_t u8FirstTimeCheck;
	//uint8_t test[10];
	TERMINAL_u8Init();
	INTERFACE_u8Init();
	EEPROM_Init();
	TERMINAL_u8EnableInterrupt(UART_callBack);


	EXTI_u8Enable(INT2,EXTI_RISING_EDGE);

	EEPROM_u8RandonReadFrom(CARD_EEPROM_ADDRESS,CARD_EEPROM_FIRST_TIME_ADDRESS,&u8FirstTimeCheck);
	TIMER0_u8PollingDelay(10);

	if (u8FirstTimeCheck!=CARD_EEPROM_FIRST_TIME_DATA)
	{
		u8State = PROGRAMMING;
		card.MODE=CARD_PROGRAMMING_MODE;
		EEPROM_u8WriteByteTo(CARD_EEPROM_ADDRESS,CARD_EEPROM_FIRST_TIME_ADDRESS,CARD_EEPROM_FIRST_TIME_DATA);
	}else{

		//u8State = USER;
		EEPROM_u8ReadStringFrom(CARD_EEPROM_ADDRESS, CARD_HOLDER_NAME_ADDRESS,card.NAME);
		EEPROM_u8ReadStringFrom(CARD_EEPROM_ADDRESS, CARD_PAN_ADDRESS, card.PAN);
		EEPROM_u8ReadStringFrom(CARD_EEPROM_ADDRESS, CARD_PIN_ADDRESS, card.PIN);

		//TERMINAL_u8EnableInterrupt(UART_callBack);
	}
	DIO_u8SetPinDirection(PORTB, PIN2, DIO_INPUT);


}



void Card_App(void){

	while(1){
		switch(u8State){
			case PROGRAMMING:
			//Enter Programming mode
				TERMINAL_u8DisableInterrupt();
				HoldeName=(uint8_t*)"INACCESSIBLE";
				TERMINAL_u8Interface(&card);
				EEPROM_u8WriteStringTo(CARD_EEPROM_ADDRESS, CARD_HOLDER_NAME_ADDRESS, card.NAME);
				EEPROM_u8WriteStringTo(CARD_EEPROM_ADDRESS, CARD_PAN_ADDRESS,card.PAN);
				EEPROM_u8WriteStringTo(CARD_EEPROM_ADDRESS, CARD_PIN_ADDRESS, card.PIN);
				u8State = USER;
				TERMINAL_u8EnableInterrupt(UART_callBack);
			break;
			case USER:
				switch(counter)
				{
				case 0:
					HoldeName = card.PAN;
					break;
				case 1:
					HoldeName = card.PIN;
					break;
				default:
					counter=0;
					break;
				}
			break;
			default:
			break;
		}	
	}
}


void UART_callBack(void){

	uint8_t au8TerminalCommand[10];		// array to hold the command entered on the terminal

	// Receive the command
	UART_u8RecieveString(au8TerminalCommand);
	UART_u8SendString(au8TerminalCommand);
	if (STR_CMP(au8TerminalCommand,(uint8_t*)"ADMIN"))
	{
		u8State = PROGRAMMING;
	}else if(STR_CMP(au8TerminalCommand,(uint8_t*)"USER"))
	{
		u8State = USER;
	}else
	{
		UART_u8SendString((uint8_t*)"WRONG INPUT");
	}
}


void __vector_3(void) __attribute__ ((signal, used));

void __vector_3(void)
{
	SPI_u8SendString(HoldeName);
	counter++;
	CLR_BIT(GIFR_REG,5);
}
