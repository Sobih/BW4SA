/**
 * @file	utils.h
 * @brief	A collection of useful helper-functions.
 *
 * This file contains some useful generic helper functions, like sorting,
 * searching, etc.
 *
 * @author	Max Sandberg (REXiator), Paula Lehtola
 * @bug		No known bugs.
 */

#ifndef UTILS_H_
#define UTILS_H_

struct wavelet_tree;
struct wavelet_node;
struct bit_vector;

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

/**
 * @brief	quicksort for an array of strings
 * @param	strings 	array of pointers of strings
 * @param	a	index of the first entry to be sorted
 * @param	b	index of the last entry to be sorted
 * @see		utils.h#quick_sort
 * @author	Paula Lehtola
 * @bug		No known bugs.
 */
void string_quick_sort(char **strings, unsigned int arr_size);

/**
 * @brief	Determines the alphabet used by a string.
 *
 * Determines the alphabet used by a string. The alphabet of a string is
 * defined as the characters used in the string, including all special
 * characters.
 *
 * @param	string	The string from which the alphabet should be deduced.
 * @return			The alphabet used by the string.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char* determine_alphabet(const char* string);

/**
 * @brief	A generic implementation of a standard binary search-algorithm.
 * @param	arr			A pointer to an array of any type upon which the
 * 						search is to be done.
 * @param	key			A pointer to a value that is to be found inside the
 * 						array.
 * @param	min			The minimum index that is to be searched.
 * @param	max			The maximum index that is to be searched.
 * @param	entry_size	The size of the type of the key.
 * @return				Returns the index of the key inside the array, or -1
 * 						if the array doesn't contain the key.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int binary_search(const void* arr, const void* key, unsigned int entry_size,
		int max, int min);

/**
 * @brief	Prints the bits of an unsigned int.
 * @param	mask	The unsigned int whose bits are to be printed.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_bits(unsigned int mask);

/**
 * @brief	A simple function that prints a bit vector and its' contents to
 * 			stdout.
 * @param	vector		The bit vector that is to be printed.
 * @see		bit_vector.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_bit_vector(struct bit_vector* vector);

/**
 * @brief	A simple function that prints a node in a wavelet tree to stdout.
 * @param	node		The node that is to be printed.
 * @see		wavelet_tree.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_wavelet_node(struct wavelet_node* node);

/**
 * @brief	Prints an entire wavelet tree.
 *
 * Prints the contents of an entire wavelet (sub)tree, printing one level
 * of depth at a time.
 *
 * @param	node		The node at which the (sub)tree that is to be
 * 						printed starts.
 * @see		wavelet_tree.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_wavelet_tree(struct wavelet_tree* tree);

#endif /* UTILS_H_ */
