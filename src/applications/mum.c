/*
 * mum.c
 *
 *  Created on: 26.2.2014
 *      Author: lvapaaka
 */

#include "mum.h"
#include "../core/mapper.h"
#include "../../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static wavelet_tree* mum_bwt1;
static wavelet_tree* mum_bwt2;
static wavelet_tree* mum_rbwt1;
static wavelet_tree* mum_rbwt2;
static triplet* mums;
static int triplets_index;

void mum_initialize_bwts(wavelet_tree* bwt1, wavelet_tree* bwt2, wavelet_tree* rbwt1, wavelet_tree* rbwt2) {
	mum_bwt1 = bwt1;
	mum_bwt2 = bwt2;
	mum_rbwt1 = rbwt1;
	mum_rbwt2 = rbwt2;
	mums = calloc(100, sizeof(triplet));
	triplets_index = 0;
}

void search_mums(substring* node1, substring* node2) {
	if (node1->normal.i == node1->normal.j) {
		if (node2->normal.i == node2->normal.j) {
			if (mum_bwt1->char_at(mum_bwt1,node1->normal.i) != mum_bwt2->char_at(mum_bwt2,node2->normal.i)) {
				if (mum_rbwt1->char_at(mum_rbwt1,node1->reverse.i)
						!= mum_rbwt2->char_at(mum_rbwt2,node2->reverse.i)) {
					triplet trip = *((triplet*) malloc(sizeof(triplet)));
					trip.pos1 = node1->normal.i;
					trip.pos2 = node2->normal.i;
					trip.length = node1->length;
					mums[triplets_index] = trip;
					triplets_index++;
				}
			}
		}
	}
}

triplet* get_mums() {
	return mums;
}

int get_mums_amount() {
	return triplets_index;
}

void print_mums(char* string) {
	int i;
	for (i = 0; i < triplets_index; i++) {
		triplet trip = mums[i];
		printf(
				"Index in the BWT first string: %d\nIndex in the BWT second string: %d\nLength: %d \n",
				trip.pos1, trip.pos2, trip.length);
	}
	map_mum_triplets_to_string(mums, mum_bwt1, mum_bwt2, triplets_index);
	for (i = 0; i < triplets_index; i++) {
		triplet trip = mums[i];
		printf(
				"Index in the first string: %d\nIndex in the second string: %d\nLength: %d \n",
				trip.pos1, trip.pos2, trip.length);
		char* subs = substring_from_string(string, trip.pos1, trip.length);
		printf("The substring itself: %s \n", subs);
	}
}

bit_vector** mum_make_bit_vectors(triplet* mapped_mums) {
	bit_vector** vectors = calloc(sizeof(bit_vector),2);
	bit_vector* bit_vector1 = malloc(sizeof(bit_vector));
	init_bit_vector(bit_vector1, mum_bwt1->num_nodes);
	bit_vector* bit_vector2 = malloc(sizeof(bit_vector));
	init_bit_vector(bit_vector2, mum_bwt2->num_nodes);
	int i;
	for (i = 0; i < triplets_index; i++) {
		triplet trip = mums[i];
		bit_vector1->mark_bit(bit_vector1, trip.pos1);
		bit_vector2->mark_bit(bit_vector2, trip.pos2);
	}
	vectors[0] = bit_vector1;
	vectors[1] = bit_vector2;
	return vectors;
}

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

void mum_print_bit_vectors(char* string1, char* string2) {
	bit_vector** vectors = mum_make_bit_vectors(mums);

	print_bit_vector_with_string (string1,vectors[0]);
	print_bit_vector_with_string (string2,vectors[1]);
}
