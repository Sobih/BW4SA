/*
 * mems.c
 *
 *  Created on: 3.4.2014
 *      Author: lvapaaka
 */

#include "../../include/utils.h"
#include "../../include/core.h"
#include "../../include/applications.h"
#include "../core/c_array.h"
#include "../core/backward_search.h"
#include "mapper.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct mem_candidate {
	substring extension;
	char first;
	char last;
} mem_candidate;

static wavelet_tree* mem_bwt1;
static wavelet_tree* mem_bwt2;
static wavelet_tree* mem_rbwt1;
static wavelet_tree* mem_rbwt2;
static triplet* mems;
static int mem_triplets_index;

void mem_initialize_bwts(wavelet_tree* bwt1, wavelet_tree* bwt2,
		wavelet_tree* rbwt1, wavelet_tree* rbwt2) {
	mem_bwt1 = bwt1;
	mem_bwt2 = bwt2;
	mem_rbwt1 = rbwt1;
	mem_rbwt2 = rbwt2;
	mems = calloc(1000000, sizeof(triplet));
	mem_triplets_index = 0;
}

int list_mem_candidates(substring* node, wavelet_tree* bwt, wavelet_tree* rbwt,
		mem_candidate* mem_candidates) {
	interval* normal_left = malloc(sizeof(interval));
	interval* reverse_left = malloc(sizeof(interval));
	interval* normal_right = malloc(sizeof(interval));
	interval* reverse_right = malloc(sizeof(interval));
//	int i;

	alphabet_data* alpha_data_left = create_alphabet_interval(&node->normal,
			bwt, 0);
	alphabet_data* alpha_data_right;
	int* c_array_left = create_c_array(bwt, &node->normal, 0, 0, 0);
	int* c_array_right;
	int alphabet_length = alpha_data_left->length;
	int index = 0;
	for (int i = 0; i < alphabet_length; i++) {
		normal_left = backward_search_interval(bwt, &node->normal,
				alpha_data_left->alphabet[i], 0);
		reverse_left = update_reverse_interval(&node->reverse, normal_left,
				alpha_data_left->alphabet, alphabet_length, c_array_left,
				alpha_data_left->alphabet[i], 0);
		alpha_data_right = create_alphabet_interval(reverse_left, rbwt, 0);
		c_array_right = create_c_array(rbwt, reverse_left, 0, 0, 0);
		for (int j = 0; j < alpha_data_right->length; j++) {
			reverse_right = backward_search_interval(rbwt, reverse_left,
					alpha_data_right->alphabet[j], 0);
			normal_right = update_reverse_interval(normal_left, reverse_right,
					alpha_data_right->alphabet, alpha_data_right->length,
					c_array_right, alpha_data_right->alphabet[j], 0);
			substring* new_substring = create_substring(normal_right,
					reverse_right, node->length, 0);
			mem_candidates[index].extension = *new_substring;
			mem_candidates[index].first = alpha_data_left->alphabet[i];
			mem_candidates[index].last = alpha_data_right->alphabet[j];
			index++;
		}
	}
	return index;
}

void search_mems(substring* node1, substring* node2) {
	mem_candidate* mem_candidates1 = calloc(
			(node1->normal.j - node1->normal.i + 1), sizeof(mem_candidate));
	mem_candidate* mem_candidates2 = calloc(
			(node2->normal.j - node2->normal.i + 1), sizeof(mem_candidate));
	int index1 = list_mem_candidates(node1, mem_bwt1, mem_rbwt1,
			mem_candidates1);
	int index2 = list_mem_candidates(node2, mem_bwt2, mem_rbwt2,
			mem_candidates2);
	for (int i = 0; i < index1; i++) {
		for (int j = 0; j < index2; j++) {
			if ((mem_candidates1[i].first != mem_candidates2[j].first || mem_candidates1[i].first == '$')
					&& (mem_candidates1[i].last != mem_candidates2[j].last || mem_candidates1[i].last == '$')) {
				for (int k = mem_candidates1[i].extension.normal.i;
						k <= mem_candidates1[i].extension.normal.j; k++) {
					for (int l = mem_candidates2[j].extension.normal.i;
							l <= mem_candidates2[j].extension.normal.j; l++) {
						triplet trip = *((triplet*) malloc(sizeof(triplet)));
						trip.pos1 = k;
						trip.pos2 = l;
						trip.length = node1->length;
						mems[mem_triplets_index] = trip;
						mem_triplets_index++;
					}
				}
			}
		}

//		printf("First char: %c\n", mem_candidates1[i].first);
//		printf("Last char: %c\n", mem_candidates1[i].last);
//		print_node(&mem_candidates1[i].extension);
	}
}

triplet* get_mems() {
	return mems;
}

void print_mems(char* string) {
	int i;
	for (i = 0; i < mem_triplets_index; i++) {
		triplet trip = mems[i];
		printf(
				"Index in the BWT first string: %d\nIndex in the BWT second string: %d\nLength: %d \n",
				trip.pos1, trip.pos2, trip.length);
	}
	map_triplets_to_string(mems, mem_bwt1, mem_bwt2, mem_triplets_index, mem_make_bit_vectors(mems));

	for(int i = 0; i < mem_triplets_index; i++){
		mems[i].pos1 = mems[i].pos1 + 1;
		mems[i].pos2 = mems[i].pos2 + 1;
	}


	for (i = 0; i < mem_triplets_index; i++) {
		triplet trip = mems[i];
		printf(
				"Index in the first string: %d\nIndex in the second string: %d\nLength: %d \n",
				trip.pos1, trip.pos2, trip.length);
		char* subs = substring_from_string(string, trip.pos1, trip.length);
		printf("The substring itself: %s \n", subs);
		printf("\n\n");
	}
}

int get_mems_amount() {
	return mem_triplets_index;
}

bit_vector** mem_make_bit_vectors(triplet* mems) {
	bit_vector** vectors = calloc(2,sizeof(bit_vector));
	bit_vector* bit_vector1 = malloc(sizeof(bit_vector));
	init_bit_vector(bit_vector1, mem_bwt1->get_num_bits(mem_bwt1));
	bit_vector* bit_vector2 = malloc(sizeof(bit_vector));
	init_bit_vector(bit_vector2, mem_bwt2->get_num_bits(mem_bwt2));
	int i;
	for (i = 0; i < mem_triplets_index; i++) {
		triplet trip = mems[i];
		bit_vector1->mark_bit(bit_vector1, trip.pos1);
		bit_vector2->mark_bit(bit_vector2, trip.pos2);
	}
	vectors[0] = bit_vector1;
	vectors[1] = bit_vector2;
	return vectors;
}
