/**
 * @file	maximal_repeats.c
 * @brief	Implementation of the functions related to maximal repeats.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "maximal_repeats.h"
#include "map_bwt_to_s.h"
#include "mapper.h"
#include "../core/iterate.h"
#include "../../include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

parameter_struct* initialize_for_max_repeats(char* string) {
	max_repeat_results* results = malloc(sizeof(max_repeat_results));
	results->length = 0;
	results->allocated_length = 10;
	results->data = malloc(results->allocated_length * sizeof(max_repeat_node));

	parameter_struct* params = malloc(sizeof(parameter_struct));
	params->callback = &search_maximal_repeats;
	params->iterate_type = MAX_REPEATS;
	params->strings = malloc(sizeof(char*));
	params->strings[0] = string;
	params->ret_data = results;

	return params;
}

/**
 * @brief	A simple function for determining if an interval is right maximal.
 * @param	inter	The interval to be checked.
 * @return			<code>1</code> if the interval is a maximal repeat, <code>0</code>
 * 					otherwise.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
inline int is_interval_left_maximal(bit_vector* runs, interval inter) {
	return (inter.i < inter.j) && (runs->rank(runs, inter.i + 1, inter.j) > 0) ? 1 : 0;
}

void search_maximal_repeats(iterator_state* state, void* results) {
	max_repeat_results* result = (max_repeat_results*) results;
	substring* node = state->current;

	//check if nodes-list is full, expand by 10 if it is
	if (result->allocated_length == result->length) {
		result->allocated_length += 10;
		result->data = realloc(result->data, result->allocated_length * sizeof(max_repeat_node));
	}

	if (is_interval_left_maximal(node->normal)) {
		max_repeat_node* res_node = &result->data[result->length];
		res_node->normal.i = node->normal.i;
		res_node->normal.j = node->normal.j;
		res_node->length = node->length;
		result->length++;
	}
}

void print_maximal_repeat_substrings(char* string, max_repeat_results* results, iterator_state* state) {
	max_repeat_node* nodes = results->data;
	wavelet_tree* max_bwt = state->bwts;
	unsigned int nodes_index = results->length;

	map_maximal_repeats_to_string(nodes, max_bwt, nodes_index);

	for (int i = 0; i < nodes_index; i++) {
		printf("String: %s, starting position: %d, length of substring: %d \n", string, nodes[i].normal.i, nodes[i].length);
		printf("Substring: %s index:%d length: %d \n",
				substring_from_string(string, nodes[i].normal.i,
						nodes[i].length), nodes[i].normal.i, nodes[i].length);
	}
}
