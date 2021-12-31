#include<stdio.h>
#include "compiler.h"
#include "Sort.h"


u8_t binarySearch(u32_t* arr,u8_t size,u32_t number)
{
    u8_t u8_startPtr=0;
    u8_t u8_endPtr = size-1;
    u8_t u8_numberIndex=-1;
    u8_t u8_midPtr;

    if (size<255)
    {
        while (u8_endPtr>=u8_startPtr)
        {
            u8_midPtr = u8_startPtr+((u8_endPtr-u8_startPtr)/2);
            if (arr[u8_midPtr]==number)
            {
                u8_numberIndex=u8_midPtr;
                break;
            }
            else if (arr[u8_midPtr]>number)
            {
                u8_endPtr=u8_midPtr-1;
            }else if (arr[u8_midPtr]<number)
            {
                u8_startPtr=u8_midPtr+1;
            }
        }
    }


    return u8_numberIndex;

}
