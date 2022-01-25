/*
 * LCD.c
 *
 * Created: 1/17/2022 12:19:06 AM
 *  Author: Alhassan Mohsen
 */

#include "LCD.h"
#include "LCD_prv.h"
#include "LCD_cfg.h"

uint8_t LCD_u8Init(void) {

	   /*step 1 : config data port*/
	#if(FUNCTION_SET == FUNCTION_SET_8BIT_MODE_2LINES || FUNCTION_SET == FUNCTION_SET_8BIT_MODE_1LINES)
		DIO_u8SetPortDirection(PORT_DATA,DIO_OUTPUT);
	#elif(FUNCTION_SET == FUNCTION_SET_4BIT_MODE_2LINES || FUNCTION_SET ==  FUNCTION_SET_4BIT_MODE_1LINES)
		DIO_u8SetPinDirection(PORT_DATA,LCD_D4_PIN,DIO_OUTPUT);
		DIO_u8SetPinDirection(PORT_DATA,LCD_D5_PIN,DIO_OUTPUT);
		DIO_u8SetPinDirection(PORT_DATA,LCD_D6_PIN,DIO_OUTPUT);
		DIO_u8SetPinDirection(PORT_DATA,LCD_D7_PIN,DIO_OUTPUT);
	#endif

		/*step : config PORT CONTROL*/
		DIO_u8SetPinDirection(PORT_CONTROL,LCD_RS_PIN,DIO_OUTPUT);
		DIO_u8SetPinDirection(PORT_CONTROL,LCD_RW_PIN,DIO_OUTPUT);
		DIO_u8SetPinDirection(PORT_CONTROL,LCD_E_PIN,DIO_OUTPUT);
#if(FUNCTION_SET == FUNCTION_SET_8BIT_MODE_2LINES || FUNCTION_SET == FUNCTION_SET_8BIT_MODE_1LINES)
	/*step 2: LCD initialization */
	TIMER0_u8PollingDelay(30);
	LCD_u8SendCommand(FUNCTION_SET);
	TIMER0_u8PollingDelay(2);
	LCD_u8SendCommand(DISPLAY_ON_OFF);
	TIMER0_u8PollingDelay(2);
	LCD_u8SendCommand(CLEAR_DISPLAY);
	TIMER0_u8PollingDelay(2);
	LCD_u8SendCommand(ENTRY_MODE_SET);
	TIMER0_u8PollingDelay(2);
#elif(FUNCTION_SET == FUNCTION_SET_4BIT_MODE_2LINES || FUNCTION_SET ==  FUNCTION_SET_4BIT_MODE_1LINES)
	TIMER0_u8PollingDelay(30);
	LCD_u8SendCommand(FUNCTION_SET & 0xF0);
	LCD_u8SendCommand(FUNCTION_SET & 0xF0);
	LCD_u8SendCommand(FUNCTION_SET << 4);
	TIMER0_u8PollingDelay(2);
	LCD_u8SendCommand(DISPLAY_ON_OFF &  0xF0);
	LCD_u8SendCommand(DISPLAY_ON_OFF << 4);
	TIMER0_u8PollingDelay(2);
	LCD_u8SendCommand(CLEAR_DISPLAY &  0xF0);
	LCD_u8SendCommand(CLEAR_DISPLAY << 4);
	TIMER0_u8PollingDelay(2);
	LCD_u8SendCommand(ENTRY_MODE_SET &  0xF0);
	LCD_u8SendCommand(ENTRY_MODE_SET << 4);
	TIMER0_u8PollingDelay(2);
#endif


}


uint8_t LCD_u8SendCommand(uint8_t u8Command){

	/*step 1: select RS to be in command mode*/
	DIO_u8SetPinData(PORT_CONTROL,LCD_RS_PIN,DIO_LOW);
	/*step 2: select R/w to be write*/
	DIO_u8SetPinData(PORT_CONTROL,LCD_RW_PIN,DIO_LOW);
	/*step 3 : send Instruction*/

#if(FUNCTION_SET == FUNCTION_SET_8BIT_MODE_2LINES || FUNCTION_SET == FUNCTION_SET_8BIT_MODE_1LINES)
    DIO_u8SetPortData(PORT_DATA,u8Command);
#elif(FUNCTION_SET == FUNCTION_SET_4BIT_MODE_2LINES || FUNCTION_SET ==  FUNCTION_SET_4BIT_MODE_1LINES)
    DIO_u8Set4BitsValue(PORT_DATA, u8Command);
#endif
    /*step 4: Enable E pin */
	DIO_u8SetPinData(PORT_CONTROL,LCD_E_PIN,DIO_HIGH);
	TIMER0_u8PollingDelay(5);
	/*step 5 : Disable E pin */
	DIO_u8SetPinData(PORT_CONTROL,LCD_E_PIN,DIO_LOW);
}

