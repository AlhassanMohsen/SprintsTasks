
#include <stdio.h>
#include"Stack.h"


StackObj* gpso_StackHead = NULL;


u8_t Stack_IsEmpty()
{
    u8_t u8_StackEmpty;
    if (gpso_StackHead==NULL)
    {
        u8_StackEmpty = STACK_EMPTY;
    }else{
        u8_StackEmpty = STACK_NOT_EMPTY;
    }

    return u8_StackEmpty;
}

void push(u8_t u8_data)
{
    StackObj* pso_TmpPtr = (StackObj*)malloc(sizeof(StackObj));

    pso_TmpPtr->pso_nxtPtr=gpso_StackHead;
    pso_TmpPtr->u8_Elementdata=u8_data;
    gpso_StackHead = pso_TmpPtr;
}
u8_t pull(void)
{
    u8_t u8_PulledData;

    StackObj* pso_TmpPtr = gpso_StackHead;
    u8_PulledData = gpso_StackHead->u8_Elementdata;

    gpso_StackHead = gpso_StackHead->pso_nxtPtr;
    free(pso_TmpPtr);
  //  printf("%d\n",gpso_StackHead->u8_Elementdata);
    return u8_PulledData;
}


void printStack(void)
{

    StackObj* pso_tmpPtr = gpso_StackHead;


    if(!Stack_IsEmpty())
    {
        do
        {
           printf("%d\n",pso_tmpPtr->u8_Elementdata);
           pso_tmpPtr=pso_tmpPtr->pso_nxtPtr;

        }while (pso_tmpPtr!=NULL);
    }else{
        printf("Stack Is Empty");
    }

}


