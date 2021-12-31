#ifndef __STACK_H_
#define __STACK_H_

#include "compiler.h"

#define STACK_NOT_EMPTY 0
#define STACK_EMPTY     1

#define STACK_NOT_FULL  0
#define STACKs_FULL      1


typedef struct StackObj{

    u8_t u8_Elementdata;
    struct StackObj* pso_nxtPtr;
}StackObj;




void push(u8_t u8_data);
u8_t pull(void);
u8_t Stack_IsEmpty();
void printStack(void);





#endif // __STACK_H_
