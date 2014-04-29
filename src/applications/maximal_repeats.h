/**
 * @file	maximal_repeats.h
 * @brief	A collection of functions for manipulating maximal repeat substrings.
 * @see		iterate.h
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef MAXIMAL_REPEATS_H_
#define MAXIMAL_REPEATS_H_

#include "../utils/structs.h"

struct wavelet_tree;
struct bit_vector;
struct substring;
struct interval;
struct max_repeat_node_with_indexes;
struct parameter_struct;
struct iterator_state;

/**
 * @brief	A simple struct for storing data on a maximal repeat substring.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct max_repeat_node
{
	interval normal;
	int length;
} max_repeat_node;

/**
 * @brief	A struct for storing the results of the callback function given
 * 			to iterate.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct max_repeat_results {
	max_repeat_node* data;
	unsigned int length;
	unsigned int allocated_length;
} max_repeat_results;

/**
 * @brief	An initialization function that creates a parameter struct that
 * 			instructs iterate to search for maximal repeats.
 * @param	string	The string that should be iterated over.
 * @return			An initialized parameter struct ready to be passed to
 * 					iterate.
 * @see		iterate.h#parameter_struct
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct parameter_struct* initialize_for_max_repeats(char* string, int threshold);

/**
 * @brief	The function given as callback to iterate for finding maximal repeats.
 *
 * Determines if a node is a maximal repeat and adds it to a list.
 *
 * @param 	state		The internal state of the iterator.
 * @param	results		A pointer to a region of memory where previous results for
 * 						this function can be found. Can safely be cast to <code>max_repeat_results</code>
 * 						if iterate was initialized using <code>initialize_for_max_repeats()</code>.
 * @see		#initialize_for_max_repeats
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void search_maximal_repeats(struct iterator_state* state, void* results);

/**
 * @brief	Prints the substring the interval represents.
 *
 * First uses the mapper-function <code>map_maximal_repeats_to_string()</code> and then prints
 * the substring based on the mapped index to stdout.
 *
 * @param	string		The original c-string.
 * @param	results		Results of iterating over the c-string to find maximal repeats.
 * @param	state		The internal state of the iterator performing the search.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_maximal_repeat_substrings(char* string, max_repeat_results* results, struct iterator_state* state);

/**
 * @brief	Creates a bit vectors based on the given string, where marked bits
 * 			correspond to starting indexes of maximal repeats inside the string.
 *
 * @param	results		The results of an iteration over a set of strings.
 * @param	state		Internal state of the iterator that performed the search.
 * @return 				Bit vectors with starts of Maximal repeats marked.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct bit_vector* max_repeat_make_bit_vector(max_repeat_results* results, struct iterator_state* state);

#endif /* MAXIMAL_REPEATS_H_ */
