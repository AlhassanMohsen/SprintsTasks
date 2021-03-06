/*
 * DIO.c
 *
 *  Created on: Jan 8, 2022
 *      Author: Alhassan Mohsen
 */


#include "DIO_interface.h"


/**
 * @fn ErrorState_t DIO_u8SetPinDirection(DIOPort_t u8_PortName,DIOPin_t u8_PinNum,DIODir_t u8_PinDir)
 * @brief this function used to choose the pin direction
 * @param u8_PortName : The port where the pin exist can be one of the following
 * PORTA
 * PORTB
 * PORTC
 * PORTD
 * @param u8_PinNum : The number of the pin
 * PIN0
 * PIN1
 * PIN2
 * PIN3
 * PIN4
 * PIN5
 * PIN6
 * PIN7
 * @param u8_PinDir : the Direction you want the pin to be on
 * DIO_INPUT
 * DIO_INPUT_PULLUP
 * DIO_OUTPUT
 * @return The return is an uint8_t number represent the error state of the function and can be
 *  255 : Wrong PIN Number
 *  254 : Wrong PORT Number
 *  253:  Wrong Direction
 */
DIO_ErrorState_t DIO_u8SetPinDirection(DIOPort_t u8_PortName,DIOPin_t u8_PinNum,DIODir_t u8_PinDir)
{
	DIO_ErrorState_t u8ErrorState= DIO_OK;

	/*Check if the inputs are in the right range*/
	if (u8_PinNum<DIO_PINS_NUMBER)
	{
		/*Check which port */
		switch (u8_PortName)
		{
			case PORTA:
				/*Check which Direction the user wants the pin to be in */
				switch (u8_PinDir)
				{
				case DIO_INPUT:
					// for input tristate mode ({DDxn, PORTxn} = 0b00)
					CLR_BIT(DDRA_REG,u8_PinNum);
					CLR_BIT(PORTA_REG,u8_PinNum);
					break;
				case DIO_INPUT_PULLUP:
					// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
					CLR_BIT(SFIOR_REG,PUD_BIT);
					CLR_BIT(DDRA_REG,u8_PinNum);
					SET_BIT(PORTA_REG,u8_PinNum);
					break;
				case DIO_OUTPUT:
					// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
					SET_BIT(DDRA_REG,u8_PinNum);
					break;
				default:
					// If the input state is not one of the above cases return error state NOK
					u8ErrorState= WRONG_DIR;
				}
				break;
			case PORTB:
				/*Check if the inputs are in the right range*/
				switch (u8_PinDir)
				{
				case DIO_INPUT:
					// for input tristate mode ({DDxn, PORTxn} = 0b00)
					CLR_BIT(DDRB_REG,u8_PinNum);
					CLR_BIT(PORTB_REG,u8_PinNum);
					break;
				case DIO_INPUT_PULLUP:
					// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
					CLR_BIT(SFIOR_REG,PUD_BIT);
					CLR_BIT(DDRB_REG,u8_PinNum);
					SET_BIT(PORTB_REG,u8_PinNum);
					break;
				case DIO_OUTPUT:
					// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
					SET_BIT(DDRB_REG,u8_PinNum);
					break;
				default:
					// If the input state is not one of the above cases return error state NOK
					u8ErrorState= WRONG_DIR;
				}
				break;
			case PORTC:
				switch (u8_PinDir)
				{
				case DIO_INPUT:
					// for input tristate mode ({DDxn, PORTxn} = 0b00)
					CLR_BIT(DDRC_REG,u8_PinNum);
					CLR_BIT(PORTC_REG,u8_PinNum);
					break;
				case DIO_INPUT_PULLUP:
					// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
					CLR_BIT(SFIOR_REG,PUD_BIT);
					CLR_BIT(DDRC_REG,u8_PinNum);
					SET_BIT(PORTC_REG,u8_PinNum);
					break;
				case DIO_OUTPUT:
					// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
					SET_BIT(DDRC_REG,u8_PinNum);
					break;
				default:
					// If the input state is not one of the above cases return error state NOK
					u8ErrorState= WRONG_DIR;
				}
				break;
			case PORTD:
				switch (u8_PinDir)
				{
				case DIO_INPUT:
					// for input tristate mode ({DDxn, PORTxn} = 0b00)
					CLR_BIT(DDRD_REG,u8_PinNum);
					CLR_BIT(PORTA_REG,u8_PinNum);
					break;
				case DIO_INPUT_PULLUP:
					// for input PULLUP mode ({DDxn, PORTxn,PUD} = 0b010)
					CLR_BIT(SFIOR_REG,PUD_BIT);
					CLR_BIT(DDRD_REG,u8_PinNum);
					SET_BIT(PORTD_REG,u8_PinNum);
					break;
				case DIO_OUTPUT:
					// for OUTPUT mode ({DDxn, PORTxn} = 0b1x)
					SET_BIT(DDRD_REG,u8_PinNum);
					break;
				default:
					// If the input state is not one of the above cases return error state NOK
					u8ErrorState= WRONG_DIR;
				}
				break;
			default:
				// If the input port is not one of the above cases return error state NOK
				u8ErrorState= WRONG_PORT;
		}
	}else{
		// If the input port or input pin is not suitable return error state NOK
		u8ErrorState= WRONG_PIN;
	}
	return u8ErrorState;
}

