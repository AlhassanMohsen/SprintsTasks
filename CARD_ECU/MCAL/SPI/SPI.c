/*
 * SPI.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Alhassan Mohsen
 */

#include "SPI.h"

#include "SPI_prv.h"
#include "SPIConfig.h"
#include "../../ECUAL/LED/LED.h"
#include "../UART/UART_interface.h"
LED_t LEDT={PORTA,PIN7};

static uint8_t volatile gu8_SPIState= SPI_NOT_INITIALIZED; /// This flag is used to detect when user is trying to use the Peripheral before initialization or in wrong mode
static void (*gpf_SPICallBack)(void)=NULL; /// pointer to the function that will be called in the SPI ISR



/**
 * @fn uint8_t SPI_u8Init(SPIMode_t u8SPIMode)
 * @brief This function is used to initialize the SPI peripheral in the passed mode
 * @pre This function require
 * 			- the configurations in the peripheral configuration file is configured with allowed options
 * 			- the u8SPIMode should take only two possibilities  SPI_MASTER or SPI_SLAVE
 */
uint8_t SPI_u8Init(SPIMode_t u8SPIMode)
{
	uint8_t u8ErrorState = SPI_OK;

LED_u8Init(&LEDT);
	/*
	 * Set the transmittion Clock of the SPI as configured by the SPI_CLK_RATE Configuration
	 */
#if SPI_CLK_RATE == SPI_CPU_4
	CLR_BIT(SPCR_REG,SPR0_BIT);
	CLR_BIT(SPCR_REG,SPR1_BIT);
	CLR_BIT(SPSR_REG,SPI2X_BIT);
#elif SPI_CLK_RATE == SPI_CPU_16
	SET_BIT(SPCR_REG,SPR0_BIT);
	CLR_BIT(SPCR_REG,SPR1_BIT);
	CLR_BIT(SPSR_REG,SPI2X_BIT);
#elif SPI_CLK_RATE == SPI_CPU_64
	CLR_BIT(SPCR_REG,SPR0_BIT);
	SET_BIT(SPCR_REG,SPR1_BIT);
	CLR_BIT(SPSR_REG,SPI2X_BIT);
#elif SPI_CLK_RATE == SPI_CPU_128
	SET_BIT(SPCR_REG,SPR0_BIT);
	SET_BIT(SPCR_REG,SPR1_BIT);
	CLR_BIT(SPSR_REG,SPI2X_BIT);
#elif SPI_CLK_RATE == SPI_CPU_2
	CLR_BIT(SPCR_REG,SPR0_BIT);
	CLR_BIT(SPCR_REG,SPR1_BIT);
	SET_BIT(SPSR_REG,SPI2X_BIT);
#elif SPI_CLK_RATE == SPI_CPU_8
	SET_BIT(SPCR_REG,SPR0_BIT);
	CLR_BIT(SPCR_REG,SPR1_BIT);
	SET_BIT(SPSR_REG,SPI2X_BIT);
#elif SPI_CLK_RATE == SPI_CPU_32
	CLR_BIT(SPCR_REG,SPR0_BIT);
	SET_BIT(SPCR_REG,SPR1_BIT);
	SET_BIT(SPSR_REG,SPI2X_BIT);
#else
	u8ErrorState = SPI_WRONG_CLK_CFG;
#endif

	/*
	 * Set the DATA sampling mode of the SPI as configured by the SPI_DATA_MODE configuration in the configuration file
	 */
#if SPI_DATA_MODE == SPI_SAMPLE_LEADING_RISING
	CLR_BIT(SPCR_REG,CPHA_BIT);
	CLR_BIT(SPCR_REG,CPOL_BIT);
#elif SPI_DATA_MODE == SPI_SAMPLE_TRAILING_FALLING
	SET_BIT(SPCR_REG,CPHA_BIT);
	CLR_BIT(SPCR_REG,CPOL_BIT);
#elif SPI_DATA_MODE == SPI_SAMPLE_LEADING_FALLING
	CLR_BIT(SPCR_REG,CPHA_BIT);
	SET_BIT(SPCR_REG,CPOL_BIT);
#elif SPI_DATA_MODE == SPI_SAMPLE_TRAILING_RISING
	SET_BIT(SPCR_REG,CPHA_BIT);
	SET_BIT(SPCR_REG,CPOL_BIT);
#else
	u8ErrorState = SPI_WRONG_SAMPLE_MODE_CFG;
#endif

	/*
	 * Setting the Data bits transmitting order as configured by the SPI_DATA_ORDER configuration in the configuration file
	 */
#if SPI_DATA_ORDER == SPI_LSB_FIRST
	SET_BIT(SPCR_REG,DORD_BIT);
#elif SPI_DATA_ORDER == SPI_MSB_FIRST
	CLR_BIT(SPCR_REG,DORD_BIT);
#else
	u8ErrorState = SPI_WRONG_DATA_ORDER_CFG;
#endif

	/*Set the SPI Mode and Configure the SPI PINS */
	if (u8SPIMode == SPI_MASTER)
	{
		//Set the SPI mode to master
		SET_BIT(SPCR_REG,MSTR_BIT);
		//Configure the MOSI pin as output
		SET_BIT(DDRB_REG,DDB5_BIT);
		//Configure the Slave Select pin as output
		SET_BIT(DDRB_REG,DDB4_BIT);
		SET_BIT(PORTB_REG,DDB4_BIT);
		//Configure the SCK pin as output
		SET_BIT(DDRB_REG,DDB7_BIT);

	}else if (u8SPIMode == SPI_SLAVE)
	{
		//Set the SPI mode to Slave
		CLR_BIT(SPCR_REG,MSTR_BIT);
		//Configure the MISO pin as output
		SET_BIT(DDRB_REG,DDB6_BIT);
	}else
	{
		u8ErrorState = SPI_WRONG_MODE;
	}

	/*Check if no error occurred in the previous stages then Enable the SPI with the Written Configurations*/
	if (u8ErrorState==SPI_OK)
	{
		SET_BIT(SPCR_REG,SPE_BIT);
		/*Change the state of the SPI to initialized as MASTER/SLAVE indicating that it is initialized and in this mode*/
		gu8_SPIState = u8SPIMode;
	}
	else
	{
		//if not do nothing
	}

	return u8ErrorState;
}


