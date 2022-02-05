/*
 * main.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Alhassan Mohsen
 */



#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../ECUAL/LED/LED.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/DELAY/TIMER0.h"
#include "ATM.h"

int main(void)
{
	ATM_Init();
	ATM_APP();

	while (1)
	{

	}

}


