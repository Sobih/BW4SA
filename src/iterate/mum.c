/*
 * mum.c
 *
 *  Created on: 26.2.2014
 *      Author: lvapaaka
 */

#include "../../include/mum.h"
#include "../../include/iterate.h"
#include "../../include/mapper.h"
#include <stdio.h>
#include <stdlib.h>

char* mum_bwt1;
char* mum_bwt2;
char* mum_rbwt1;
char* mum_rbwt2;
triplet* mums;
int triplets_index = 0;

void mum_initialize_bwts(char* bwt1, char* bwt2, char* rbwt1, char* rbwt2) {
	mum_bwt1 = bwt1;
	mum_bwt2 = bwt2;
	mum_rbwt1 = rbwt1;
	mum_rbwt2 = rbwt2;
	mums = calloc(100, sizeof(triplet));
}

void search_mums(substring* node1, substring* node2) {
	if (node1->normal->i == node1->normal->j) {
		if (node2->normal->i == node2->normal->j) {
			if (mum_bwt1[node1->normal->i] != mum_bwt2[node2->normal->i]) {
				if (mum_rbwt1[node1->reverse->i]
						!= mum_rbwt2[node2->reverse->i]) {
					triplet trip = *((triplet*) malloc(sizeof(triplet)));
					trip.pos1 = node1->normal->i;
					trip.pos2 = node2->normal->i;
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
