/*
 * UART.c
 *
 *  Created on: Jan 24, 2022
 *      Author: vip
 */

#include "UART_interface.h"
#include "UART_prv.h"
#include "UARTConfig.h"

static void (*RecieveCallBack)(void);
static void (*TransmitCallBack)(void);

uint8_t UART_u8Init(uint32_t UART_u32BaudRate)
{
	uint8_t u8ErrorState = UART_OK;
	uint16_t u16UBBR;

	SET_BIT(UCSRC_REG,URSEL_BIT);

#if   UART_OPERATION_MODE == UART_ASYNC_NORMAL_SPEED
	CLR_BIT(UCSRC_REG,UMSEL_BIT);
	CLR_BIT(UCSRA_REG,U2X_BIT);
	u16UBBR = (UART_F_CPU/(16UL*UART_u32BaudRate)-1);
#elif UART_OPERATION_MODE == UART_ASYNC_DOUBLE_SPEED
	CLR_BIT(UCSRC_REG,UMSEL_BIT);
	SET_BIT(UCSRA_REG,U2X_BIT);
	u16UBBR = (UART_F_CPU/(8*UART_u32BaudRate))-1;
#elif UART_OPERATION_MODE == UART_SYNC_MODE
	SET_BIT(UCSRC_REG,UMSEL_BIT);
	CLR_BIT(UCSRC_REG,UCPOL_BIT);
	u16UBBR = (UART_F_CPU/(2*UART_u32BaudRate))-1;
#else
	u8ErrorState = WRONG_OPERATION_MODE_CFG;
#endif

#if UART_CHARACTER_SIZE == UART_5_BIT_CHARACTER
	CLR_BIT(UCSRC_REG,UCSZ0_BIT);
	CLR_BIT(UCSRC_REG,UCSZ1_BIT);
	CLR_BIT(UCSRB_REG,UCSZ2_BIT);
#elif UART_CHARACTER_SIZE == UART_6_BIT_CHARACTER
	SET_BIT(UCSRC_REG,UCSZ0_BIT);
	CLR_BIT(UCSRC_REG,UCSZ1_BIT);
	CLR_BIT(UCSRB_REG,UCSZ2_BIT);
#elif UART_CHARACTER_SIZE == UART_7_BIT_CHARACTER
	CLR_BIT(UCSRC_REG,UCSZ0_BIT);
	SET_BIT(UCSRC_REG,UCSZ1_BIT);
	CLR_BIT(UCSRB_REG,UCSZ2_BIT);
#elif UART_CHARACTER_SIZE == UART_8_BIT_CHARACTER
	SET_BIT(UCSRC_REG,UCSZ0_BIT);
	SET_BIT(UCSRC_REG,UCSZ1_BIT);
	CLR_BIT(UCSRB_REG,UCSZ2_BIT);
#elif UART_CHARACTER_SIZE == UART_9_BIT_CHARACTER
	SET_BIT(UCSRC_REG,UCSZ0_BIT);
	SET_BIT(UCSRC_REG,UCSZ1_BIT);
	SET_BIT(UCSRB_REG,UCSZ2_BIT);
#else
	u8ErrorState = WRONG_CHARACTER_SIZE_CFG;
#endif

#if UART_PARITY_MODE == UART_DISABLE_PARITY
	CLR_BIT(UCSRC_REG,UPM0_BIT);
	CLR_BIT(UCSRC_REG,UPM1_BIT);
#elif UART_PARITY_MODE == UART_EVEN_PARITY
	CLR_BIT(UCSRC_REG,UPM0_BIT);
	SET_BIT(UCSRC_REG,UPM1_BIT);
#elif UART_PARITY_MODE == UART_ODD_PARITY
	SET_BIT(UCSRC_REG,UPM0_BIT);
	SET_BIT(UCSRC_REG,UPM1_BIT);
#else
	u8ErrorState = WRONG_PARITY_CFG;
#endif

#if UART_STOP_BITS_NUMBER == UART_1_STOP_BIT
	CLR_BIT(UCSRC_REG,USBS_BIT);
#elif UART_STOP_BITS_NUMBER == UART_2_STOP_BIT
	SET_BIT(UCSRC_REG,USBS_BIT);
#else
	u8ErrorState = WRONG_STOP_BITS_CFG;
#endif

	UBRRL_REG= u16UBBR;
	UBRRH_REG= (u16UBBR>>8);

	SET_BIT(UCSRB_REG,RXEN_BIT);
	SET_BIT(UCSRB_REG,TXEN_BIT);


	return u8ErrorState;
}
uint8_t UART_u8SendByte(uint8_t u8Data)
{
	uint8_t u8ErrorState = UART_OK;
	while(!GET_BIT(UCSRA_REG,UDRE_BIT));
	UDR_REG = u8Data;
	return u8ErrorState;
}
uint8_t UART_u8RecieveByte(uint8_t* pu8RecievedData)
{
	uint8_t u8ErrorState = UART_OK;
	while (!GET_BIT(UCSRA_REG,RXC_BIT));
	*pu8RecievedData = UDR_REG;
	return u8ErrorState;
}
uint8_t UART_u8EnableRecievingInterrupt(void (*pfnCallBack)(void))
{
	uint8_t u8ErrorState = UART_OK;
	if (pfnCallBack!=NULL)
	{
		RecieveCallBack = pfnCallBack;
		SET_BIT(UCSRB_REG,RXCIE_BIT);
		SET_BIT(SREG_REG,I_BIT);
	}else
	{
		u8ErrorState = UART_NULL_INPUT;
	}

	return u8ErrorState;
}
uint8_t UART_u8EnableSendingInterrupt(void (*pfnCallBack)(void))
{
	uint8_t u8ErrorState = UART_OK;
	if (pfnCallBack!=NULL)
	{
		TransmitCallBack = pfnCallBack;
		SET_BIT(UCSRB_REG,UDRIE_BIT);
		SET_BIT(SREG_REG,I_BIT);
	}else
	{
		u8ErrorState = UART_NULL_INPUT;
	}

	return u8ErrorState;

}
uint8_t UART_u8DisableRecievingInterrupt(void)
{
	uint8_t u8ErrorState = UART_OK;
	RecieveCallBack = NULL;
	CLR_BIT(UCSRB_REG,RXCIE_BIT);
	return u8ErrorState;
}
uint8_t UART_u8DisableSendingInterrupt(void)
{
	uint8_t u8ErrorState = UART_OK;
	TransmitCallBack = NULL;
	CLR_BIT(UCSRB_REG,TXCIE_BIT);
	return u8ErrorState;
}
uint8_t UART_u8Deinit(void)
{
	uint8_t u8ErrorState = UART_OK;
	CLR_BIT(UCSRB_REG,RXEN_BIT);
	CLR_BIT(UCSRB_REG,TXEN_BIT);
	return u8ErrorState;
}


void __vector_13(void) {
	uint8_t UDRFlush;
	if (RecieveCallBack!=NULL)
	{
		RecieveCallBack();
	}else
	{
		UDRFlush = UDR_REG;
	}
}
void __vector_14(void) {
	if (RecieveCallBack!=NULL)
	{
		TransmitCallBack();
	}
}
