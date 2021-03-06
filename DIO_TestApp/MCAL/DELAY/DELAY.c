/*
 * DELAY.c
 *
 *  Created on: Jan 15, 2022
 *      Author: Alhassan Mohsen
 */


#include "DELAY_interface.h"
#include "DELAY_cfg.h"
#include "DELAY_prv.h"

static volatile uint16_t msDelayCounter ;


DelayErrorState_t DELAY_ms(uint16_t u8MsDelay)
{
	msDelayCounter = 0;
	uint8_t u8ErrorState = DELAY_OK;
	TIM0_Config_t DelayConfig = {TIM0_CTC,DELAY_TIMER_PRESCALAR};


	// initiate the timer in CTC Mode with system clock pre-scaled by 64
	u8ErrorState = TIM0_u8Init(&DelayConfig);

	if (u8ErrorState == TIM0_OK)
	{
		// set the compare value with DELAY_MS_COMPARE_COUNTS to ensure an interrupt every 1 ms
		u8ErrorState = TIM0_u8SetCompareValue(DELAY_MS_COMPARE_COUNTS);
	}else{
		u8ErrorState = DELAY_TMER_RETURN_ERROR;
	}
	if (u8ErrorState == TIM0_OK)
	{
		// Enable the Compare match interrupt and use the DELAY_vMsCallBackFun as a call back function
		u8ErrorState = TIM0_u8EnableOCInterrupt(DELAY_vMsCallBackFun);
	}else{
		u8ErrorState = DELAY_TMER_RETURN_ERROR;
	}
	if (u8ErrorState == TIM0_OK)
	{
		// After setting the timer configurations Start The Timer
		u8ErrorState = TIM0_u8TimerStart();
	}else{
		u8ErrorState = DELAY_TMER_RETURN_ERROR;
	}

	// Loop until the Counter equal to the desired delay (the counter is updated every 1 ms)
	while (msDelayCounter <= u8MsDelay);

	// After finish Disable Interrupts
	TIM0_u8DisableOCInterrupt();
	return u8ErrorState;
}


void DELAY_vMsCallBackFun(void)
{
	msDelayCounter++;
}
