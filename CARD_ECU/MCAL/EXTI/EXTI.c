/*
 * EXTI.c
 *
 *  Created on: Feb 5, 2022
 *      Author: Esraa
 */

#include "EXTI_prv.h"
#include "EXTI.h"


uint8_t EXTI_u8Enable(EXTINumber_t u8InterruptNumber, EXTITiggerType_t u8InterruptTrigger)
{
	uint8_t u8ErrorState = EXTI_OK;

	switch(u8InterruptNumber)
	{
	case INT0:
		CLR_BIT(GICR_REG,INT0_BIT);
		CLR_BIT(DDRD_REG,DDD2_BIT);
		switch(u8InterruptTrigger)
		{
		case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR_REG,ISC00_BIT);
			CLR_BIT(MCUCR_REG,ISC01_BIT);
			break;
		case EXTI_TOGGLE:
			SET_BIT(MCUCR_REG,ISC00_BIT);
			CLR_BIT(MCUCR_REG,ISC01_BIT);
			break;
		case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCR_REG,ISC00_BIT);
			SET_BIT(MCUCR_REG,ISC01_BIT);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(MCUCR_REG,ISC00_BIT);
			SET_BIT(MCUCR_REG,ISC01_BIT);
			break;
		default:
			u8ErrorState = EXTI_WRONG_TRIGGER_TYPE;
		}
		SET_BIT(GICR_REG,INT0_BIT);
		break;
	case INT1:
		CLR_BIT(GICR_REG,INT1_BIT);
		CLR_BIT(DDRD_REG,DDD3_BIT);
		switch(u8InterruptTrigger)
		{
		case EXTI_LOW_LEVEL:
			CLR_BIT(MCUCR_REG,ISC10_BIT);
			CLR_BIT(MCUCR_REG,ISC11_BIT);
			break;
		case EXTI_TOGGLE:
			SET_BIT(MCUCR_REG,ISC10_BIT);
			CLR_BIT(MCUCR_REG,ISC11_BIT);
			break;
		case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCR_REG,ISC10_BIT);
			SET_BIT(MCUCR_REG,ISC11_BIT);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(MCUCR_REG,ISC10_BIT);
			SET_BIT(MCUCR_REG,ISC11_BIT);
			break;
		default:
			u8ErrorState = EXTI_WRONG_TRIGGER_TYPE;
		}
		SET_BIT(GICR_REG,INT1_BIT);
		break;
	case INT2:
		CLR_BIT(GICR_REG,INT2_BIT);
		CLR_BIT(DDRB_REG,DDB2_BIT);
		switch(u8InterruptTrigger)
		{
		case EXTI_FALLING_EDGE:
			CLR_BIT(MCUCSR_REG,ISC2_BIT);
			break;
		case EXTI_RISING_EDGE:
			SET_BIT(MCUCSR_REG,ISC2_BIT);
			break;
		default:
			u8ErrorState = EXTI_WRONG_TRIGGER_TYPE;
		}
		SET_BIT(GICR_REG,INT2_BIT);
		break;
	default:
		u8ErrorState =EXTI_WRONG_INT_NUMBER;
	}

	SET_BIT(SREG_REG,I_BIT);

	return u8ErrorState;
}

void EXTI_vidGenerateInterrupt();