/**
 * @fn   ErrorState_t DIO_u8SetPinData (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,DIODir_t u8_PinValue)
 * @brief this function is used to output on a chosen pin
 * @param u8_PortName : The port where the pin exist can be one of the following
 * PORTA
 * PORTB
 * PORTC
 * PORTD
 * @param u8_PinNum : The number of the pin
 * PIN0
 * PIN1
 * PIN2
 * PIN3
 * PIN4
 * PIN5
 * PIN6
 * PIN7
 * @param u8_PinValue
 * DIO_HIGH
 * DIO_LOW
 * @return a number between 0 - 255 represent the Error state of the function
 *  255 : Wrong PIN Number
 *  254 : Wrong PORT Number
 *  251:  Wrong Value
 */
DIO_ErrorState_t DIO_u8SetPinData (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,uint8_t u8_PinValue)
{
	DIO_ErrorState_t u8ErrorState = DIO_OK;
	if (u8_PinNum < DIO_PINS_NUMBER)
	{
		/*Check which port */
		switch(u8_PortName)
		{
		case PORTA:
			switch(u8_PinValue)
			{
			// set or clear bit depend on PinValue
			case DIO_HIGH:
				SET_BIT(PORTA_REG,u8_PinNum);
				break;
			case DIO_LOW:
				CLR_BIT(PORTA_REG,u8_PinNum);
				break;
			default:
				// If not HIGH or LOW return error state WRONG_VALUE
				u8ErrorState = WRONG_VALUE;
			}
			break;
		case PORTB:
			switch(u8_PinValue)
			{
			// set or clear bit depend on PinValue
			case DIO_HIGH:
				SET_BIT(PORTB_REG,u8_PinNum);
				break;
			case DIO_LOW:
				CLR_BIT(PORTB_REG,u8_PinNum);
				break;
			default:
				// If not HIGH or LOW return error state WRONG_VALUE
				u8ErrorState = WRONG_VALUE;
			}
			break;
		case PORTC:
			switch(u8_PinValue)
			{
			// set or clear bit depend on PinValue
			case DIO_HIGH:
				SET_BIT(PORTC_REG,u8_PinNum);
				break;
			case DIO_LOW:
				CLR_BIT(PORTC_REG,u8_PinNum);
				break;
			default:
				// If not HIGH or LOW return error state WRONG_VALUE
				u8ErrorState = WRONG_VALUE;
			}
			break;
		case PORTD:
			switch(u8_PinValue)
			{
			// set or clear bit depend on PinValue
			case DIO_HIGH:
				SET_BIT(PORTD_REG,u8_PinNum);
				break;
			case DIO_LOW:
				CLR_BIT(PORTD_REG,u8_PinNum);
				break;
			default:
			 	// If not HIGH or LOW return error state WRONG_VALUE
				u8ErrorState = WRONG_VALUE;
			}
			break;
		default :
			// if the input port is not one of the previous return the Error State WRONG_PORT
			u8ErrorState = WRONG_PORT;
		}
	}else
	{
		// if not suitable pin state return error state WRONG_PIN
		u8ErrorState = WRONG_PIN;
	}
	return u8ErrorState;
}

/**
 * @fn ErrorState_t DIO_u8GetPinData (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,uint8_t* pu8_ReturnVar)
 * @brief This function is used to get the state of the pin when it is configured as input
 * @param u8_PortName : The port where the pin exist can be one of the following
 * PORTA
 * PORTB
 * PORTC
 * PORTD
 * @param u8_PinNum : The number of the pin
 * PIN0
 * PIN1
 * PIN2
 * PIN3
 * PIN4
 * PIN5
 * PIN6
 * PIN7
 * @param pu8_ReturnVar this is a pointer to a unsigned integer to hold the pin state
 * @return returns a number from 0 - 255 represent the Error State
 *  255 : Wrong PIN Number
 *  254 : Wrong PORT Number
 *  252 : The input pointer is not pointing to a valid memory place
 */
