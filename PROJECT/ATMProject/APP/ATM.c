/*
 * ATM.c
 *
 *  Created on: Jan 28, 2022
 *      Author: Alhassan Mohsen
 */

#include "ATM_prv.h"
#include "ATM.h"

static volatile ATMModes_t gu8_ATMMode= ATM_START;
static volatile uint8_t LastAccountPtr;
static volatile uint32_t gu8_MaxAmount;
static volatile uint16_t u16BalanceAddress;
BTN_t CardBTN={PORTB,PIN0};
TEMPElement_t TempSensor={PORTA,PIN0};

//static volatile uint8_t gu8_ATMPollingReadFlag = 0;

void ATM_Init(void)
{
	// DIO_u8SetPinDirection(PORTB, PIN4, DIO_OUTPUT);
	// DIO_u8SetPinDirection(PORTB, PIN5, DIO_OUTPUT);
	// DIO_u8SetPinDirection(PORTB, PIN6, DIO_INPUT);
	// DIO_u8SetPinDirection(PORTB, PIN7, DIO_OUTPUT);


	// configure the Interrupt pin that will be used to ask for the card data
	DIO_u8SetPinDirection(PORTB,PIN2,DIO_OUTPUT);
	DIO_u8SetPinData(PORTB, PIN2, DIO_LOW);
	//Initiate the SPI in slave mode where the terminal is asking for the data when needed through an Interrupt PIN
	SPI_u8Init(SPI_SLAVE);
	///TIMER0_u8PollingDelay(10);
	// Initiate UART communication between the ATM and the user through terminal
	UART_u8Init(ATM_UART_BAUDRATE);

	//Initiate Temperature Sensor
	TEMP_u8Init();

	//Make the UART Update the Operating mode when the operation is interrupted by typing on the termincal
	UART_u8EnableRecievingInterrupt(ATM_UpdateMode);
	//Initiate the Communication with the EEPROM which acts as the Bank Servers
	EEPROM_Init();
	//Initiate the Communication with LCD and Keypad as User Interface
	LCD_u8Init();
	KEYPAD_u8Init();
	//Initiate Card Button which emulate the task of the card reader
	BTN_u8Init(CardBTN);


#ifdef EEPROM_RESET
	// if the EEPROM is in RESET mode Clear All the data saved on it by restoring the Data Pointer to its start location
	EEPROM_u8WriteStringTo(ATM_EEPROM_ADDRESS,ATM_EEPROM_PTR,ATM_DATA_START_ADDRESS);

#endif

	// Read the data from tha address ATM_EEPROM_FIRST_TIME_ADDRESS and check if it contain the ATM_EEPROM_FIRST_TIME_DATA
	//This mean that this EEPROM is used and initialized before so the user can fetch the data from it directly
	EEPROM_u8RandonReadFrom(ATM_EEPROM_ADDRESS,ATM_EEPROM_FIRST_TIME_ADDRESS,&LastAccountPtr);

	if (LastAccountPtr!=ATM_EEPROM_FIRST_TIME_DATA)
	{
		// if it doesn't contain ATM_EEPROM_FIRST_TIME_DATA Byte in this location then this is the first use

		//Write the ATM_EEPROM_FIRST_TIME_DATA to the address so it is flagged as used before
		EEPROM_u8WriteByteTo(ATM_EEPROM_ADDRESS,ATM_EEPROM_FIRST_TIME_ADDRESS,ATM_EEPROM_FIRST_TIME_DATA);
		// Let the Data Start Address is saved in a memory location of the Last Data saved Pointer so it points to the beginning of the EEPROM Data segment
		EEPROM_u8WriteByteTo(ATM_EEPROM_ADDRESS,ATM_EEPROM_PTR,ATM_DATA_START_ADDRESS);
	}else{

		//if it is used before then go and fetch the location of the last data address available
		EEPROM_u8RandonReadFrom(ATM_EEPROM_ADDRESS,ATM_EEPROM_PTR,&LastAccountPtr);
		// and fetch the max amount of the ATM
		EEPROM_u8ReadIntFrom(ATM_EEPROM_ADDRESS,ATM_MAX_AMOUNT_LOCATION,&gu8_MaxAmount);
		//if the Last address available is the ATM_DATA_END_ADDRESS this means that ATM has reached it's maximum capacity and it will overrun
		if (LastAccountPtr>=ATM_DATA_END_ADDRESS)
		{
			UART_u8SendString("EEPROM RESET\n");
			EEPROM_u8WriteByteTo(ATM_EEPROM_ADDRESS,ATM_EEPROM_PTR,ATM_DATA_START_ADDRESS);
			LastAccountPtr = ATM_DATA_START_ADDRESS;
		}
	}
	//Fetch the ATM ADMIN Mode password from the EEPROM
	EEPROM_u8WriteStringTo(ATM_EEPROM_ADDRESS,ATM_PASSWORD_LOCATION,ATM_ADMIN_PASSWORD);

}

