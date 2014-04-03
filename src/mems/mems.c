/*
 * mems.c
 *
 *  Created on: 3.4.2014
 *      Author: lvapaaka
 */

#include "../../include/structs.h"
#include "../../include/wavelet_tree.h"
#include "../../include/mapper.h"
#include "../../include/utils.h"
#include <stdlib.h>
#include <stdio.h>


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

void search_mems(substring* node1, substring* node2) {
	int index1, index2;
	for (index1 = node1->normal.i; index1 <= node1->normal.j; index1++) {
		for (index2 = node2->normal.i; index2 <= node2->normal.j; index2++) {
			if (mem_bwt1->char_at(mem_bwt1, index1) != mem_bwt2->char_at(mem_bwt2, index2)) {
				if (mem_rbwt1->char_at(mem_rbwt1, index1) != mem_rbwt2->char_at(mem_rbwt2, index2)) {
					triplet trip = *((triplet*) malloc(sizeof(triplet)));
					trip.pos1 = index1;
					trip.pos2 = index2;
					trip.length = node1->length;
					mems[mem_triplets_index] = trip;
					mem_triplets_index++;
				}
			}
		}
	}
}

triplet* get_mems(){
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

int get_mems_amount(){
	return mem_triplets_index;
}
