#ifndef __SEARCH_H_
#define __SEARCH_H_

#define NUM_NOT_FOUND   255

/** \brief this function is used to Search the array for a number using the binary search algorithm
 *
 * \param au32_arr      an array of u32_t
 * \param u8_arrSize    the number of array elements
 * \return return a u8_t number represent the index of the number found or -1 if not found
 *
 */
u8_t binarySearch(u32_t* arr,u8_t size,u32_t number);

#endif // __SEARCH_H_