void ATM_APP(void)
{

	uint8_t u8PasswordCheck; 					 /// a variable used to hold the result of the entered password checking
	uint8_t u8UserInput;				  		 /// used to hold the inputs of the user interface modules
	uint8_t au8CardPAN[9];					     /// an array that will receive the card PAN through SPI
	uint32_t u32CardPAN; 						 // card PAN after converted to an integer number
	uint8_t au8CardPIN[4]; 						 // an array that will receive the card PIN through SPI
	uint8_t u8CardMode=CARD_ACCESSIBLE; 		 // a variable represent the card accessibility (Card can be inaccessible if it is in ADMIN mode
	uint32_t u32UserBalance;					 // a variable that hold the user balance as stored on the server side
	uint8_t u8AccountAvailability;			     // A variable represent if the card PAN is registered on the server or not
	uint32_t u32InputAmount ;					 // integer number represent the user input to amount of money he want to withdraw
	uint8_t au8TerminalCommand[10];				 // an array to hold the user input to terminal
	uint16_t u16TemperatureReading;				// Variable to hold the Temperature Reading
	while (1)
	{
		// Check the mode of the ATM
		switch (gu8_ATMMode)
		{
		case ATM_START:

			// if it is in the START mode Do nothing until the Terminal input some state to operate in
			break;
		case ATM_PROGRAMMING_MODE:
			//if the input state is ATM_PROGRAMMING_MODE

			//First disable the interrupt because now the inteface is done through UART terminal
			UART_u8DisableReceivingInterrupt();
			// Display on the ATM LCD that the LCD is in ADMIN Mode
			LCD_u8SendString((uint8_t*)"ADMIN MODE\r\n");
			// Ask for the ADMIN password and check correctness
			ATM_CheckPassword(&u8PasswordCheck);
			if (u8PasswordCheck==ATM_PASSWORD_OK)
			{
				//if the Password is right
				do{
					//display the ADMIN menu
					UART_u8SendString((uint8_t*)"\r\n 1- Add Customer Data \n");
					UART_u8SendString((uint8_t*)"\r\n 2- Edit the Max Amount \n");
					UART_u8SendString((uint8_t*)"\r\n 3- Exit \r\n");
					// get the Choice
					UART_u8ReceiveByte(&u8UserInput);

					//check what choice it is and implement its logic
					if (u8UserInput==ATM_ADMIN_ADD_CUSTOMER)
					{
						ATM_AddNewAccount();

					}else if (u8UserInput==ATM_ADMIN_MAX_AMOUNT)
					{
						ATM_AddMaxAmount();
					}else if (u8UserInput==ATM_ADMIN_EXIT)
					{
						UART_u8SendString((uint8_t*)"\r\n Thank You!! \r\n");
						gu8_ATMMode=ATM_OPERATION_MODE;
					}
					else
					{
						// if other input is entered display a error message
						UART_u8SendString((uint8_t*)"\r\n Wrong Input \r\n");
					}

					// do this until the user choose EXIT
				}while ((u8UserInput!=ATM_ADMIN_EXIT));

			}else if (u8PasswordCheck==ATM_PASSWORD_NOK){
				// if the Entered Password is wrong display an error message then exit to Operation mode
				UART_u8SendString((uint8_t*)"\r\n Wrong Password \r\n");
			}

			// After finishing convert the mode to Operation mode
			gu8_ATMMode=ATM_OPERATION_MODE;

			//Enable the interrupts again (now the interface is done using UI module not the UART terminal
			UART_u8EnableRecievingInterrupt(ATM_UpdateMode);
			break;

		case ATM_OPERATION_MODE:
			//if the current mode of the ATM is OPERATION MODE

			LCD_u8SendCommand(LCD_CLEAR);
			LCD_u8SendString((uint8_t*)"Welcome......");
			LCD_u8SetCursor(ATM_LCD_SECOND_ROW);
			LCD_u8SendString((uint8_t*)"Insert Your Card");
			//Wait until a Card is present and the Card button is pressed
			do{
				BTN_u8IsPressed(CardBTN,&u8UserInput);
			}while(u8UserInput&&gu8_ATMMode!=ATM_PROGRAMMING_MODE);


			while (!u8UserInput&&gu8_ATMMode!=ATM_PROGRAMMING_MODE)
			{// While the card is present and there is no ADMIN command sent through the UART terminal

				//First Get PAN Number from the Card using SPI channel
				ATM_GetCardData(au8CardPAN);
				//Check if the card send the string INACCESSIBLE
				if(STR_CMP(au8CardPAN,(uint8_t*)"INACCESSIBLE"))
				{
					UART_u8SendString("INACCESSIBLE");
					//if it is sent then the card is not available to be used (may be the card is in Programming mode)
					u8CardMode=CARD_INACCESSIBLE;
				}else
				{
					//if the card sent another strings then the car is accessible and the Received String is the PAN
					u8CardMode=CARD_ACCESSIBLE;
					//Convert the PAN to integer to save it in the EEPROM in a searchable format
					StringToInt(au8CardPAN,&u32CardPAN);
					UART_u8SendInt(u32CardPAN);
					//UART_u8SendByte(0x0D);
					//UART_u8SendInt(u32CardPAN); //1
					//UART_u8SendByte(0x0D);

					// Get the second String from the Card which Represent the PIN Number
					ATM_GetCardData(au8CardPIN);
					//UART_u8SendByte(0x0D);
					//UART_u8SendString((uint8_t*)"PIN:  ");
					//UART_u8SendString(au8CardPIN);

					// Check if the PAN number exist in the Server side or not and if exist return the Account Balance
					ATM_GetBalance(u32CardPAN,&u32UserBalance,&u8AccountAvailability);
					//UART_u8SendByte(0x0D);
					//UART_u8SendInt(u8AccountAvailability);
					//UART_u8SendByte(0x0D);
				}

				// if the card is Accessible
				if (u8CardMode==CARD_ACCESSIBLE)
				{
					// and the PAN exist in the Bank Servers
					if(u8AccountAvailability==1)
					{
						do{
							//Display the user menu on the ATM LCD interface
							LCD_u8SendCommand(LCD_CLEAR);
							LCD_u8SendString((uint8_t*)"1- WITHDRAW CASH");
							LCD_u8SetCursor(ATM_LCD_SECOND_ROW);
							LCD_u8SendString((uint8_t*)"2- Get Temp");

							// busy wait until you Get the Customer choice
							do
							{
								KEYPAD_u8GetPressedKey(&u8UserInput);
							}while(u8UserInput==KEYPAD_NO_PRESSED_KEY && gu8_ATMMode!=ATM_PROGRAMMING_MODE);


							if( u8UserInput == ATM_INSERT_CARD)
							{
								// if the user choose to insert a card then clear the lcd and ask him to enter the password of the Card
								LCD_u8SendCommand(LCD_CLEAR);
								LCD_u8SendString((uint8_t*)"Enter PIN: ");
								LCD_u8SetCursor(ATM_LCD_SECOND_ROW);

								// Get the entered PIN and check if the Input PIN match the received Card PIN
								ATM_GetPass(au8CardPIN,&u8PasswordCheck);

								//UART_u8SendString(au8CardPIN);

								if (u8PasswordCheck==ATM_PASS_RIGHT)
								{
									// if the Input PIN is right clear the LCD and ask to enter an amount
									LCD_u8SendCommand(LCD_CLEAR);
									LCD_u8SendString((uint8_t*)"Your Amount : ");
									LCD_u8SetCursor(ATM_LCD_SECOND_ROW);

									ATM_GetAmmount(&u32InputAmount);

									if (u32InputAmount>gu8_MaxAmount)
									{
										LCD_u8SendCommand(LCD_CLEAR);
										LCD_u8SendString((uint8_t*)"Max Amount is: ");
										LCD_u8SetCursor(ATM_LCD_SECOND_ROW);
										LCD_u8SendNumber(gu8_MaxAmount);
										TIMER0_u8PollingDelay(ATM_LCD_DISPLAY_TIME);
									}else if(u32InputAmount<=u32UserBalance)
									{
										//if it is then clear Display and print operation Done
										LCD_u8SendCommand(LCD_CLEAR);
										LCD_u8SendString((uint8_t*)"Operation Done");
										u32UserBalance= u32UserBalance-u32InputAmount;
										EEPROM_u8WriteIntTo(ATM_EEPROM_ADDRESS,u16BalanceAddress,u32UserBalance);
										TIMER0_u8PollingDelay(ATM_LCD_DISPLAY_TIME);
										LCD_u8SendCommand(LCD_CLEAR);
										LCD_u8SendString((uint8_t*)"New Balance");
										LCD_u8SetCursor(ATM_LCD_SECOND_ROW);
										LCD_u8SendNumber(u32UserBalance);
										TIMER0_u8PollingDelay(ATM_LCD_DISPLAY_TIME);


									}else
									{
										// if not then clear Display and print No Credit fot 5 seconds
										LCD_u8SendCommand(LCD_CLEAR);
										LCD_u8SendString((uint8_t*)"No Credit");
										TIMER0_u8PollingDelay(ATM_LCD_DISPLAY_TIME);
									}
									//Check if the Input Amount is less than or equal to the available balance in the account



								}else
								{
									// if the PIN entered is not right then display wrong PIN for 5 seconds
									LCD_u8SendCommand(LCD_CLEAR);
									LCD_u8SendString((uint8_t*)"Wrong PIN");
									TIMER0_u8PollingDelay(ATM_LCD_DISPLAY_TIME);
								}

							}else if(u8UserInput==ATM_GET_TEMP)
							{// if the user chose to print the current temperature

								//Get the sensor Reading
								TEMP_u8GetRead(&TempSensor,&u16TemperatureReading);
								//Clear the LCD and print the reading Value for 5 seconds
								LCD_u8SendCommand(LCD_CLEAR);
								LCD_u8SendNumber(500);
								TIMER0_u8PollingDelay(ATM_LCD_DISPLAY_TIME);
							}

							KEYPAD_u8GetPressedKey(&u8UserInput);
						}while(u8UserInput==KEYPAD_NO_PRESSED_KEY&&gu8_ATMMode!=ATM_PROGRAMMING_MODE);


					}else{

						// if the card PAN is not on the Bank servers then clear display and inform the user that card is expired
						LCD_u8SendCommand(LCD_CLEAR);
						LCD_u8SendString((uint8_t*)"Card Expired");
						TIMER0_u8PollingDelay(ATM_LCD_DISPLAY_TIME);
					}

				}else
				{
					//if the card replied with inaccessible then the card is not available to be used
					UART_u8SendString((uint8_t*)"Card Inaccessible");
					LCD_u8SendString((uint8_t*)"Card Inaccessible");
					TIMER0_u8PollingDelay(ATM_LCD_DISPLAY_TIME);
				}

				//update the state of the card button to check if it still exist
				//if the card still exist and the programming mode is not entered using terminal then do the same sequence again
				BTN_u8IsPressed(CardBTN,&u8UserInput);
			}


			//UART_u8EnableRecievingInterrupt(ATM_UpdateMode);
			break;
		case ATM_WRONG_MODE_INPUT:

			UART_u8DisableReceivingInterrupt();
			do{

				UART_u8SendString((uint8_t*)"Wrong Input Please Enter either ADMIN or USER\r\n");

				UART_u8RecieveString(au8TerminalCommand);
				if (STR_CMP(au8TerminalCommand,(uint8_t*)"ADMIN"))
				{
					// check if the command received is ADMIN then set the ATM mode to ATM_PROGRAMMING_MODE
					gu8_ATMMode = ATM_PROGRAMMING_MODE;
				}else if(STR_CMP(au8TerminalCommand,(uint8_t*)"USER"))
				{
					// check if the command received is USER then set the ATM mode to ATM_OPERATION_MODE
					gu8_ATMMode = ATM_OPERATION_MODE;
				}
			}while (gu8_ATMMode==ATM_WRONG_MODE_INPUT);

			UART_u8EnableRecievingInterrupt(ATM_UpdateMode);
			break;
		default:
			UART_u8SendString((uint8_t*)"Wrong Entry \r\n");

		}


	}
}


