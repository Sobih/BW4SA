/*
 * maximal_repeats.h
 *
 *  Created on: 26.2.2014
 *      Author: lvapaaka
 */

#ifndef MAXIMAL_REPEATS_H_
#define MAXIMAL_REPEATS_H_

#include "structs.h"

struct wavelet_tree;

typedef struct max_repeat_node
{
	interval normal;
	int length;
} max_repeat_node;

/**
 * @brief 		Initializes the BWT for the file so that callback doesn't require passing it on.
 *
 * @param 		BWT of the searched string
 */
void max_repeats_initialize_bwt(struct wavelet_tree* bwt);

/**
 * @brief 		The function given to callback. Determines if a node is a maximal repeat and adds it to a list.
 *
 * @param 		A substring node that has the intervals in BWT and BWT of the reverse of the string.
 */
void search_maximal_repeats(substring* node);

/**
 * @brief 		Returns the list of maximal repeat nodes.
 *
 * @return		List of found maximal repeats as nodes that hold a BWT interval and length of substring.
 */
max_repeat_node* get_nodes();

/**
 * @brief		Prints the substring the interval represents
 *
 * First uses the mapper-function map_maximal_repeats_to_string and then prints the substring based on the mapped index.
 *
 * @param		string			Original string.
 * @bug			No known bugs.
 */
void print_maximal_repeat_substrings(char* string);

/**
 * @brief 		Returns the size of the node list.
 *
 * @return		Size of the node list. Same as number of found maximal repeats.
 */
int get_max_repeats_nodes_index();

#endif /* MAXIMAL_REPEATS_H_ */
