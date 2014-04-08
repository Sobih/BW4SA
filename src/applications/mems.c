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
#include <stdlib.h>
#include <stdio.h>

typedef struct mem_candidate {
	substring left_extension;
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
	mems = calloc(100, sizeof(triplet));
	mem_triplets_index = 0;
}

void list_mem_candidates(substring* node, wavelet_tree* bwt, wavelet_tree* rbwt,
		mem_candidate* mem_candidates) {
	interval* normal = malloc(sizeof(interval));
	interval* reverse = malloc(sizeof(interval));
//	int i;

	alphabet_data* alpha_data = create_alphabet_interval(&node->normal, bwt, 0);
	int* c_array = create_c_array(bwt, &node->normal, 0, 0, 0);
	int alphabet_length = alpha_data->length;
//	int index;
	for (int i = 0, index = 0; i < alphabet_length; i++, index++) {
		normal = backward_search_interval(bwt, node->normal, alpha_data->alphabet[i], 0);
		reverse = update_reverse_interval(&node->reverse, normal,
				alpha_data->alphabet, alphabet_length, c_array,
				alpha_data->alphabet[i], 0);

		substring* new_substring = create_substring(normal, reverse,
				node->length, 0);
		mem_candidates[index].left_extension = *new_substring;
		mem_candidates[index].first = alpha_data->alphabet[i];
		mem_candidates[index].last = 'c';
	}
}

void search_mems(substring* node1, substring* node2) {
	printf("\n\nInput:\n");
	print_node(node1);
	print_node(node2);
	mem_candidate* mem_candidates1 = calloc(
			(node1->normal.j - node1->normal.i + 1), sizeof(mem_candidate));
	mem_candidate* mem_candidates2 = calloc(
			(node2->normal.j - node2->normal.i + 1), sizeof(mem_candidate));
	list_mem_candidates(node1, mem_bwt1, mem_rbwt1, mem_candidates1);
	list_mem_candidates(node2, mem_bwt2, mem_rbwt2, mem_candidates2);
	printf("Output:\n");
	for (int i = 0; i <= node1->normal.j - node1->normal.i + 1; i++) {
		printf("%c", mem_candidates1[i].first);
		printf("%c", mem_candidates1[i].first);
		print_node(&mem_candidates1[i].left_extension);
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
	map_mum_triplets_to_string(mems, mem_bwt1, mem_bwt2, mem_triplets_index);
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
