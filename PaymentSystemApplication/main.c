#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "PaymentSystem.h"

int main()
{
    u8_t u8_ReturnedTransState;
    u8_t u8_UserInput='y';

    while (u8_UserInput=='y')
    {
        u8_ReturnedTransState= makeTransactionMain();
            /**< Check if any of the previous states change the state of the Transaction to DECLINED then reject the Transaction */
        if (u8_ReturnedTransState == APPROVED)
        {
            printf("The Transaction is APPROVED\n");
        }else if (u8_ReturnedTransState == DECLINED)
        {
            printf("The Transaction is DECLINED\n");
        }
        printf("Do you Want To Continue (y/n)?\n");
        fflush(stdin);
        scanf("%c",&u8_UserInput);
    }


    return 0;
}