uint8_t LCD_u8SendData(uint8_t u8data) {

	/*step 1: select RS to be in data mode*/
	DIO_u8SetPinData(PORT_CONTROL,LCD_RS_PIN,DIO_HIGH);
	/*step 2: select R/w to be write*/
	DIO_u8SetPinData(PORT_CONTROL,LCD_RW_PIN,DIO_LOW);

#if(FUNCTION_SET == FUNCTION_SET_8BIT_MODE_2LINES || FUNCTION_SET == FUNCTION_SET_8BIT_MODE_1LINES)
	/*step 3 : send data*/
	DIO_u8SetPortData(PORT_DATA,u8data);

	/*step 4: Enable E pin */
	DIO_u8SetPinData(PORT_CONTROL,LCD_E_PIN,DIO_HIGH);
	TIMER0_u8PollingDelay(5);
	/*step 5 : Disable E pin */
	DIO_u8SetPinData(PORT_CONTROL,LCD_E_PIN,DIO_LOW);
#elif(FUNCTION_SET == FUNCTION_SET_4BIT_MODE_2LINES || FUNCTION_SET ==  FUNCTION_SET_4BIT_MODE_1LINES)
	/*send high nibble*/
    uint8_t u8Temp = u8data;
    u8Temp = u8Temp & 0xF0;
    DIO_u8Set4BitsValue(PORT_DATA,u8Temp);//HIGH

	/*step 4: Enable E pin */
    DIO_u8SetPinData(PORT_CONTROL,LCD_E_PIN,DIO_HIGH);
	TIMER0_u8PollingDelay(5);
	/*step 5 : Disable E pin */
	DIO_u8SetPinData(PORT_CONTROL,LCD_E_PIN,DIO_LOW);

	/*send low nibble*/
	u8data = (u8data & 0x0F)<< 4;
	DIO_u8Set4BitsValue(PORT_DATA,u8data);//Low

	/*step 4: Enable E pin */
	DIO_u8SetPinData(PORT_CONTROL,LCD_E_PIN,DIO_HIGH);
	TIMER0_u8PollingDelay(5);
	/*step 5 : Disable E pin */
	DIO_u8SetPinData(PORT_CONTROL,LCD_E_PIN,DIO_LOW);
#endif

}


uint8_t LCD_u8SendString(uint8_t *pu8str){
	uint8_t state = STD_TYPES_OK;
	uint8_t i = 0;
	while(pu8str[i] != '\0')
	{
		LCD_u8SendData(pu8str[i]);
		i++;
	}

	return state;

}

void LCD_u8SendNumber(uint16_t u16Num)
{

	   uint8_t LOC_u8NumStr[10];
	   uint8_t i=0,j;
	   while(u16Num != 0)
	   {
		   LOC_u8NumStr[i] = u16Num%10 ;
		   i++;
		   u16Num /= 10;
	   }
	   for(j=i-1;j>=0;j--)
	   {
		   LCD_u8SendData(LOC_u8NumStr[j] + '0');
		   if(j == 0)break;
	   }

}

uint8_t LCD_u8SetCursor(uint8_t u8Row, uint8_t u8Col)
{
	uint8_t u8ErrorState = STD_TYPES_OK;
#if(FUNCTION_SET == FUNCTION_SET_8BIT_MODE_2LINES || FUNCTION_SET == FUNCTION_SET_8BIT_MODE_1LINES)
		if(u8Col >= 0 && u8Col <= 15)
		{
          switch(u8Row)
          {
          case 0:
        	  LCD_u8SendCommand(SET_DDRAM_ADDRESS + u8Col);
        	  break;
          case 1:
        	  LCD_u8SendCommand(SET_DDRAM_ADDRESS + HLCD_SECOND_ROW_ADDRESS_OFFSET+ u8Col);
        	  break;
          default:
        	  u8ErrorState = STD_TYPES_NOK;
          }

	   }else {
		   u8ErrorState = STD_TYPES_NOK;
	   }
#elif(FUNCTION_SET == FUNCTION_SET_4BIT_MODE_2LINES || FUNCTION_SET ==  FUNCTION_SET_4BIT_MODE_1LINES)
		if(u8Col >= 0 && u8Col <= 15)
			{
			  switch(u8Row)
			  {
			  case 0:
				  LCD_u8SendCommand((SET_DDRAM_ADDRESS + u8Col) & 0xF0);
				  LCD_u8SendCommand((SET_DDRAM_ADDRESS + u8Col) << 4);
				  break;
			  case 1:
				  LCD_u8SendCommand((SET_DDRAM_ADDRESS + HLCD_SECOND_ROW_ADDRESS_OFFSET+ u8Col) & 0xF0);
				  LCD_u8SendCommand((SET_DDRAM_ADDRESS + HLCD_SECOND_ROW_ADDRESS_OFFSET+ u8Col)<< 4);
				  break;
	          default:
	        	  u8ErrorState = STD_TYPES_NOK;
	          }

		   }
		else {
			   u8ErrorState = STD_TYPES_NOK;
		   }
#endif

		return u8ErrorState;
}


uint8_t LCD_u8SendCustomized(uint8_t * pu8CustomChar,uint8_t u8CharID)
{
	uint8_t i;
	/*set AC to point to CGRAM address*/
	 LCD_u8SendCommand(SET_CGRAM_ADDRESS + u8CharID * 8);

	 /*send character pattern to be written in CGRAM */
	 for(i=0;i<7;i++)
	 {
		 LCD_u8SendData(pu8CustomChar[i]);
	 }
	 /*return AC to point to DDRAM address*/
	 LCD_u8SendCommand(SET_DDRAM_ADDRESS);
}

uint8_t LCD_u8printCustomized(uint8_t u8CharID)
{
	LCD_u8SendData(u8CharID);
}
