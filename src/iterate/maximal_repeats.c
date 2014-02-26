/*
 * maximal_repeats.c
 *
 *  Created on: 26.2.2014
 *      Author: lvapaaka
 */

#include "../../include/bit_vector.h"
#include "print_node.h"
#include "../../include/backward_search.h" // only for interval
#include "../../include/iterate.h" // only for substring
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bit_vector* max_repeats_runs;
substring* nodes[100];
int nodes_index = 0;

bit_vector* create_runs_vector_from_bwt(char* bwt) {
	bit_vector* runs = malloc(sizeof(bit_vector));
	init_bit_vector(runs, strlen(bwt));

	runs->mark_bit(runs, 0);
	for (int i = 1; i < strlen(bwt); i++) {
		if (bwt[i - 1] != bwt[i]) {
			runs->mark_bit(runs, i);
		}
	}
	return runs;
}

void max_repeats_initialize_bwt(char* bwt) {
	max_repeats_runs = create_runs_vector_from_bwt(bwt);
}

int is_interval_left_maximal(Interval* interval) {
	if (interval->i >= interval->j)
		return 0;

	if (max_repeats_runs->rank_interval(max_repeats_runs, (interval->i) + 1, interval->j) > 0) {
		return 1;
	} else{
		return 0;
	}
}


void search_maximal_repeats(substring* node) {
	if(is_interval_left_maximal(node->normal)){
		nodes[nodes_index] = node;
		nodes_index++;
	}
}

substring** get_nodes(){
	return nodes;
}

void maximals_print_nodes(){
	int i;
	for(i = 0; i< nodes_index;i++){
		print_node(nodes[i]);
	}
}