void ATM_GetCardData(uint8_t* pu8_DataPlace)
{
	//UART_u8SendString("GetData");
	// Send an interrupt signal to the card ecu to request the beginning of the transmission on the SPI Channel
	DIO_u8SetPinData(PORTB, PIN2, DIO_HIGH);
	//Receive the data from the SPI channel and save it in the passed variable
	SPI_u8ReceiveString(pu8_DataPlace);
	//Return the interrupt pin to its original state
	DIO_u8SetPinData(PORTB, PIN2, DIO_LOW);
}

void ATM_UpdateMode(void)
{

		uint8_t au8TerminalCommand[10];		// array to hold the command entered on the terminal

		// Receive the command
		UART_u8RecieveString(au8TerminalCommand);

		if (STR_CMP(au8TerminalCommand,(uint8_t*)"ADMIN"))
		{
			// check if the command received is ADMIN then set the ATM mode to ATM_PROGRAMMING_MODE
			gu8_ATMMode = ATM_PROGRAMMING_MODE;
		}else if(STR_CMP(au8TerminalCommand,(uint8_t*)"USER"))
		{
			// check if the command received is USER then set the ATM mode to ATM_OPERATION_MODE
			gu8_ATMMode = ATM_OPERATION_MODE;
		}else
		{
			// check if the command received is not one the two then set the ATM mode to ATM_WRONG_MODE_INPUT
			gu8_ATMMode =ATM_WRONG_MODE_INPUT;
		}

}

