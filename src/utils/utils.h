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

#ifndef UTILITIES_H_
#define UTILITIES_H_

struct wavelet_tree;
struct wavelet_node;
struct bit_vector;
struct substring;
struct interval;

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

/**
 * @brief	Returns a substring char array from the given char array.
 *
 * @param	string		The whole string
 * @param	position	Starting position of the substring
 * @param	length		Length of the substring
 * @bug		No known bugs.
 */
char *substring_from_string(char *string, int position, int length);

/**
* @brief creates vector runs from given string
*
* @param string normal string (rbwt is generated from it)
*
* @return pointer to runs vector
*
* @author Topi Paavilainen
*
* @bug no known bugs
**/
struct bit_vector* create_runs_vector(const struct wavelet_tree* string, struct bit_vector* target);

/**
 * @brief Creates a substring struct from interval and length.
 * @param interval in normal BWT
 * @param interval in the BWT of the reverse of the string
 * @param length of substring
 *
 * @return pointer to a new substring struct
 */
struct substring* create_substring(struct interval* normal, struct interval* reverse, int length,
		struct substring* target);

/**
 * Updates the interval in the BWT of the reverse of the string
 * @param reverse-BWT interval of the mother node
 * @param updated BWT interval in this node
 * @param alphabet in the interval
 * @param array C of the interval
 * @param extension character
 * @return a new updated Interval struct in the BWT of the reverse of the string
 */
struct interval* update_reverse_interval(struct interval* inter, struct interval* normal,
		const char* alphabet, unsigned int alphabet_length, const int* c_array,
		const char c, struct interval* target);

#endif /* UTILITIES_H_ */
