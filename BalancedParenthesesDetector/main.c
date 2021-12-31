#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "ParenthesesDetector.h"

int main()
{
    u8_t testCaseArray[100];
    u8_t u8_UserInput='y';

    while (u8_UserInput=='y')
    {
        printf("Please Enter a Test Case: ");
        fflush(stdin);
        fgets(testCaseArray, sizeof(testCaseArray), stdin);
        printf("%s\n",balancedParentheses(testCaseArray));
        printf("Want to Enter another test case (y/n)? ");
        fflush(stdin);
        scanf("%c",&u8_UserInput);
    }

    return 0;
}
