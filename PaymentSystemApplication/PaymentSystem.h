#ifndef __PAYMENTSYSTEM_H_
#define __PAYMENTSYSTEM_H_

typedef struct ST_cardData_t{

    u8_t cardHolderName[25];
    u8_t primaryAccountNumber[20];
    u8_t cardExpirationDate[2];
}ST_cardData_t;


typedef struct ST_terminalData_t{

    float transAmount;
    float maxTransAmount;
    u16_t transactionDate[3];
}ST_terminalData_t;

typedef enum EN_transStat_t
{
    DECLINED,
    APPROVED
}EN_transStat_t;

typedef struct ST_transation_t{

    ST_cardData_t cardHolderData;
    ST_terminalData_t transData;
    EN_transStat_t transStat;
}ST_transation_t;

/** \brief  This function Contain the Logic of the transaction process
 *
 * \param   void
 * \param
 * \return  return the state of the transaction if it is APPROVED or DECLINED
 *
 */

EN_transStat_t makeTransactionMain(void);



#endif // __PAYMENTSYSTEM_H_
