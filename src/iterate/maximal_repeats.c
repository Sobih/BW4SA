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
#include "../bwt/map_bwt_to_s.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/utils.h"
#include "../../include/mapper.h"

char* max_bwt;
bit_vector* max_repeats_runs;
max_repeat_node** nodes;
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
	max_bwt = bwt;
	max_repeats_runs = create_runs_vector_from_bwt(bwt);
	nodes = calloc(100,sizeof(max_repeat_node));
}

int is_interval_left_maximal(Interval* interval) {
	if (interval->i >= interval->j)
		return 0;

	if (max_repeats_runs->rank_interval(max_repeats_runs, (interval->i) + 1,
			interval->j) > 0) {
		return 1;
	} else {
		return 0;
	}
}

void search_maximal_repeats(substring* node) {
	if (is_interval_left_maximal(node->normal)) {
		max_repeat_node* max_node = malloc(sizeof(max_repeat_node));
		max_node->normal = node->normal;
		max_node->length = node->length;
		nodes[nodes_index] = max_node;
		nodes_index++;
	}
}

max_repeat_node** get_nodes() {
	return nodes;
}

char *substring_from_string(char *string, int position, int length) {
	char *pointer;
	int i;
	int pointer_index = 0;

	pointer = malloc(length + 1);

	printf("position: %d \n",position);

	for (i = position; i < position + length; i++) {
		pointer[pointer_index] = string[i];
		pointer_index++;
	}
	pointer[pointer_index] = '\0';

	return pointer;
}

void print_maximal_repeat_substrings(char* string) {
	map_maximal_repeats_to_string(nodes, max_bwt);
	int i;
	int count = get_max_repeats_nodes_index();

	for (i = 0; i < count; i++) {
		printf("%s \n",
				substring_from_string(string, nodes[i]->normal->i,
						nodes[i]->length));
	}
}

void map_to_string_and_print(max_repeat_node* node, char* string) {
	int* suffix_array = map_create_suffix_array_from_bwt(max_bwt);
	int str_length = strlen(max_bwt);
	int bwt_index_i = node->normal->i;
	int bwt_index_j = node->normal->j;
	int* indexes_in_string = malloc(str_length * sizeof(int));
	int index_array_i = 0;
	char* node_as_string = malloc(str_length);
	int i;
	for (i = 0; i < str_length; i++) {
		if (i == bwt_index_i) {
			node_as_string = substring_from_string(string, suffix_array[i],
					node->length);
			printf("Substring: %s\n", node_as_string);
		}
		if (i >= bwt_index_i && i <= bwt_index_j) {
			indexes_in_string[index_array_i] = suffix_array[i];
			index_array_i++;
		}
		if (i == bwt_index_j) {
			quick_sort(indexes_in_string, index_array_i, sizeof(int));
			printf("Indexes in string: ");
			int j;
			for (j = 0; j < index_array_i - 1; j++) {
				printf("%d, ", indexes_in_string[j]);
			}
			printf("%d\n", indexes_in_string[index_array_i - 1]);
		}
	}
}

void maximals_print_nodes(char* string) {
	int i;
	printf("Maximal repeats: \n");
	for (i = 0; i < nodes_index; i++) {
		map_to_string_and_print(nodes[i], string);
	}
}

int get_max_repeats_nodes_index() {
	return nodes_index;

}
