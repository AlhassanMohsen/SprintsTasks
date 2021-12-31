
#include<stdio.h>
#include "compiler.h"
#include "Sort.h"

void swap(u32_t* num1,u32_t* num2 )
{
    u32_t temp;
    temp= *num1;
    *num1=*num2;
    *num2=temp;
}

void void_InsertionSort(u32_t* au32_arr, u8_t u8_arrSize)
{
    u8_t u8_arrNav,u8_swapPtr;
    u32_t u32_SwapTemp;
    for (u8_arrNav=1; u8_arrNav<u8_arrSize; u8_arrNav++)
    {
        u8_swapPtr=u8_arrNav;
        while ((au32_arr[u8_swapPtr]<au32_arr[u8_swapPtr-1])&& u8_swapPtr>0)
        {
            swap((au32_arr+u8_swapPtr),(au32_arr+u8_swapPtr-1));
            u8_swapPtr--;
        }
    }

}
u8_t u8_IsSorted(u32_t* au32_arr, u8_t u8_arrSize)
{
    u8_t u8_sortingState=ARRAY_SORTED;
    for (u8_t u8_arrNav=1; u8_arrNav<u8_arrSize;u8_arrNav++)
    {
        if (au32_arr[u8_arrNav-1]>au32_arr[u8_arrNav])
        {
            u8_sortingState= ARRAY_UNSORTED;
            break;
        }else{
            //NOP
        }
    }

    return u8_sortingState;
}