/**
 * @fn uint8_t SPI_u8SendByte(uint8_t u8Data)
 * @brief This function is used to Send a byte using the SPI peripheral
 * @pre This function require
 * 			- The SPI to be initialized
 */
uint8_t SPI_u8SendByte(uint8_t u8Data)
{
	uint8_t u8ErrorState = SPI_OK;
	uint8_t flush_buffer;
	if (gu8_SPIState!=SPI_NOT_INITIALIZED)//check first if the SPI is initialized
	{
		CLR_BIT(PORTB_REG,DDB4_BIT);
		//Load the Data to the SPI data Register to initiate the transmission
		SPDR_REG = u8Data;
		//Wait until the Transmission is complete
		while (!GET_BIT(SPSR_REG,SPIF_BIT));
		flush_buffer = SPDR_REG;		/* Flush received data */
//		SET_BIT(PORTB_REG,DDB4_BIT);
	}else
	{
		u8ErrorState = SPI_INITIALIZATION_ERROR;
	}
	return u8ErrorState;
}


/**
 * @fn uint8_t SPI_u8SendString(uint8_t* pu8Data)
 * @brief This function is used to Send a String using the SPI peripheral
 * @pre This function require
 * 			- The SPI to be initialized
 * 			- the pu8Data pointer can not points to NULL
 */
uint8_t SPI_u8SendString(uint8_t* pu8Data)
{
	uint8_t u8ErrorState=SPI_OK;
	uint8_t u8CharCounter=0; /// a variable used to navigate the array of the characters

	if (gu8_SPIState!=SPI_NOT_INITIALIZED)// Check first if the SPI is initialized
	{
		if (pu8Data!=NULL) // if it is initialized then check the pointer is not pointing to NULL
		{
			while (pu8Data[u8CharCounter]!='\0')
			{
				//While the current character is not endline
				// Send the character through SPI
				SPI_u8SendByte(pu8Data[u8CharCounter]);
				//check the next character
				u8CharCounter++;
			}
			//After sending the string send endline character indicating the end of the string
			SPI_u8SendByte('\0');

		}else
		{
			// if the input pointer is pointing to NULL update the error state
			u8ErrorState = SPI_NULL_INPUT;
		}

	}else
	{
		// if the SPI is not initialized then update the error state
		u8ErrorState=SPI_INITIALIZATION_ERROR;
	}

	return u8ErrorState;
}


/**
 * @fn uint8_t SPI_u8ReceiveByte(uint8_t* u8Data)
 * @brief This function is used to Receive a byte from the SPI peripheral
 * @pre This function require
 * 			- The SPI to be initialized
 * 			- the pu8Data pointer can not points to NULL
 */
uint8_t SPI_u8ReceiveByte(uint8_t* pu8Data)
{
	uint8_t u8ErrorState = SPI_OK;


	if (gu8_SPIState!=SPI_NOT_INITIALIZED)//check first if the SPI is initialized
	{
		if (pu8Data!=NULL)//Then Check if the pointer is not pointing to a NULL
		{
			//Wait until the Reception is complete
			while (!GET_BIT(SPSR_REG,SPIF_BIT));
			//Load the SPI data Register to the place the pointer holding its address
			*pu8Data = SPDR_REG;
		}else
		{
			u8ErrorState = SPI_NULL_INPUT;
		}

	}else
	{
		u8ErrorState = SPI_INITIALIZATION_ERROR;
	}
	return u8ErrorState;
}


/**
 * @fn uint8_t SPI_u8ReceiveString(uint8_t* pu8Data)
 * @brief This function is used to Receive a String using the SPI peripheral
 * @pre This function require
 * 			- The SPI to be initialized
 * 			- the pu8Data pointer can not points to NULL
 */
