/*
 * UI.h
 *
 *  Created on: Jan 10, 2022
 *      Author: Esraa
 */

#ifndef UI_H_
#define UI_H_

#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"
#include "../../ECUAL/LED/LED.h"
#include "../../ECUAL/KEYPAD/KEYPAD_interface.h"


uint8_t UI_GetKeyPressed(uint8_t* UI_keyModuleReturn);
uint8_t UI_Init(void);
uint8_t UI_SetLedModuleState(uint8_t UI_LEDModuleState);



#endif /* UI_H_ */
