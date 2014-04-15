/**
 * @file	mems.c
 * @brief	Implementation of the functions for finding MEMs using iterate.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "mems.h"
#include "../../include/utils.h"
#include "../../include/core.h"
#include "../../include/applications.h"
#include "../core/c_array.h"
#include "../core/backward_search.h"
#include "mapper.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief	A structure for storing a possible MEM.
 * @author	Topi Paavilainen
 */
typedef struct mem_candidate {
	substring extension;
	char first;
	char last;
} mem_candidate;

/**
 * @brief	A structure for storing the variables used by the MEM-search.
 * @author	Max Sandberg (REXiator)
 */
typedef struct mem_parameters {
	interval normal_left, normal_right;
	interval reverse_left, reverse_right;
	alphabet_data alpha_data_left, alpha_data_right;
} mem_parameters;

parameter_struct* initialize_for_mems(char** strings) {
	mem_results* results = malloc(sizeof(mem_results));
	results->length = 0;
	results->allocated_length = 10;
	results->data = malloc(results->allocated_length * sizeof(triplet));

	mem_parameters* mem_params = malloc(sizeof(mem_parameters));
	mem_params->alpha_data_left->alphabet = mem_params->alpha_data_right->alphabet = 0;
	results->params = mem_params;

	parameter_struct* params = malloc(sizeof(parameter_struct));
	params->callback = &search_mems;
	params->iterate_type = MEM;
	params->strings = strings;
	params->ret_data = results;

	return params;
}

/**
 * @brief	A function for finding potential MEMs.
 * @param	node			The current substring being searched.
 * @param	bwt				The BWT of a string, represented as a wavelet tree.
 * @param	rbwt			The BWT of the reverse of a string, represented as a wavelet tree.
 * @param	mem_candidates	The current list of possible MEMs being searched.
 * @param	mem_params		The parameters used by the MEM search.
 * @return					Returns the length of the list of MEM candidates.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int list_mem_candidates(substring* node, wavelet_tree* bwt, wavelet_tree* rbwt,
		mem_candidate* mem_candidates, mem_parameters* mem_params) {
	interval* normal_left = &mem_params->normal_left;
	interval* reverse_left = &mem_params->reverse_left;
	interval* normal_right = &mem_params->normal_right;
	interval* reverse_right = &mem_params->reverse_right;

	mem_candidate* candidate;

	alphabet_data* alpha_data_left = create_alphabet_interval(&node->normal,
			bwt, &mem_params->alpha_data_left);
	alphabet_data* alpha_data_right = &mem_params->alpha_data_right;

	int alphabet_length = alpha_data_left->length;

	unsigned int* c_array_left = create_c_array(bwt, &node->normal, 0, 0, 0);
	unsigned int* c_array_right = malloc((alphabet_length + 1) * sizeof(unsigned int));

	int index = 0;

	for (int i = 0; i < alphabet_length; i++) {
		normal_left = backward_search_interval(bwt, &node->normal,
				alpha_data_left->alphabet[i], normal_left);
		reverse_left = update_reverse_interval(&node->reverse, normal_left,
				alpha_data_left->alphabet, alphabet_length, c_array_left,
				alpha_data_left->alphabet[i], reverse_left);

		alpha_data_right = create_alphabet_interval(reverse_left, rbwt, alpha_data_right);
		c_array_right = create_c_array(rbwt, reverse_left, 0, 0, c_array_right);

		for (int j = 0; j < alpha_data_right->length; j++) {
			candidate = &mem_candidates[index];

			reverse_right = backward_search_interval(rbwt, reverse_left,
					alpha_data_right->alphabet[j], reverse_right);
			normal_right = update_reverse_interval(normal_left, reverse_right,
					alpha_data_right->alphabet, alpha_data_right->length,
					c_array_right, alpha_data_right->alphabet[j], normal_right);

			create_substring(normal_right, reverse_right, node->length, &candidate->extension);
			candidate->first = alpha_data_left->alphabet[i];
			candidate->last = alpha_data_right->alphabet[j];

			index++;
		}
	}

	free(alpha_data_left->alphabet);
	free(alpha_data_right->alphabet);
	alpha_data_left->alphabet = alpha_data_right->alphabet = 0;

	free(c_array_left);
	free(c_array_right);

	return index;
}

void search_mems(iterator_state* state, void* results) {
	mem_results* result = (mem_results*) results;
	mem_parameters* params = (mem_parameters*) result->params;

	//check if triplet-list is full, expand by 10 if it is
	if (result->allocated_length == result->length) {
		result->allocated_length += 10;
		result->data = realloc(result->data, result->allocated_length * sizeof(triplet));
	}

	triplet* mems = result->data;

	substring* node1 = &state->current[0], *node2 = &state->current[1];

	mem_candidate* mem_candidates1 = malloc((node1->normal.j - node1->normal.i + 1) * sizeof(mem_candidate));
	mem_candidate* mem_candidates2 = malloc((node2->normal.j - node2->normal.i + 1) * sizeof(mem_candidate));

	int index1 = list_mem_candidates(node1, &state->bwts[0], &state->reverse_bwts[0], mem_candidates1);
	int index2 = list_mem_candidates(node2, &state->bwts[1], &state->reverse_bwts[1], mem_candidates2);

	for (int i = 0; i < index1; i++) {
		for (int j = 0; j < index2; j++) {
			if ((mem_candidates1[i].first != mem_candidates2[j].first || mem_candidates1[i].first == '$')
					&& (mem_candidates1[i].last != mem_candidates2[j].last || mem_candidates1[i].last == '$')) {
				for (int k = mem_candidates1[i].extension.normal.i;
						k <= mem_candidates1[i].extension.normal.j; k++) {
					for (int l = mem_candidates2[j].extension.normal.i;
							l <= mem_candidates2[j].extension.normal.j; l++) {
						triplet* trip = mems[result->length];
						trip->pos1 = k;
						trip->pos2 = l;
						trip->length = node1->length;
						result->length++;
					}
				}
			}
		}

//		printf("First char: %c\n", mem_candidates1[i].first);
//		printf("Last char: %c\n", mem_candidates1[i].last);
//		print_node(&mem_candidates1[i].extension);
	}

	free(mem_candidates1);
	free(mem_candidates2);
}

void print_mems(char* string, mem_results* results, iterator_state* state) {
	triplet* mems = results->data;

	int i;
	for (i = 0; i < results->length; i++) {
		triplet trip = mems[i];
		printf(
				"Index in the BWT first string: %d\nIndex in the BWT second string: %d\nLength: %d \n",
				trip.pos1, trip.pos2, trip.length);
	}

	map_mum_triplets_to_string(mems, &state->bwts[0], &state->bwts[1], results->length);

	for(int i = 0; i < results->length; i++){
		mems[i].pos1 = mems[i].pos1 + 1;
		mems[i].pos2 = mems[i].pos2 + 1;
	}

	for (i = 0; i < results->length; i++) {
		triplet trip = mems[i];
		printf(
				"Index in the first string: %d\nIndex in the second string: %d\nLength: %d \n",
				trip.pos1, trip.pos2, trip.length);
		char* subs = substring_from_string(string, trip.pos1, trip.length);
		printf("The substring itself: %s \n", subs);
		printf("\n\n");
	}
}
