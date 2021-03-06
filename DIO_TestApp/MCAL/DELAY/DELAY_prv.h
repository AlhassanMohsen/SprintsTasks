/*
 * DELAY_prv.h
 *
 *  Created on: Jan 15, 2022
 *      Author: Alhassan Mohsen
 */

#ifndef MCAL_DELAY_DELAY_PRV_H_
#define MCAL_DELAY_DELAY_PRV_H_

/**
 * Check The cpu clock and the prescalar used for timer0 to decide the compare counts suitable to generate an interrupt every 1 ms
 */
#if (DELAY_F_CPU==8000000UL && DELAY_PRESCALAR == PRESCALAR_64)
#define DELAY_MS_COMPARE_COUNTS		124
#endif

/**
 * @fn void DELAY_vMsCallBackFun(void);
 * @brief this function is used to write the logic wanted to be performed in the ISR of the timer
 */
void DELAY_vMsCallBackFun(void);

#endif /* MCAL_DELAY_DELAY_PRV_H_ */