DIO_ErrorState_t DIO_u8GetPinData (DIOPort_t u8_PortName,DIOPin_t u8_PinNum,uint8_t* pu8_ReturnVar)
{
	DIO_ErrorState_t u8ErrorState=DIO_OK;

	if (u8_PinNum < DIO_PINS_NUMBER && pu8_ReturnVar != NULL )
	{
		if (u8_PinNum < DIO_PINS_NUMBER)
		{
			switch (u8_PortName)
			{
			// get bit value in register to variable depend on port and pin
			case PORTA:
				*pu8_ReturnVar = GET_BIT(PINA_REG,u8_PinNum);
				break;
			case PORTB:
				*pu8_ReturnVar = GET_BIT(PINB_REG,u8_PinNum);
				break;
			case PORTC:
				*pu8_ReturnVar = GET_BIT(PINC_REG,u8_PinNum);
				break;
			case PORTD:
				*pu8_ReturnVar=GET_BIT(PIND_REG,u8_PinNum);
				break;
			default:
				// if not suitable port return error state NOK
				u8ErrorState=WRONG_PORT;
			}
		}else{
			// if the PIN chosen is out of range return the Error state as WRONG_PIN
			u8ErrorState=WRONG_PIN;
		}

	}else
	{
		// if return address not passed return error state NULL_PTR
		u8ErrorState=NULL_PTR;
	}

	return u8ErrorState;
}

/**
 * @fn ErrorState_t DIO_u8SetPortDirection(DIOPort_t u8_PortName,DIODir_t u8_Dir)
 * @brief this function is used to set the direction for a complete DIO Port
  * @param u8_PortName : The port where the pin exist can be one of the following
 * PORTA
 * PORTB
 * PORTC
 * PORTD
 * @param u8_Dir : the Direction you want the pin to be on
 * DIO_INPUT
 * DIO_INPUT_PULLUP
 * DIO_OUTPUT
 * @return return a number between 0 - 255 represent the Error State
 *  254 : Wrong PORT Number
 *  253:  Wrong Direction
 */
DIO_ErrorState_t DIO_u8SetPortDirection(DIOPort_t u8_PortName,DIODir_t u8_Dir)
{
	DIO_ErrorState_t u8ErrorState=DIO_OK;
	switch (u8_PortName)
	{
	case PORTA:
		switch (u8_Dir)
		{
		case DIO_INPUT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRA_REG = DIO_PORT_LOW;
			SET_BIT(SFIOR_REG,PUD_BIT);
			break;
		case DIO_INPUT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG,PUD_BIT);
			DDRA_REG =  DIO_PORT_LOW;
			PORTA_REG = DIO_PORT_HIGH;
			break;
		case DIO_OUTPUT:
			// for input tristate mode ( DDRx = 0xff )
			DDRA_REG = DIO_PORT_HIGH;
			break;
		default:
			// If the input state is not one of the above cases return error state WRONG_DIR
			u8ErrorState=WRONG_DIR;
		}
		break;
	case PORTB:
		switch (u8_Dir)
		{
		case DIO_INPUT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRB_REG = DIO_PORT_LOW;
			SET_BIT(SFIOR_REG,PUD_BIT);
			break;
		case DIO_INPUT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG,PUD_BIT);
			DDRB_REG =  DIO_PORT_LOW;
			PORTB_REG = DIO_PORT_HIGH;
			break;
		case DIO_OUTPUT:
			// for input tristate mode ( DDRx = 0xff )
			DDRB_REG = DIO_PORT_HIGH;
			break;
		default:
			// If the input state is not one of the above cases return error state WRONG_DIR
			u8ErrorState=WRONG_DIR;
		}
		break;
	case PORTC:
		switch (u8_Dir)
		{
		case DIO_INPUT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRC_REG = DIO_PORT_LOW;
			SET_BIT(SFIOR_REG,PUD_BIT);
			break;
		case DIO_INPUT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG,PUD_BIT);
			DDRC_REG =  DIO_PORT_LOW;
			PORTC_REG = DIO_PORT_HIGH;
			break;
		case DIO_OUTPUT:
			// for input tristate mode ( DDRx = 0xff )
			DDRC_REG = DIO_PORT_HIGH;
			break;
		default:
			// If the input state is not one of the above cases return error state WRONG_DIR
			u8ErrorState=WRONG_DIR;
		}
		break;
	case PORTD:
		switch (u8_Dir)
		{
		case DIO_INPUT:
			// for input tristate mode ({DDRx, PORTx} = {0x00,0x00})
			DDRD_REG = DIO_PORT_LOW;
			SET_BIT(SFIOR_REG,PUD_BIT);
			break;
		case DIO_INPUT_PULLUP:
			// for input PULLUP mode ( {DDRx, PORTx,PUD} =  {0b0,0x00,0xff} )
			CLR_BIT(SFIOR_REG,PUD_BIT);
			DDRD_REG =  DIO_PORT_LOW;
			PORTD_REG = DIO_PORT_HIGH;
			break;
		case DIO_OUTPUT:
			// for input tristate mode ( DDRx = 0xff )
			DDRD_REG = DIO_PORT_HIGH;
			break;
		default:
			// If the input state is not one of the above cases return error state WRONG_DIR
			u8ErrorState=WRONG_DIR;
		}
		break;
	default:
		// If the input port is not one of the above cases return error state WRONG_PORT
		u8ErrorState=WRONG_PORT;
	}

	return u8ErrorState;
}

