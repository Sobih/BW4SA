/**
 * @file	utils.h
 * @brief	A collection of useful helper-functions.
 *
 * This file contains some useful generic helper functions, like sorting,
 * searching, etc.
 *
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef UTILS_H_
#define UTILS_H_

/**
 * @brief	Standard generic quicksort-implementation.
 *
 * This is a standard quicksort-algorithm that can be used for any data-type.
 * It sorts the contents of an array in ascending order.
 *
 * @param	arr			Pointer to the array to be sorted.
 * @param	arr_size	Size of the array to be sorted.
 * @param	entry_size	Size of the individual entries in the array.
 * @return				Returns the sorted array.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void quick_sort(void* arr, unsigned int arr_size, unsigned int entry_size);

/**
 * @brief	A small function that prints the bits of an unsigned
 * 			int.
 * @param	mask		The unsigned integer whose bit value will
 * 						be printed.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_bits(unsigned int mask);

#endif /* UTILS_H_ */
