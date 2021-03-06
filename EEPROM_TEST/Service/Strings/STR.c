/*
 * STR.c
 *
 *  Created on: Feb 3, 2022
 *      Author: Esraa
 */


#include "STR.h"
#include "../../MCAL/UART/UART_interface.h"


uint8_t STR_CMP(uint8_t* STR1,uint8_t* STR2)
{
	uint8_t u8StringCounter=0;
	uint8_t u8String1_Length=0;
	uint8_t u8String2_Length=0;
	uint8_t u8SimilarityCounter=0;
	uint8_t u8CMPResult;

	do
	{
		u8String1_Length++;
		u8StringCounter++;
	}while (STR1[u8StringCounter]!='\0'&&STR1[u8StringCounter]!=0x0D);

	u8StringCounter=0;

	do
	{
		u8String2_Length++;
		u8StringCounter++;
	}while (STR2[u8StringCounter]!='\0'&&STR2[u8StringCounter]!=0x0D);

	u8StringCounter=0;


	if (u8String2_Length==u8String1_Length)
	{

		for (u8StringCounter=0;u8StringCounter<u8String1_Length;u8StringCounter++)
		{
			if (STR1[u8StringCounter]==STR2[u8StringCounter])
			{
				u8SimilarityCounter++;
			}else
			{
				break;
			}
		}
	}


	if (u8String1_Length==u8SimilarityCounter && u8SimilarityCounter!=0)
	{
		u8CMPResult=CMP_MATCH;
	}else
	{
		u8CMPResult=CMP_NOT_MATCHED;
	}
	return u8CMPResult;
}


uint8_t STR_BinToInt(uint8_t* BinaryArray)
{
	uint16_t u16ReturnedInt=0;
	for(uint8_t Counter=0;Counter<=16;Counter++)
	{
		u16ReturnedInt= u16ReturnedInt|((BinaryArray[Counter]-'0')<<Counter);
	}

	return u16ReturnedInt;
}
