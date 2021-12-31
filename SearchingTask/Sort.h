#ifndef __SORT_H_
#define __SORT_H_

#define ARRAY_UNSORTED 0
#define ARRAY_SORTED   1

/** \brief this function test if the array is sorted or not
 *
 * \param au32_arr an   array of u32_t
 * \param u8_arrSize    the number of array elements
 * \return ARRAY_UNSORTED if the array is not sorted and ARRAY_SORTED if it is already sorted
 *
 */

u8_t u8_IsSorted(u32_t* au32_arr, u8_t u8_arrSize);

/** \brief this function is used to sort the array using the insertion algorithm
 *
 * \param au32_arr an   array of u32_t
 * \param u8_arrSize    the number of array elements
 * \return void
 *
 */

void void_InsertionSort(u32_t* arr, u8_t arrSize);

#endif // __SORT_H_
