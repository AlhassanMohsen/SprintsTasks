
#include <stdlib.h>

#include "Stack.h"

extern StackObj* gpso_StackHead;


u8_t* balancedParentheses(u8_t* expression)
{
    u8_t u8_nav=0;
    u8_t u8_OpencurlyCount=0;
    u8_t u8_OpenroundCount=0;
    u8_t u8_ClosedcurlyCount=0;
    u8_t u8_ClosedroundCount=0;

    u8_t u8_tmpData;
    StackObj* pso_StackNav=NULL;

        /**< Push every character in the string to the stack  */
    while (expression[u8_nav]!='\0')
    {
        push(expression[u8_nav]);
        u8_nav++;
    }

    pso_StackNav= gpso_StackHead;


        /**< Loop on the Stack and count the  opened and closed brackets to find if there is no match */
    while (pso_StackNav!=NULL)
    {
        u8_tmpData=pso_StackNav->u8_Elementdata;
        switch(u8_tmpData)
        {
        case '{':
            u8_OpencurlyCount++;
            break;
        case '}':
            u8_ClosedcurlyCount++;
            break;
        case '(':
            u8_OpenroundCount++;
            break;
        case ')':
            u8_ClosedroundCount++;
            break;
        default:
            break;
        }
        pso_StackNav=pso_StackNav->pso_nxtPtr;
    }

    if ((u8_OpencurlyCount==u8_ClosedcurlyCount)&&(u8_OpenroundCount==u8_ClosedroundCount))
    {
        return "Balanced";
    }
    else{

        return "Not Balanced";
    }


}