uint8_t SPI_u8ReceiveString(uint8_t* pu8Data)
{
	uint8_t u8ErrorState=SPI_OK;
	uint8_t u8CharCounter=0;  /// a variable used to navigate the array of the characters
	uint8_t u8Temp;			/// a variable used to temporarily hold the value of the last character sent

	if (gu8_SPIState!=SPI_NOT_INITIALIZED)// Check first if the SPI is initialized
	{
		if (pu8Data!=NULL)// if it is initialized then check the pointer is not pointing to NULL
		{
			do
			{
				//Receive Byte
				SPI_u8ReceiveByte(&u8Temp);
				//Save the received byte to the first empty place in the array of characters
				pu8Data[u8CharCounter] = u8Temp;
				//update the array navigator
				u8CharCounter++;
			}while (u8Temp!='\0'); // do this until we receive endline character indicating the end of the string

			// save the endline character in the end of the string
			pu8Data[u8CharCounter] = u8Temp;

		}else
		{
			// if the input pointer is pointing to NULL update the error state
			u8ErrorState = SPI_NULL_INPUT;
		}

	}else
	{
		// if the SPI is not initialized then update the error state
		u8ErrorState=SPI_INITIALIZATION_ERROR;
	}

	return u8ErrorState;
}

/**
 * @fn uint8_t SPI_u8EnableInterrupt(void (*pfnCallBack)(void))
 * @brief This function is called to enable the SPI Transmit complete Interrupt
 * @pre - the SPI must be initialized
 * 		- the pointer to function not pointing to NULL
 */
uint8_t SPI_u8EnableInterrupt(void (*pfnCallBack)(void))
{
	uint8_t u8ErrorState = SPI_OK;
	if (gu8_SPIState != SPI_NOT_INITIALIZED)// Check first if the SPI is initialized
	{
		if (pfnCallBack!=NULL)// if it is initialized then check the pointer is not pointing to NULL
		{
			// Set the pointer of the call function to the function address passed by the user
			gpf_SPICallBack = pfnCallBack;
			// Set the Enable bit of the SPI Interrupt
			SET_BIT(SPCR_REG,SPIE_BIT);
			// Set the Enable bit of the Global Interrupt
			SET_BIT(SREG_REG,I_BIT);
		}else
		{
			// if the input pointer is pointing to NULL update the error state
			u8ErrorState = SPI_NULL_INPUT;
		}
	}else
	{
		// if the SPI is not initialized then update the error state
		u8ErrorState = SPI_INITIALIZATION_ERROR;
	}
	return u8ErrorState;

}


/**
 * @fn void SPI_u8DisableInterrupt(void)
 * @brief Used to disable the SPI Interrupt
 */
void SPI_u8DisableInterrupt(void)
{
	// Reset the pointer of the call function to NULL
	gpf_SPICallBack = NULL;
	// Reset the Enable bit of the SPI Interrupt to disable it
	CLR_BIT(SPCR_REG,SPIE_BIT);
}

/**
 * @fn void SPI_u8Deinit(void)
 * @brief This function is called to Stop the SPI Peripheral and De-initialize it
 */
void SPI_u8Deinit(void)
{
	// Disable the SPI capabilities of Receiving and transmitting
	CLR_BIT(SPCR_REG,SPE_BIT);
	//Reset the pointer to the callback function to NULL
	gpf_SPICallBack = NULL;
	// Clear the Enable bit of the SPI Interrupt
	CLR_BIT(SPCR_REG,SPIE_BIT);
	// Reset the Initialization flag indicating that the SPI is not initialized anymore
	gu8_SPIState = SPI_NOT_INITIALIZED;

}


void SPI_u8ReceiveInt(uint32_t* pu8Data)
{

	IntData_t Received;
	SPI_u8ReceiveByte(&Received.u8Bytes[3]);
	//UART_u8SendByte(Received.u8Bytes[0]);
	SPI_u8ReceiveByte(&Received.u8Bytes[2]);
	//UART_u8SendByte(Received.u8Bytes[1]);
	SPI_u8ReceiveByte(&Received.u8Bytes[1]);
	//UART_u8SendByte(Received.u8Bytes[2]);
	SPI_u8ReceiveByte(&Received.u8Bytes[0]);
	//UART_u8SendByte(Received.u8Bytes[3]);
	*pu8Data = Received.num;
}


void SPI_u8SendInt(uint32_t u32Data){

	IntData_t New;
	uint8_t Byte1 = (u32Data);
	uint8_t Byte2 = (u32Data>>8);
	uint8_t Byte3 = (u32Data>>16);
	uint8_t Byte4 = (u32Data>>24);

	New.num=u32Data;
	UART_u8SendByte(u32Data);
	UART_u8SendInt(New.u8Bytes[3]);
	SPI_u8SendByte(New.u8Bytes[3]);
	SPI_u8SendByte(New.u8Bytes[2]);
	SPI_u8SendByte(New.u8Bytes[1]);
	SPI_u8SendByte(New.u8Bytes[0]);
}

/**
 * @brief the SPI Interrupt ISR
 */
void __vector_12(void) {

	if (gpf_SPICallBack!=NULL) // check if the pointer to the Callback is pointing to NULL
	{
		//if not then call the function pointing to it
		gpf_SPICallBack();
	}
}

