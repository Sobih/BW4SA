/*
 * mum.h
 *
 *  Created on: 26.2.2014
 *      Author: lvapaaka
 */

#ifndef MUM_H_
#define MUM_H_

#include "iterate.h"

typedef struct triplet_struct {
	unsigned int pos1;
	unsigned int pos2;
	unsigned int length;
} triplet;

void mum_initialize_bwts(char* bwt1,char* bwt2, char* rbwt1, char* rbwt2);

void search_mums(substring* node1, substring* node2);

triplet* get_mums();

void print_mums(char* string);

int get_triplets_index();

void mum_print_bit_vectors();

#endif /* MUM_H_ */
