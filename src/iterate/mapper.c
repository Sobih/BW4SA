/**
 * @file	mapper.c
 * @brief	Implementation of the mapping functions.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "../../include/maximal_repeats.h"
#include "../../include/mum.h"
#include "../../include/structs.h"
#include "../../include/backward_search.h"
#include "../../include/wavelet_tree.h"
#include <stdlib.h>
#include <string.h>

void map_maximal_repeats_to_string(max_repeat_node* nodes, wavelet_tree* bwt,
		int count) {
	int i;
	long n = bwt->get_num_bits(bwt);
	int k;
	interval* inter = malloc(sizeof(interval));
	interval* target = malloc(sizeof(interval));
	inter->i = 0;
	inter->j = 0;
	for (i = 0; i < count; i++) {
		for (k = 0; k < n; k++) {
			if (nodes[i].normal.i == inter->i) {
				nodes[i].normal.i = (n - k) - 1;
				break;
			}
			target = backward_search_interval(bwt, inter,
					bwt->char_at(bwt, inter->i), target);
			memcpy(inter, target, sizeof(interval));
		}
		inter->i = 0;
		inter->j = 0;
	}
	free(inter);
	free(target);
}

/**
 * @brief	A function for mapping the indices inside the BWT to indices inside
 * 			the original c-string.
 * @param	nodes		A list of triplet-nodes.
 * @param	bwt			The BWT of a string, represented as a wavelet tree.
 * @param	count		Length of the array.
 * @param	position	Determines which of the indices is to be updated.
 * 						Has to be either <code>1</code> or <code>2</code>.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void update_position_in_triplets(triplet* nodes, wavelet_tree* bwt, int count,
		int position) {
	int i;
	long n = bwt->get_num_bits(bwt);
	int k;
	interval* inter = malloc(sizeof(interval));
	interval* target = malloc(sizeof(interval));
	inter->i = 0;
	inter->j = 0;
	for (i = 0; i < count; i++) {
		for (k = 0; k < n; k++) {
			if (position == 1) {
				if (nodes[i].pos1 == inter->i) {
					nodes[i].pos1 = (n - k) - 1;
					break;
				}
			}
			if (position == 2) {
				if (nodes[i].pos2 == inter->i) {
					nodes[i].pos2 = (n - k) - 1;
					break;
				}
			}
			target = backward_search_interval(bwt, inter,
					bwt->char_at(bwt, inter->i), target);
			memcpy(inter, target, sizeof(interval));
		}
		inter->i = 0;
		inter->j = 0;
	}
	free(inter);
	free(target);
}

void map_mum_triplets_to_string(triplet* nodes, wavelet_tree* bwt1,
		wavelet_tree* bwt2, int count) {
	update_position_in_triplets(nodes, bwt1, count, 1);
	update_position_in_triplets(nodes, bwt2, count, 2);
}

