/*
 * KEYPAD_cfg.h
 *
 *  Created on: Jan 11, 2022
 *      Author: Binary Beasts
 */

#ifndef ECUAL_KEYPAD_KEYPAD_CFG_H_
#define ECUAL_KEYPAD_KEYPAD_CFG_H_

#define KEYPAD_ROWS 4
#define KEYPAD_COL  4

#define COL_S   2
#define COL_MAX 6

#define ROW_S   2
#define ROW_MAX 6

#define COL_PORT  PORTC
#define ROW_PORT  PORTD

#define COL_PIN0  PIN2
#define COL_PIN1  PIN3
#define COL_PIN2  PIN4
#define COL_PIN3  PIN5

#define ROW_PIN0  PIN2
#define ROW_PIN1  PIN3
#define ROW_PIN2  PIN4
#define ROW_PIN3  PIN5

#define KEYPAD_VALUES  {{7,8,9,'-'},{4,5,6,'*'},{1,2,3,'/'},{'c',0,'.','E'}}
// 'E' --> Enter ( + ) , '.' for decimal point ( = )

#endif /* ECUAL_KEYPAD_KEYPAD_CFG_H_ */
