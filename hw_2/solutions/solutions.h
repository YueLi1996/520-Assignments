#ifndef SOLUTIONS_H
#define SOLUTIONS_H
#include <stdlib.h>



/*! Keep track of the sum of the arguments it has been called with over time
 *  \param num The integer number
 */
int running_total (int num);

/*! takes an array and its length, and returns a new array that is the reverse of the given arra
 *  \param array a pointer pointing to the first index of an array
 *  \param size length of the array
 */
int* reverse (int* array, int size);

/*!  takes an array and its length, and reverses it in place.
 *  \param array a pointer pointing to the first index of an array
 *  \param size length of the array
 */
void reverse_in_place (int* array, int size);

/*!  takes an array of integers, a length, and a value and returns the number of occurences of that value in the array.
 *  \param array a pointer pointing to the first index of an array
 *  \param size length of the array
 *  \param value target value
 */
int num_occurences  (int* array, int size, int value);

#endif