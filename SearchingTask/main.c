#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "Sort.h"
#include "Search.h"

#define MAX_ARRAY_SIZE  255

/** \brief a utility function to print an array of u32_t numbers
 *
 * \param arr       is an array of u32_t numbers
 * \param arrSize   is the number of elements in the array
 * \return void
 *
 */
void u8_printArray(u32_t* arr, u8_t arrSize);


int main()
{
    u32_t TestCase1[15]={3,44,38,5,47,15,36,26,27,2,46,4,19,50,48}; // Unsorted array test case
    u32_t TestCase2[10]={2,4,6,8,9,11,13,14,15,16};  //Sorted Test Case
    u32_t u32_InputArr[255];
    u8_t u8_ReturnedIndex,u8_userInput='y';
    u32_t u32_SearchNum;

    /**< The first Test Case */
    printf("The First Test Case:  Unsorted Array \n");
    u8_printArray(TestCase1,15);

    /**< Check if the array is already sorted if not the sort it before searching */
    if (!u8_IsSorted(TestCase1, 15))
    {
        printf("I did Sorting First\n");
        void_InsertionSort(TestCase1, 15);
    }else{
        //NOP
    }

    /**< Do binary search on the sorted array the save the index */
    u8_ReturnedIndex=binarySearch(TestCase1,15,50);

    /**< check if the return is not NUM_NOT_FOUND then print the index otherwise print not found */
    if (u8_ReturnedIndex==NUM_NOT_FOUND)
    {
        printf("The number is not in the array\n");
    }else{
        printf("Found the number on index: %d\n",u8_ReturnedIndex);
    }

    /**< The second Test Case */
    printf("The Second Test Case:  Sorted Array \n");
    u8_printArray(TestCase2,10);
    if (!u8_IsSorted(TestCase2, 10))
    {
        printf("I did Sorting First\n");
        void_InsertionSort(TestCase2, 10);
    }else{
        //NOP
    }
    u8_ReturnedIndex=binarySearch(TestCase2,10,50);

    if (u8_ReturnedIndex==NUM_NOT_FOUND)
    {
        printf("The number is not in the array\n");
    }else{
        printf("Found the number on index: %d\n",u8_ReturnedIndex);
    }



    /**< Ask the user if he wants to enter another test case if yes take his inputs */
    while (u8_userInput=='y')
    {
        printf("Enter Your Test Case Array Size");
        scanf("%d",&u8_userInput);

        /**< check if the input is in the allowed range */
        if (u8_userInput<MAX_ARRAY_SIZE)
        {
            /**< if yes ask the user to input his array */
            printf("Enter you Array: \n");
            for (u8_t counter=0;counter<u8_userInput;counter++)
            {
                fflush(stdin);
                scanf("%d",&u32_InputArr[counter]);
            }

            printf("Enter A number To Search: ");
            scanf("%d",&u32_SearchNum);


            if (!u8_IsSorted(u32_InputArr, u8_userInput))
            {
                printf("I did Sorting First The array became: \n");
                void_InsertionSort(u32_InputArr, u8_userInput);
                u8_printArray(u32_InputArr,u8_userInput);
            }else{
                //NOP
            }
            u8_ReturnedIndex=binarySearch(u32_InputArr,u8_userInput,u32_SearchNum);

            if (u8_ReturnedIndex==NUM_NOT_FOUND)
            {
                printf("The number is not in the array\n");
            }else{
                printf("Found the number on index: %d\n",u8_ReturnedIndex);
            }
        }
        else {
            printf("The input size is invalid make sure it is less than 255\n");
        }

        printf("Do you want to Enter your test case (y/n)?");
        fflush(stdin);
        scanf("%c",&u8_userInput);
    }

    return 0;
}



void u8_printArray(u32_t* arr, u8_t arrSize)
{
    for (u8_t counter=0; counter<arrSize;counter++)
    {
        printf("%d\t",arr[counter]);
    }
    printf("\n");
}
