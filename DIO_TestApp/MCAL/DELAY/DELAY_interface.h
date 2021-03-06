/*
 * DELAY_inteface.h
 *
 *  Created on: Jan 15, 2022
 *      Author:  Alhassan Mohsen
 */

#ifndef MCAL_DELAY_DELAY_INTERFACE_H_
#define MCAL_DELAY_DELAY_INTERFACE_H_


#include "../../LIB/Typedef.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/atmega32.h"
#include "../TIMER0/TIMER0_interface.h"

/**
 * @enum Defines the Error States of the Delay Driver
 */
typedef enum {
	DELAY_OK=1,            //!< No Error Occurred
	DELAY_TMER_RETURN_ERROR = 255//!< There is an error happened during calling timer function test you timer
}DelayErrorState_t;


/**
 * @fn DelayErrorState_t DELAY_ms(uint16_t u8MsDelay)
 * @brief This function used to make a delay using pooling mechanism
 * @param u8MsDelay : the time of the delay desired in milliseconds can be 0 - 65535
 * @return return a number from 0 - 255 represent the error states of the function. Possible returns are
 *  1  : DELAY_OK
 *  255: DELAY_TMER_RETURN_ERROR
 */
DelayErrorState_t DELAY_ms(uint16_t u8MsDelay);



#endif /* MCAL_DELAY_DELAY_INTERFACE_H_ */
