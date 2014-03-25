/**
 * @file	triplet_sorter.h
 * @brief	Quicksort that takes compare function as a parameter. Compare functions are made for triplets (for pos1 and pos2) and for max_repeat_nodes.
 * @bug		No known bugs.
 */

#ifndef TRIPLET_SORTER_H_
#define TRIPLET_SORTER_H_

/**
 * @brief	
 *	A compare function for compare_quick_sort. Compares triplets by the value of pos1.
 *
 * @param	first	a void pointer which will be converted to a triplet pointer
 * @param	second	a void pointer which will be converted to a triplet pointer
 * @see		triplet_sorter.h#compare_quick_sort
 * @author	Paula Lehtola
 * @bug		No known bugs.
 */
int compare_triplets_pos1(void* first, void* second);

/**
 * @brief	
 *	A compare function for compare_quick_sort. Compares triplets by the value of pos2.
 *
 * @param	first	a void pointer which will be converted to a triplet pointer
 * @param	second	a void pointer which will be converted to a triplet pointer
 * @see		triplet_sorter.h#compare_quick_sort
 * @author	Paula Lehtola
 * @bug		No known bugs.
 */
int compare_triplets_pos2(void* first, void* second);

/**
 * @brief	
 *	A compare function for compare_quick_sort. Compares max_repeat_nodes by comparing first the i values of the interval, and if they are equal, compares the j values.
 *
 * @param	first	a void pointer which will be converted to a max_repeat_node pointer
 * @param	second	a void pointer which will be converted to a max_repeat_node pointer
 * @see		triplet_sorter.h#compare_quick_sort
 * @author	Paula Lehtola
 * @bug		No known bugs.
 */
int compare_max_repeat_nodes(void* first, void* second);

/**
 * @brief	A quicksort which uses a comparison function which has been given as a function pointer parameter.
 *
 *
 * @param	arr			Pointer to the array to be sorted.
 * @param	arr_size	Size of the array to be sorted.
 * @param	entry_size	Size of the individual entries in the array.
 * @param	compare		A function pointer for the comparison functions.	
 * @return				Returns the sorted array.
 * @bug					No known bugs.
 */

void compare_quick_sort(void* arr, unsigned int arr_size, unsigned int entry_size, int (*compare)(void* first, void* second));

#endif /* TRIPLET_SORTER_H_ */
