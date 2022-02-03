/*
 * SPI.c
 *
 * Created: 1/24/2022 6:17:40 PM
 *  Author: Khaled Ali
 */ 
#include "SPI.h"

#include "../DELAY/TIMER0.h"

void SPI_u8Init(void){
	if(DATA_ORDER){
		SET_BIT(SPCR_REG, DORD);
	}
	else{
		CLR_BIT(SPCR_REG, DORD);
	}
	if(MASTER == 1){
		SET_BIT(SPCR_REG, MSTR);
	}
	else{
		CLR_BIT(SPCR_REG, MSTR);
	}
	
	if(SPI_PRESCALER == 4){
		CLR_BIT(SPCR_REG, SPR1);
		CLR_BIT(SPCR_REG, SPR0);
	}
	else if(SPI_PRESCALER == 16){
		CLR_BIT(SPCR_REG, SPR1);
		SET_BIT(SPCR_REG, SPR0);
	}
	else if(SPI_PRESCALER == 64){
		SET_BIT(SPCR_REG, SPR1);
		CLR_BIT(SPCR_REG, SPR0);
	}
	else if(SPI_PRESCALER == 128){
		SET_BIT(SPCR_REG, SPR1);
		SET_BIT(SPCR_REG, SPR0);
	}
	SET_BIT(SPCR_REG, SPE);
}

void SPI_u8SendData(uint8_t data){
	SPDR_REG = data;
	uint8_t volatile buffer;
	while(GET_BIT(SPSR_REG, SPIF) == 0);
	//Flush the buffer
	buffer = SPDR_REG;
}

SPI_ERR_STATE SPI_u8GetData(uint8_t* data){
	SPI_ERR_STATE u8State = SPI_OK;
	if(data == NULL){
		u8State = SPI_ERR;
	}
	else{
		if(MASTER == 1){
			SPDR_REG = 0xFF; //Initiate the Clock
		}
		while(GET_BIT(SPSR_REG, SPIF) == 0);
		*data = SPDR_REG;
	}
	return u8State;
}

void SPI_SetData(uint8_t data){
	SPDR_REG = data;
}

SPI_ERR_STATE SPI_u8SendString(uint8_t* str){
	SPI_ERR_STATE u8State = SPI_OK;
	if(str == NULL){
		u8State = SPI_ERR;
	}
	else{
		uint8_t* itr = str;
		while(*itr != '\0'){
			SPI_u8SendData(*itr);
			itr++;
			TIMER0_u8PollingDelay(10);
		}
	}
	return u8State;
}
SPI_ERR_STATE SPI_u8RecieveString(uint8_t* str, uint8_t size){
	SPI_ERR_STATE u8State = SPI_OK;
	if(str == NULL){
		u8State =  SPI_ERR;
	}
	else{
		for(uint8_t itr = 0; itr < size && u8State == SPI_OK; ++itr){
			u8State = SPI_u8GetData(&str[itr]);
		}
	}
	return u8State;
}