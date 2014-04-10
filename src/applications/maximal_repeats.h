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

typedef struct max_repeat_results {
	max_repeat_node* data;
	unsigned int length;
	unsigned int allocated_length;
} max_repeat_results;

struct parameter_struct* initialize_for_max_repeats(char* string);

/**
 * @brief	The function given as callback to iterate for finding maximal repeats.
 *
 * Determines if a node is a maximal repeat and adds it to a list.
 *
 * @param 	node	A substring node that contains the intervals inside the BWT
 * 					and the BWT of the reverse of the string.
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
 * @param	string	The original c-string.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_maximal_repeat_substrings(char* string, max_repeat_results* results, struct iterator_state* state);

#endif /* MAXIMAL_REPEATS_H_ */
