/*
 * mems.c
 *
 *  Created on: 3.4.2014
 *      Author: lvapaaka
 */

#include "../../include/structs.h"

static wavelet_tree* mem_bwt1;
static wavelet_tree* mem_bwt2;
static wavelet_tree* mem_rbwt1;
static wavelet_tree* mem_rbwt2;
static triplet* mems;
static int mem_triplets_index;

void mum_initialize_bwts(wavelet_tree* bwt1, wavelet_tree* bwt2, wavelet_tree* rbwt1, wavelet_tree* rbwt2) {
	mem_bwt1 = bwt1;
	mem_bwt2 = bwt2;
	mem_rbwt1 = rbwt1;
	mem_rbwt2 = rbwt2;
	mems = calloc(100, sizeof(triplet));
	mem_triplets_index = 0;
}



void search_mems(substring* node1, substring* node2) {

}


