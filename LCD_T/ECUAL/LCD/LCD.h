/*
 * LCD.h
 *
 * Created: 1/17/2022 12:19:20 AM
 *  Author: Khaled Ali
 */

#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/Typedef.h"
#include "LCD_cfg.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DELAY/TIMER0.h"
#include "../../LIB/BIT_Math.h"

uint8_t LCD_u8Init(void);

uint8_t LCD_u8SendCommand(uint8_t command);

uint8_t LCD_u8SendData(uint8_t data);
void LCD_u8SendNumber(uint16_t num);
uint8_t LCD_u8SendString(uint8_t *str);
uint8_t LCD_u8SetCursor(uint8_t row, uint8_t col);
uint8_t LCD_u8printCustomized(uint8_t u8CharID);
uint8_t LCD_u8SendCustomized(uint8_t * pu8CustomChar,uint8_t u8CharID);

#endif /* LCD_H_ */
