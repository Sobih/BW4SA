/**
 * @file	maximal_repeats.c
 * @brief	Implementation of the functions related to maximal repeats.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "maximal_repeats.h"
#include "map_bwt_to_s.h"
#include "mapper.h"
#include "../../include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static wavelet_tree* max_bwt;
static bit_vector* max_repeats_runs;
static max_repeat_node* nodes;
static int nodes_index;

//bit_vector* max_repeats_in_bwt;

void max_repeats_initialize_bwt(wavelet_tree* bwt) {
	max_bwt = bwt;
	max_repeats_runs = create_runs_vector(bwt,0);
	nodes = calloc(1000,sizeof(max_repeat_node));
	nodes_index = 0;
}

/**
 * @brief	A simple function for determining if an interval is right maximal.
 * @param	inter	The interval to be checked.
 * @return			<code>1</code> if the interval is a maximal repeat, <code>0</code>
 * 					otherwise.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int is_interval_left_maximal(interval inter) {
	if (inter.i >= inter.j)
		return 0;

	if (max_repeats_runs->rank(max_repeats_runs, (inter.i) + 1,
			inter.j) > 0) {
		return 1;
	} else {
		return 0;
	}
}

void search_maximal_repeats(substring* node) {
	if (is_interval_left_maximal(node->normal)) {
		max_repeat_node max_node = *((max_repeat_node*) malloc(sizeof(max_repeat_node)));
		max_node.normal.i = node->normal.i;
		max_node.normal.j = node->normal.j;
		max_node.length = node->length;
		nodes[nodes_index] = max_node;
		nodes_index++;
	}
}

max_repeat_node* get_nodes() {
	return nodes;
}

void print_maximal_repeat_substrings(char* string) {
	map_maximal_repeats_to_string(nodes, max_bwt, nodes_index);
	int i;

	for (i = 0; i < nodes_index; i++) {
		printf("String: %s, starting position: %d, length of substring: %d \n", string, nodes[i].normal.i, nodes[i].length);
		printf("Substring: %s index:%d length: %d \n",
				substring_from_string(string, nodes[i].normal.i,
						nodes[i].length), nodes[i].normal.i, nodes[i].length);
	}
}

int get_max_repeats_nodes_index() {
	return nodes_index;

}
