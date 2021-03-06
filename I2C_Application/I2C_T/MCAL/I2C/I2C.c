/*
 * I2C.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */

#include "I2C_interface.h"
#include "I2C_prv.h"
#include "I2C_config.h"
#include "../../ECUAL/LED/LED.h"
LED_t LEDTEST1={PORTA,PIN0};
LED_t LEDTEST2={PORTA,PIN1};

static volatile uint8_t gu8_I2CState= I2C_NO_INFO;
static volatile uint8_t gu8_I2CMode;
static volatile uint8_t gu8_I2CData[255]={0};
static volatile uint8_t gu8_I2CLastByte= 0;
static volatile uint8_t gu8_I2CRepeatedStart= 0;


uint8_t I2C_u8Init()
{
	uint8_t u8ErrorState = I2C_OK;

	//Set the clock rate of the I2C bus
	TWBR_REG = I2C_400KHZ;
	//Set the slave address which it will respond to
	TWAR_REG =I2C_OWN_SLAVE_ADDRESS;
	//Enable the ACK
	SET_BIT(TWCR_REG,TWEA_BIT);
	SET_BIT(TWCR_REG,TWIE_BIT);
	SET_BIT(SREG_REG,I_BIT);
	//Enable the I2C Peripheral
	SET_BIT(TWCR_REG,TWEN_BIT);
	LED_u8Init(&LEDTEST1);
	LED_u8Init(&LEDTEST2);


	return u8ErrorState;
}


uint8_t I2C_u8GetStatus(void)
{
	return TWSR_REG & I2C_PRESCALAR_MASK;
}

uint8_t I2C_u8MasterSendByte(uint8_t u8SlaveAddress, uint8_t u8Data)
{
	uint8_t u8ErrorState = I2C_OK;


	if (u8SlaveAddress<I2C_ADDRESSES_LIMIT)
	{//check that the address is less than 120 because the addresses from 120 to 127 are reserved for future purposes

		//Send the Start Condition
		SET_BIT(TWCR_REG,TWSTA_BIT);
		while (!(gu8_I2CState== I2C_MT_DATA_TRANSMITTED_ACK || gu8_I2CState== I2C_MT_DATA_TRANSMITTED_NACK))
		{//do the following until the status of the I2C states that the transmission is done successfully

			//Wait until it is sent
			while (!GET_BIT(TWCR_REG,TWINT_BIT));
			//Get the state of the I2C
			//gu8_I2CState= I2C_u8GetStatus();

			switch(gu8_I2CState)// check which state it is
			{
			case I2C_MT_START_TRANSMITTED:
				//if it is state that the start condition is successfully sent then load the slave address in the data register and set the mode to write
				TWDR_REG = u8SlaveAddress;
				CLR_BIT(TWDR_REG,0);
				// Clear the interrupt flag to start the next action by the peripheral
				ASSIGN_HIGH_NIB(TWCR_REG,I2C_CLR_INTERRUPT_FLAG);

				break;
			case I2C_MT_SLAVE_WRITE_TRANSMITTED_ACK:
				//if it is state that the SLA/W is successfully sent then load the data to be sent in the data register
				TWDR_REG= u8Data;
				// Clear the interrupt flag to start the next action by the peripheral
				ASSIGN_HIGH_NIB(TWCR_REG,I2C_CLR_INTERRUPT_FLAG);
				LED_u8On(&LEDTEST1);
				break;
			case I2C_MT_SLAVE_WRITE_TRANSMITTED_NACK:
				//if it is state that the SLA/W is successfully sent then load the data to be sent in the data register
				TWDR_REG= u8Data;
				// Clear the interrupt flag to start the next action by the peripheral
				ASSIGN_HIGH_NIB(TWCR_REG,I2C_CLR_INTERRUPT_FLAG);
				break;

			default:
				u8ErrorState = I2C_WRONG_STATUS;
			}
		}
		LED_u8On(&LEDTEST2);

	}else
	{
		u8ErrorState = I2C_WRONG_ADDRESS;
	}
	return u8ErrorState;
}

uint8_t I2C_u8SendRepeatedStart(void)
{
	uint8_t u8ErrorState = I2C_OK;
//	uint8_t u8I2CState= I2C_u8GetStatus();

	if (gu8_I2CState==I2C_MT_DATA_TRANSMITTED_ACK || gu8_I2CState==I2C_MT_DATA_TRANSMITTED_NACK)
	{// if the current state is the data byte is sent
		//Then send the Repeated start condition and clear the interrupt flag to send it
		ASSIGN_HIGH_NIB(TWCR_REG,I2C_CLR_INTERRUPT_FLAG);
	}else
	{
		// if not update the error state to indicate that the start condition can not be send here
		u8ErrorState = I2C_START_WRONG_PLACE;
	}


	return u8ErrorState;
}

uint8_t I2C_u8Stop(void)
{
	uint8_t u8ErrorState = I2C_OK;
	//uint8_t u8I2CState= I2C_u8GetStatus();

	if (gu8_I2CState!=I2C_MT_START_TRANSMITTED || gu8_I2CState==I2C_MT_REPEATED_START_TRANSMITTED)
	{// if the current state is not after a start condition

		//Then send the stop condition and clear the interrupt flag to send it
		ASSIGN_HIGH_NIB(TWCR_REG,I2C_SEND_STOP_CONDITION);
	}else
	{
		// if not update the error state to indicate that the start condition can not be send here
		u8ErrorState = I2C_START_WRONG_PLACE;
	}


	return u8ErrorState;
}

uint8_t I2C_u8SlaveGetByte(uint8_t* pu8Reading)
{
	uint8_t u8TempReading;

	while (!(gu8_I2CState==I2C_SR_DATA_RECIEVED ||gu8_I2CState==I2C_SR_LAST_BYTE_RECIEVED ) )
	{
		while (!GET_BIT(TWCR_REG,TWINT_BIT));
		ASSIGN_HIGH_NIB(TWCR_REG,I2C_CLR_INTERRUPT_FLAG);
	}
	ASSIGN_HIGH_NIB(TWCR_REG,I2C_RECOGNIZE_SLA_WITH_ACK);
	*pu8Reading= TWDR_REG;

}

void __vector_19(void) {
	gu8_I2CState=TWSR_REG & I2C_PRESCALAR_MASK;


}
