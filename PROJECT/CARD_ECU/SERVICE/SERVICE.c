/*
 * SERVICE.c
 *
 * Created: 1/31/2022 
 *  Author: Abdelrhman Elsawy
 */
 
#include "SERVICE.h"

uint8_t StringToInt (uint8_t * Str,uint32_t* pu32Result)
{
/*	*pu32Result = 0 ;
	while ( *Str != '\0' )
	{
		*pu32Result = (*(pu32Result) * 10)+ ( *Str - '0' );
		Str++ ;
	}
	return 1 ;
	*/
    uint8_t u8ArrayCounter=0;
    uint32_t u8Multiplier=1;
    *pu32Result=0;
    uint8_t ArrayNav=0;
    //UART_u8SendString(ReceivedStr);
    while (Str[u8ArrayCounter]!=0x00)
    {
    	u8ArrayCounter++;
    }

    for(uint8_t loopCounter=0;loopCounter<u8ArrayCounter;loopCounter++)
    {

        for(uint8_t multiplier=(u8ArrayCounter-1)-loopCounter;multiplier>0;multiplier--)
        {
        	u8Multiplier=10*u8Multiplier;
        }
        *pu32Result = *pu32Result + ((Str[ArrayNav]-'0')*u8Multiplier);
        ArrayNav++;
        u8Multiplier=1;
    }
}

f32_t StringToFloat (uint8_t * Str)
{
	f32_t iPart , dPart , result , mult ;
	mult = 0.1 ;
	iPart = dPart = result = 0.0 ;
	UART_u8SendString(Str);
	UART_u8SendByte(0x0D);
	while( *Str != '.' ) 
	{
		iPart = iPart * 10.0 + (*Str -'0') ;
		UART_u8SendInt(iPart);
		UART_u8SendByte(0x0D);
		Str++ ;
	}
	Str++;
	while( *Str != '\0' ) 
	{
		dPart += (*Str - '0')*mult;
		mult *= 0.1;
		Str++ ;
		UART_u8SendInt(dPart);
		UART_u8SendByte(0x0D);
	}
	result = iPart + dPart;
}