void ATM_CheckPassword(uint8_t* pu8CheckResult)
{
	uint8_t au8UserPassword[4];
	uint8_t u8PasswordReading;
	uint8_t RightPasswordCounter=0;

	UART_u8SendString((uint8_t*)"Please Enter ADMIN Password: \r\n");
	for (uint8_t i=0;i<4;i++)
	{
		//gu8_ATMPollingReadFlag=1;
		UART_u8ReceiveByte(&au8UserPassword[i]);
		EEPROM_u8RandonReadFrom(ATM_EEPROM_ADDRESS,(ATM_PASSWORD_LOCATION+i),&u8PasswordReading);
		if (au8UserPassword[i]==u8PasswordReading)
		{
			RightPasswordCounter++;
		}else {
			//NOP
		}
	}
	if (RightPasswordCounter==4)
	{
		*pu8CheckResult=ATM_PASSWORD_OK;
	}else
	{
		*pu8CheckResult=ATM_PASSWORD_NOK;
	}
//	gu8_ATMPollingReadFlag=0;

}

void ATM_AddNewAccount()
{
	uint32_t u8customerData;
	uint8_t u8UserInput='y';
	while (u8UserInput!='n')
	{


		UART_u8SendString((uint8_t*)"\r\n Please Enter the PAN: \r\n");
		UART_u8ReceiveInt(&u8customerData);
		EEPROM_u8WriteIntTo(ATM_EEPROM_ADDRESS,LastAccountPtr,u8customerData);
		LastAccountPtr+=4;



		UART_u8SendString((uint8_t*)"\r\n Please Enter the Balance: \r\n");
		UART_u8ReceiveInt(&u8customerData);
		EEPROM_u8WriteIntTo(ATM_EEPROM_ADDRESS,LastAccountPtr,u8customerData);
		LastAccountPtr+=4;


		UART_u8SendString((uint8_t*)"\r\n Enter new Account(y/n) \r\n");
		UART_u8ReceiveByte(&u8UserInput);
	}
	TIMER0_u8PollingDelay(10);
	EEPROM_u8WriteByteTo(ATM_EEPROM_ADDRESS,ATM_EEPROM_PTR,LastAccountPtr);

}

