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
 * @brief 	Initializes the BWT for the file so that callback doesn't require passing it on.
 *
 * Has to be called before iteration can commence!
 *
 * @param 	bwt 	BWT of the string to be iterated upon.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void max_repeats_initialize_bwt(struct wavelet_tree* bwt);

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
void search_maximal_repeats(struct substring* node);

/**
 * @brief 	Returns the list of maximal repeat substrings.
 * @return	A list of found maximal repeat substrings as nodes that hold
 * 			a BWT interval and length of substring.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
max_repeat_node* get_nodes();

struct max_repeat_with_indexes* get_max_repeats_with_indexes();

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
void print_maximal_repeat_substrings(char* string);

/**
 * @brief 	Returns the size of the list of substrings.
 * @return	Size of the node list. Same as number of found maximal repeats.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int get_max_repeats_nodes_index();

struct bit_vector* max_repeat_make_bit_vector(max_repeat_node* nodes);

#endif /* MAXIMAL_REPEATS_H_ */