/**
 * @fn ErrorState_t DIO_u8SetPortData(DIOPort_t u8_PortName,uint8_t u8_Value)
 * @brief this function is used to output a value on DIO Port
 * @param u8_PortName : The port where the pin exist can be one of the following
 * PORTA
 * PORTB
 * PORTC
 * PORTD
 * @param u8_Value a number between from 0 - 255
 * @return return a number between 0 - 255 represent the Error State
 *  254 : WRONG Port
 */
DIO_ErrorState_t DIO_u8SetPortData(DIOPort_t u8_PortName,uint8_t u8_Value)
{
	DIO_ErrorState_t u8ErrorState=DIO_OK;

		switch (u8_PortName)
		{
		case PORTA:
			PORTA_REG = u8_Value;
			break;
		case PORTB:
			PORTB_REG = u8_Value;
			break;
		case PORTC:
			PORTC_REG=u8_Value;
			break;
		case PORTD:
			PORTD_REG=u8_Value;
			break;
		default:
			// if input port is not one of the above cases return error state WRONG_PORT
			u8ErrorState=WRONG_PORT;
		}

	return u8ErrorState;
}

/**
 * @fn ErrorState_t DIO_u8GetPortData (DIOPort_t u8_PortName,uint8_t* pu8_ReturnVar)
 * @brief this function is used to get the value presented on an input DIO Port
 * @param u8_PortName : The port where the pin exist can be one of the following
 * PORTA
 * PORTB
 * PORTC
 * PORTD
 * @param pu8_ReturnVar this is a pointer to a uint8_t to hold the data on the port
 * @return return a number between 0 - 255 represent the Error State
 *  254 : WRONG Port
 *  252 : The input pointer is not pointing to a valid memory place
 */
DIO_ErrorState_t DIO_u8GetPortData (DIOPort_t u8_PortName,uint8_t* pu8_ReturnVar)
{
	DIO_ErrorState_t u8ErrorState = DIO_OK;
	if (pu8_ReturnVar!=NULL)
	{
		// get port value in register to variable depend on port and pin 
		switch(u8_PortName)
		{
		case PORTA:
			*pu8_ReturnVar= PORTA_REG;
			break;
		case PORTB:
			*pu8_ReturnVar= PORTB_REG;
			break;
		case PORTC:
			*pu8_ReturnVar= PORTC_REG;
			break;
		case PORTD:
			*pu8_ReturnVar= PORTD_REG;
			break;
		default:
			// if not suitable port return error state WRONG_PORT
			u8ErrorState=WRONG_PORT;
		}
	}else{
		// if no address passed to function return error state NULL_PTR
		u8ErrorState=NULL_PTR;
	}

	return u8ErrorState;
}

/**
 * @fn ErrorState_t DIO_u8TogglePinData(DIOPort_t u8_PortName,DIOPin_t u8_PinNum)
 * @brief This function is used to toggle the output of an output pin
 * @param u8_PortName : The port where the pin exist can be one of the following
 * PORTA
 * PORTB
 * PORTC
 * PORTD
 * @param u8_PinNum : The number of the pin
 * PIN0
 * PIN1
 * PIN2
 * PIN3
 * PIN4
 * PIN5
 * PIN6
 * PIN7
 * @return returns a number from 0 - 255 represent the Error State
 *  255 : Wrong PIN Number
 *  254 : Wrong PORT Number
 */
DIO_ErrorState_t DIO_u8TogglePinData(DIOPort_t u8_PortName,DIOPin_t u8_PinNum){

	DIO_ErrorState_t u8ErrorState = DIO_OK;
	if (u8_PinNum < DIO_PINS_NUMBER)
	{
		switch(u8_PortName){
		// toogle bit value depend on port and pin
		case PORTA:
			Toggle_BIT(PORTA_REG, u8_PinNum);
			break;
		case PORTB:
			Toggle_BIT(PORTB_REG, u8_PinNum);
			break;
		case PORTC:
			Toggle_BIT(PORTC_REG, u8_PinNum);
			break;
		case PORTD:
			Toggle_BIT(PORTD_REG, u8_PinNum);
			break;
		default:
			// if input port is not one of the above cases return error state WRONG_PORT
			u8ErrorState = WRONG_PORT;
		}
	}else{
		u8ErrorState = WRONG_PIN;
	}

	return u8ErrorState;
}
