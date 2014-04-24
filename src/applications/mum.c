/**
 * @file	mum.c
 * @brief	Implementation of the algorithms related to maximal unique matches.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "mum.h"
#include "mapper.h"
#include "../core/iterate.h"
#include "../../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


parameter_struct* initialize_for_mums(char** strings, int max_number_mums) {
	mum_results* results = malloc(sizeof(mum_results));
	results->length = 0;
	results->allocated_length = max_number_mums;
	results->data = malloc(results->allocated_length * sizeof(triplet));

	parameter_struct* params = malloc(sizeof(parameter_struct));
	params->callback = &search_mums;
	params->iterate_type = MUM;
	params->strings = strings;
	params->ret_data = results;

	return params;
}

void search_mums(iterator_state* state, void* results) {
	mum_results* result = (mum_results*) results;
	substring* node1 = &state->current[0], *node2 = &state->current[1];
	wavelet_tree* mum_bwt1 = &state->bwts[0], *mum_bwt2 = &state->bwts[1];
	wavelet_tree* mum_rbwt1 = &state->reverse_bwts[0], *mum_rbwt2 = &state->reverse_bwts[1];

	//check if triplet-list is full, expand by 10 if it is
	if (result->allocated_length == result->length) {
		result->allocated_length += 10;
		result->data = realloc(result->data, result->allocated_length * sizeof(triplet));
	}

	if (node1->normal.i == node1->normal.j) {
		if (node2->normal.i == node2->normal.j) {
			if ((mum_bwt1->char_at(mum_bwt1,node1->normal.i) != mum_bwt2->char_at(mum_bwt2,node2->normal.i))||
					mum_bwt1->char_at(mum_bwt1, node1->normal.i) == '$') {
				if ((mum_rbwt1->char_at(mum_rbwt1,node1->reverse.i)
						!= mum_rbwt2->char_at(mum_rbwt2,node2->reverse.i)) ||
						mum_rbwt1->char_at(mum_rbwt1, node1->reverse.i) == '$') {

					triplet* trip = &result->data[result->length];
					trip->pos1 = node1->normal.i;
					trip->pos2 = node2->normal.i;
					trip->length = node1->length;
					result->length++;
				}
			}
		}
	}
}

void print_mums(char* string, mum_results* results, iterator_state* state) {
	int i;
	for (i = 0; i < results->length; i++) {
		triplet trip = results->data[i];
		printf(
				"Index in the BWT first string: %d\nIndex in the BWT second string: %d\nLength: %d \n",
				trip.pos1, trip.pos2, trip.length);
	}
	map_mum_triplets_to_string(results->data, &state->bwts[0], &state->bwts[1], results->length);
	for (i = 0; i < results->length; i++) {
		triplet trip = results->data[i];
		printf(
				"Index in the first string: %d\nIndex in the second string: %d\nLength: %d \n",
				trip.pos1, trip.pos2, trip.length);
		char* subs = substring_from_string(string, trip.pos1, trip.length);
		printf("The substring itself: %s \n", subs);
	}
}

bit_vector** mum_make_bit_vectors(mum_results* results, iterator_state* state) {
	bit_vector** vectors = calloc(sizeof(bit_vector),2);
	bit_vector* bit_vector1 = malloc(sizeof(bit_vector));
	init_bit_vector(bit_vector1, state->bwts[0].get_num_bits(&state->bwts[0]));
	bit_vector* bit_vector2 = malloc(sizeof(bit_vector));
	init_bit_vector(bit_vector2, state->bwts[1].get_num_bits(&state->bwts[1]));
	int i;
	for (i = 0; i < results->length; i++) {
		triplet trip = results->data[i];
		bit_vector1->mark_bit(bit_vector1, trip.pos1);
		bit_vector2->mark_bit(bit_vector2, trip.pos2);
	}
	vectors[0] = bit_vector1;
	vectors[1] = bit_vector2;
	return vectors;
}

/**
 * @brief	A simple function for printing a bit vector with the c-string
 * 			that is related to it to stdout.
 * @param	string1	The string related to the vector.
 * @param	vector	The bit vector to be printed.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_bit_vector_with_string(char* string1, bit_vector* vector) {
	printf("%s \n", string1);
	int i;
	int length = strlen(string1);
	for (i = 0; i < length; i++) {
		if (vector->is_bit_marked(vector, i)) {
			printf("1");
		} else {
			printf("0");
		}
	}
	printf("\n");
}

void mum_print_bit_vectors(char* string1, char* string2, mum_results* results, iterator_state* state) {
	bit_vector** vectors = mum_make_bit_vectors(results, state);

	print_bit_vector_with_string (string1,vectors[0]);
	print_bit_vector_with_string (string2,vectors[1]);
}
