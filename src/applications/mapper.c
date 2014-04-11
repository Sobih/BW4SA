/**
 * @file	mapper.c
 * @brief	Implementation of the mapping functions.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator), Paula Lehtola
 * @bug		No known bugs.
 */

#include "mapper.h"
#include "maximal_repeats.h"
#include "mum.h"
#include "triplet_sorter.h"
#include "../../include/utils.h"
#include "../core/backward_search.h"
#include <stdlib.h>
#include <string.h>

void map_maximal_repeats_to_string(max_repeat_node* nodes, wavelet_tree* bwt,
		int count, bit_vector* bit_vec) {
	int i = 0;	
	long n = bwt->get_num_bits(bwt);
	int k;
	mapped_pair* pairs = calloc(count, sizeof(mapped_pair));
	interval* inter = malloc(sizeof(interval));
	interval* target = malloc(sizeof(interval));
	inter->i = 0;
	inter->j = 0;
	
	for (k = 0; k < n; k++) {
		if (bit_vec->is_bit_marked(bit_vec, inter->i)) {
			//printf("marked bit! \n");
			
			pairs[i].bwt_pos = inter->i;
			pairs[i].orig_pos = (n - k) - 1;
			i++;
		}
		target = backward_search_interval(bwt, inter,
				bwt->char_at(bwt, inter->i), target);
		memcpy(inter, target, sizeof(interval));
	}

	compare_quick_sort(pairs, i, sizeof(mapped_pair), &compare_mapped_pairs_by_bwt_pos);
	compare_quick_sort(nodes, count, sizeof(max_repeat_node), &compare_max_repeat_nodes);
	
	for(int j = 0; j < count; j++){
		nodes[j].normal.i = pairs[j].orig_pos;
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
mapped_pair* update_position_in_triplets(wavelet_tree* bwt, int count,
		bit_vector* bit_vec) {
	int i = 0;	
	long n = bwt->get_num_bits(bwt);
	int k;
	mapped_pair* pairs = calloc(count, sizeof(mapped_pair));
	interval* inter = malloc(sizeof(interval));
	interval* target = malloc(sizeof(interval));
	inter->i = 0;
	inter->j = 0;
	
	for (k = 0; k < n; k++) {
		if (bit_vec->is_bit_marked(bit_vec, inter->i)) {
			
			pairs[i].bwt_pos = inter->i;
			pairs[i].orig_pos = (n - k) - 1;
			i++;
		}
		target = backward_search_interval(bwt, inter,
				bwt->char_at(bwt, inter->i), target);
		memcpy(inter, target, sizeof(interval));
	}
	
	return pairs;
}

void map_mum_triplets_to_string(triplet* nodes, wavelet_tree* bwt1,
		wavelet_tree* bwt2, int count) {
	bit_vector** vecs = mum_make_bit_vectors(nodes);
	mapped_pair* pairs1 = update_position_in_triplets(bwt1, count, vecs[0]);
	compare_quick_sort(pairs1, count, sizeof(mapped_pair), &compare_mapped_pairs_by_bwt_pos);
	compare_quick_sort(nodes, count, sizeof(triplet), &compare_triplets_pos1);
	
	for(int j = 0; j < count; j++){
		nodes[j].pos1 = pairs1[j].orig_pos;
	}
	
	
	mapped_pair* pairs2 = update_position_in_triplets(bwt2, count, vecs[1]);
	compare_quick_sort(pairs2, count, sizeof(mapped_pair), &compare_mapped_pairs_by_bwt_pos);
	compare_quick_sort(nodes, count, sizeof(triplet), &compare_triplets_pos2);
	
		for(int j = 0; j < count; j++){
		nodes[j].pos2 = pairs2[j].orig_pos;
	}
}

