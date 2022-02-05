/*
 * SERVICE.h
 *
 * Created: 1/31/2022 
 *  Author: Abdelrhman Elsawy
 */ 


#ifndef SERVICE_H_
#define SERVICE_H_

#include "../LIB/BIT_Math.h"
#include "../LIB/Typedef.h"
#include "../ECUAL/LCD/LCD.h"
#include "../ECUAL/KEYPAD/KEYPAD_interface.h"
#include "../SERVICE/SERVICE.h"

uint8_t StringToInt (uint8_t * Str,uint32_t* pu32Result);
f32_t StringToFloat (uint8_t * Str);


#endif /* SERVICE_H_ */
