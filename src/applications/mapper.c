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

max_repeat_with_indexes* map_maximal_repeats_to_string(max_repeat_node* nodes,
		wavelet_tree* bwt, int nodes_length, bit_vector* bit_vec) {
	long n = bwt->get_num_bits(bwt);
	int k, l;
	int marked_bits = marked_bits_on_bit_vector(bit_vec,
			bwt->get_num_bits(bwt));

	max_repeat_with_indexes* max_indexes = calloc(nodes_length,
			sizeof(max_repeat_with_indexes));

	mapped_pair* pairs = calloc(marked_bits, sizeof(mapped_pair));
	interval* inter = malloc(sizeof(interval));
	interval* target = malloc(sizeof(interval));
	inter->i = 0;
	inter->j = 0;

	int i = 0;
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

	compare_quick_sort(pairs, i, sizeof(mapped_pair),
			&compare_mapped_pairs_by_bwt_pos);
	compare_quick_sort(nodes, nodes_length, sizeof(max_repeat_node),
			&compare_max_repeat_nodes);

	int last_node_start = 0;
	for (int j = 0; j < nodes_length; j++) {
		i = last_node_start;
		max_indexes[j].length = nodes[j].length;
		max_indexes[j].interval_size = (nodes[j].normal.j - nodes[j].normal.i)
				+ 1;
		unsigned int* list = calloc(max_indexes[j].interval_size,
				sizeof(unsigned int));

		l = 0;
		while (l < max_indexes[j].interval_size) {
			if (pairs[i].bwt_pos == nodes[j].normal.i + l) {
				// saving the starting position of a sub-interval for optimizing going through nested maximal repeats
				if (l == 0) {
					last_node_start = i;
				}
				list[l] = pairs[i].orig_pos;
				l++;
			}
			i++;
		}
		quick_sort(list, max_indexes[j].interval_size, sizeof(unsigned int));
		max_indexes[j].indexes = list;
	}
	free(inter);
	free(target);
	/*free(pairs);*/
	return max_indexes;
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
mapped_pair* update_position_in_triplets(wavelet_tree* bwt, int nodes_length,
		bit_vector* bit_vec, int marked_bits) {
	int i = 0;
	long n = bwt->get_num_bits(bwt);

	mapped_pair* pairs = calloc(marked_bits, sizeof(mapped_pair));
	interval* inter = malloc(sizeof(interval));
	interval* target = malloc(sizeof(interval));
	inter->i = 0;
	inter->j = 0;

	int k;
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

int marked_bits_on_bit_vector(bit_vector* vec, int vector_length) {
	int marked_bits = 0;
	for (int i = 0; i < vector_length; i++) {
		if (vec->is_bit_marked(vec, i))
			marked_bits++;
	}
	return marked_bits;
}

void map_mum_triplets_to_string(triplet* nodes, wavelet_tree* bwt1,
		wavelet_tree* bwt2, int nodes_length, bit_vector** vecs) {

	print_bit_vector(vecs[0]);
	print_bit_vector(vecs[1]);

	int bits = marked_bits_on_bit_vector(vecs[0], bwt1->get_num_bits(bwt1));

	mapped_pair* pairs1 = update_position_in_triplets(bwt1, nodes_length,
			vecs[0], bits);
	compare_quick_sort(pairs1, bits, sizeof(mapped_pair),
			&compare_mapped_pairs_by_bwt_pos);
	compare_quick_sort(nodes, nodes_length, sizeof(triplet),
			&compare_triplets_pos1);

	for (int j = 0; j < nodes_length; j++) {
		nodes[j].pos1 = pairs1[j].orig_pos;
	}

	bits = marked_bits_on_bit_vector(vecs[1], bwt2->get_num_bits(bwt2));

	mapped_pair* pairs2 = update_position_in_triplets(bwt2, nodes_length,
			vecs[1], bits);
	compare_quick_sort(pairs2, bits, sizeof(mapped_pair),
			&compare_mapped_pairs_by_bwt_pos);
	compare_quick_sort(nodes, nodes_length, sizeof(triplet),
			&compare_triplets_pos2);
	for (int j = 0; j < nodes_length; j++) {
		nodes[j].pos2 = pairs2[j].orig_pos;
	}
	free(vecs);
	free(pairs1);
	free(pairs2);
}

void map_mem_triplets_to_string(triplet* nodes, wavelet_tree* bwt1,
		wavelet_tree* bwt2, int nodes_length, bit_vector** vecs) {

	print_bit_vector(vecs[0]);
	print_bit_vector(vecs[1]);

	int bits = marked_bits_on_bit_vector(vecs[0], bwt1->get_num_bits(bwt1));

	mapped_pair* pairs1 = update_position_in_triplets(bwt1, nodes_length,
			vecs[0], bits);
	compare_quick_sort(pairs1, bits, sizeof(mapped_pair),
			&compare_mapped_pairs_by_bwt_pos);
	compare_quick_sort(nodes, nodes_length, sizeof(triplet),
			&compare_triplets_pos1);

	int k = 0;
	for (int j = 0; j < nodes_length; j++) {

		int position = nodes[j].pos1;

		nodes[j].pos1 = pairs1[k].orig_pos;
		if (j == nodes_length - 1) {
			break;
		}
		if (position != nodes[j + 1].pos1) {
			k++;
		}
	}

	bits = marked_bits_on_bit_vector(vecs[1], bwt2->get_num_bits(bwt2));

	mapped_pair* pairs2 = update_position_in_triplets(bwt2, nodes_length,
			vecs[1], bits);
	compare_quick_sort(pairs2, bits, sizeof(mapped_pair),
			&compare_mapped_pairs_by_bwt_pos);
	compare_quick_sort(nodes, nodes_length, sizeof(triplet),
			&compare_triplets_pos2);

	k = 0;
	for (int j = 0; j < nodes_length; j++) {

		int position = nodes[j].pos2;

		nodes[j].pos2 = pairs2[k].orig_pos;
		if (j == nodes_length - 1) {
			break;
		}
		if (position != nodes[j + 1].pos2) {
			k++;
		}
	}

	int str_length1 = bwt1->get_num_bits(bwt1);
	int str_length2 = bwt2->get_num_bits(bwt2);

	for (int i = 0; i < nodes_length; i++) {
		nodes[i].pos1 = nodes[i].pos1 + 1;
		if (nodes[i].pos1 == str_length1) {
			nodes[i].pos1 = 0;
		}
		nodes[i].pos2 = nodes[i].pos2 + 1;
		if (nodes[i].pos2 == str_length2) {
			nodes[i].pos2 = 0;
		}
	}

	free(vecs);
	free(pairs1);
	free(pairs2);
}

