/*
 * main.c
 *
 *  Created on: Jan 22, 2022
 *      Author: vip
 */


#include "../LIB/BIT_Math.h"
#include "../LIB/Typedef.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../ECUAL/LCD/LCD.h"
/*
 * The main Program is to read a volt value from the potentiometer
 *
 */
int main(void)
{

	/*
	 * Define the POT as an ADC Channel with the single conversion mode
	 */
	ADCChannel_t st_POT= {PORTA,PIN0,ADC_SINGLE_CONVERSION};
	uint16_t u16POTReadings;// To save the readings

	/*
	 * Initiate our modules and peripherals
	 */
	ADC_u8Init();
	LCD_u8Init();

	// Set the pin on of the POT to be an input pin
	DIO_u8SetPinDirection(PORTA,PIN0,DIO_INPUT);

	while (1)
	{
		//Clear the screen before writing
		LCD_u8SendCommand(0x01);
		//Start another single conversion
		ADC_u8StartConversion(&st_POT);
		//Get the ADC readings as milli volt values
		ADC_u8GetVolt(&u16POTReadings);
		//Send the number to be printed on the LCD
		LCD_u8SendNumber(u16POTReadings);
		//delay for 300 ms to read before clear
		TIMER0_u8PollingDelay(300);
	}
}
