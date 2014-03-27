/*
 * mapper.c
 *
 *  Created on: 13.3.2014
 *      Author: lvapaaka
 */

#include "../../include/maximal_repeats.h"
#include "../../include/mum.h"
#include "../../include/structs.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"
#include <stdlib.h>
#include <string.h>

void map_maximal_repeats_to_string(max_repeat_node* nodes, wavelet_tree* bwt, int count) {
	int i;
	long n = bwt->num_nodes - 1;
	int k;
	interval* inter = malloc(sizeof(interval));
	inter->i = 0;
	inter->j = 0;
	for (i = 0; i < count; i++) {
		for (k = 1; k <= n; k++) {
			if (nodes[i].normal.i == inter->i) {
				nodes[i].normal.i = (n - k) + 1;
				break;
			}
			inter = backward_search_interval(bwt, inter,
					bwt->char_at(bwt,inter->i),inter);
		}
		free(inter);
	}
}

void update_position_in_triplets(triplet* nodes, wavelet_tree* bwt, int count,
		int position) {
	int i;
	long n = bwt->num_nodes - 1;
	int k;
	interval* inter = malloc(sizeof(interval));
	inter->i = 0;
	inter->j = 0;
	for (i = 0; i < count; i++) {
		for (k = 1; k <= n; k++) {
			if (position == 1) {
				if (nodes[i].pos1 == inter->i) {
					nodes[i].pos1 = (n - k) + 1;
					break;
				}
			}
			if (position == 2) {
				if (nodes[i].pos2 == inter->i) {
					nodes[i].pos2 = (n - k) + 1;
					break;
				}
			}
			inter = backward_search_interval(bwt, inter,
					bwt->char_at(bwt,inter->i),inter);
		}
		free(inter);

	}
}

void map_mum_triplets_to_string(triplet* nodes, wavelet_tree* bwt1, wavelet_tree* bwt2, int count) {
	update_position_in_triplets(nodes, bwt1, count, 1);
	update_position_in_triplets(nodes, bwt2, count, 2);
}