void ATM_AddMaxAmount()
{
	uint32_t u8UserInput;
	uint32_t u32MaxAmount;
	//uint8_t u8Counter=0;
	UART_u8SendString((uint8_t*)"\r\n Please Enter the Max Amount: \r\n");
	UART_u8ReceiveInt(&u32MaxAmount);
	EEPROM_u8WriteIntTo(ATM_EEPROM_ADDRESS,ATM_MAX_AMOUNT_LOCATION,u32MaxAmount);


	UART_u8SendString((uint8_t*)"\r\n The new Max Amount is : \r\n");
	EEPROM_u8ReadIntFrom(ATM_EEPROM_ADDRESS,ATM_MAX_AMOUNT_LOCATION,&u8UserInput);
	UART_u8SendInt(u8UserInput);
}


uint8_t ATM_GetPass(uint8_t * Pass_int,uint8_t* pu8PasswordCheck)
{

	uint8_t u8ErrorState = STD_TYPES_OK ;
	uint8_t index = 0 ;
	uint8_t u8PressedKey = KEYPAD_NO_PRESSED_KEY ;

	while( index < 4 )
	{
		u8PressedKey = KEYPAD_NO_PRESSED_KEY ;
		while ( u8PressedKey == KEYPAD_NO_PRESSED_KEY )
		{
			if ( KEYPAD_u8GetPressedKey(&u8PressedKey) != STD_TYPES_OK )
			{
				u8ErrorState = STD_TYPES_NOK ;
			}
			if ( ( u8PressedKey < 0 ) || ( u8PressedKey > 9 ) )
			{
				u8ErrorState = STD_TYPES_NOK ;
			}
			if ( ( u8PressedKey >= 0 ) && ( u8PressedKey <= 9 ) )
			{
				if (u8PressedKey+'0'==Pass_int[index])
				{
					index++;
				}else
				{
					LCD_u8SendString((uint8_t*)"Wrong PIN");
					index=255;
				}
				//Pass_int[index] = u8PressedKey ;


				if ( LCD_u8SendData('*') != STD_TYPES_OK )
				{
					u8ErrorState = STD_TYPES_NOK ;
				}

			 }
		  }
	}
	if ( index == 4 )
	{
		*pu8PasswordCheck=1;
		//Pass_int[index]= '\0' ;
		//*Pass_int = StringToInt( Pass ) ;
	}else{
		*pu8PasswordCheck=0;
	}
	return u8ErrorState ;
}

