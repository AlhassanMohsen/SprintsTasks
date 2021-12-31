
#include<stdio.h>
#include "compiler.h"
#include "PaymentSystem.h"
#include <string.h>
#define APPROVED 1
#define DECLINED 0


typedef struct ST_accountBalance_t{

    float balance;
    u8_t primaryAccountNumber[20];
}ST_accountBalance_t;




ST_accountBalance_t ServerData[10]= {
    {100.0,"123456789"},{6000.0,"234567891"},{3250.25,"567891234"},{1500.12,"456789123"},{500.0,"258649173"},{2100.00,"654823719"},
    {0.00, "971362485"},{1.00  ,"793148625"},{10.12  ,"123123456"},{0.55   ,"456789321"}
};


/** \brief This is a private function used to Set the Data of the card
 *
 * \param ps_CardDataPtr  pointer to structure that points to the card data structure to fill
 * \param
 * \return void
 *
 */

static void CardDataSetter(ST_cardData_t* ps_CardDataPtr)
{
    u8_t TempString[6];

    printf("Please Enter the Card Holder Name: \n");
    fflush(stdin);
    fgets(ps_CardDataPtr->cardHolderName, sizeof(ps_CardDataPtr->cardHolderName), stdin);
    printf("Please Enter the Primary Account Number: \n");
   // fgets(ps_CardDataPtr->primaryAccountNumber, sizeof(ps_CardDataPtr->primaryAccountNumber), stdin);
    fflush(stdin);
    scanf("%s",ps_CardDataPtr->primaryAccountNumber);
    fflush(stdin);
    printf("Please Enter the Card Expiry Date: \n");
    fflush(stdin);
    fgets(TempString, sizeof(TempString), stdin);
    fflush(stdin);
    sscanf( TempString, "%u/%u",&ps_CardDataPtr->cardExpirationDate[0],&ps_CardDataPtr->cardExpirationDate[1]);
}

/** \brief This is a private function used to Set the Data of the terminal
 *
 * \param ps_CardDataPtr  pointer to structure that points to the terminal data structure to fill
 * \param
 * \return void
 *
 */
static void terminalDataSetter(ST_terminalData_t* ps_terminalDataPtr)
{
    u8_t TempString[11];
    ps_terminalDataPtr->maxTransAmount=5000.0;

    printf("Please Enter the Transaction Date: \n");
    fflush(stdin);
    fgets(TempString, sizeof(TempString), stdin);
    sscanf( TempString, "%d/%d/%d",&ps_terminalDataPtr->transactionDate[0],&ps_terminalDataPtr->transactionDate[1], &ps_terminalDataPtr->transactionDate[2] );
    printf("Please Enter the transaction Amount: \n");
    scanf("%f",&ps_terminalDataPtr->transAmount);

    //return ps_terminalDataPtr;
}

/** \brief  This function Contain the Logic of the transaction process
 *
 * \param   void
 * \param
 * \return  return the state of the transaction if it is APPROVED or DECLINED
 *
 */
EN_transStat_t makeTransactionMain()
{
    u8_t TransactionDay[2],TransactionMonth[2],ExpiryDay[2],ExpiryMonth[2];
    u8_t DecimalTransactionDay,DecimalTransactionMonth,DecimalExpiryDay,DecimalExpiryMonth;
    u8_t tmpCounter1=3;
    u8_t tmpCounter2=0;


    ST_transation_t* transactionData= (ST_transation_t*)malloc(sizeof(ST_transation_t));

    CardDataSetter(&transactionData->cardHolderData);
    terminalDataSetter(&transactionData->transData);

    /**< Check if the Card is Expired */
    if (((transactionData->transData.transactionDate[2])-2000>transactionData->cardHolderData.cardExpirationDate[1]))
    {
        transactionData->transStat = DECLINED;
    }else if ((transactionData->transData.transactionDate[2]==transactionData->cardHolderData.cardExpirationDate[1]))
    {
        if (((transactionData->transData.transactionDate[1]>transactionData->cardHolderData.cardExpirationDate[0])))
        {
            transactionData->transStat = DECLINED;
        }else{
            //NOP
        }
    }else{
            //NOP
    }

    /**< if the Card is Not Expired then Check if the requested amount is acceptable by the terminal */
    if (transactionData->transStat == DECLINED)
    {
        if (transactionData->transData.transAmount > transactionData->transData.maxTransAmount)
        {
            transactionData->transStat = DECLINED;
        }else {
            //NOP
        }
    }



    /**< if the card is not Expired and the amount is accepted by the terminal begin checking the information with the server */
    if(transactionData->transStat != DECLINED)
    {
        u8_t comparingOutput=0;

        /**< Search for the PAN in the database using Linear Search*/
        for (u8_t u8_TmpCounter=0;u8_TmpCounter <(sizeof(ServerData)/sizeof(ServerData[0]));u8_TmpCounter++)
        {
            comparingOutput=strcmp(ServerData[u8_TmpCounter].primaryAccountNumber,transactionData->cardHolderData.primaryAccountNumber);

            /**< if it is found then check if the account balance is sufficient for the transaction   */
            if(!comparingOutput)
            {
                if ((transactionData->transData.transAmount <= ServerData[u8_TmpCounter].balance))
                {
                   transactionData->transStat= APPROVED;

                }else
                {
                   transactionData->transStat= DECLINED;
                }
                break;

            }else
            {
                transactionData->transStat= DECLINED;
            }
        }
    }

    return transactionData->transStat;
}