uint8_t ATM_GetAmmount( uint32_t * Ammount_int )
{
	uint8_t u8ErrorState = STD_TYPES_OK ;
	uint8_t Ammount[100] = {"50.5"} ;
	uint8_t index = 0 ;
	uint8_t u8PressedKey = KEYPAD_NO_PRESSED_KEY ;
	while ( u8PressedKey != 'E' )
	{
		if ( KEYPAD_u8GetPressedKey(&u8PressedKey) != STD_TYPES_OK )
		{
			u8ErrorState = STD_TYPES_NOK ;
		}
		if ( ( u8PressedKey < 0 ) || ( u8PressedKey > 9 ) )
		{
			u8ErrorState = STD_TYPES_NOK ;
		}
		if ( ( u8PressedKey >= 0 ) && ( u8PressedKey <= 9 ) )
		{
			Ammount[index] = u8PressedKey + '0' ;
			if ( LCD_u8SendData(Ammount[index]) != STD_TYPES_OK )
			{
				u8ErrorState = STD_TYPES_NOK ;
			}
			index++;
		}
	}
	Ammount[index] = '\0';
	StringToInt(Ammount,Ammount_int);
	//UART_u8SendString()

	return u8ErrorState ;
}

uint8_t ATM_GetBalance(uint32_t u32UserPAN,uint32_t* u32UserBalance, uint8_t* u8CardState)
{
	uint32_t u32CompareVal=0;
	uint16_t u32MemNav = ATM_DATA_START_ADDRESS;
	uint32_t temp;
	*u8CardState = 1;
	while (u32CompareVal!=u32UserPAN && u32MemNav!=ATM_DATA_END_ADDRESS)
	{
		EEPROM_u8ReadIntFrom(ATM_EEPROM_ADDRESS,u32MemNav,&u32CompareVal);
		u32MemNav+=4;
		EEPROM_u8ReadIntFrom(ATM_EEPROM_ADDRESS,u32MemNav,u32UserBalance);
		u32MemNav+=4;
	}
	if (u32MemNav==ATM_DATA_END_ADDRESS)
	{
		*u8CardState=0;
	}else
	{
		u16BalanceAddress=u32MemNav-4;
	}
}
