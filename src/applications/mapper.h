/*
 * mapper.h
 *
 *  Created on: 13.3.2014
 *      Author: lvapaaka
 */

#ifndef MAPPER_H_
#define MAPPER_H_

struct max_repeat_node;
struct triplet;
struct wavelet_tree;

/**
 * @brief	Maps the BWT indexes to indexes in the original string in all found maximal repeats.
 *
 * Updates the normal.i value to index in the original string.
 *
 * @bug		No known bugs.
 */
void map_maximal_repeats_to_string(struct max_repeat_node* nodes, struct wavelet_tree* bwt, int count);

/**
 * @brief	Maps the BWT indexes to indexes in the original string in all found MUMs.
 *
 * Updates the position values in both strings to indexes in the original string.
 *
 * @bug		No known bugs.
 */
void map_mum_triplets_to_string(struct triplet* nodes, struct wavelet_tree* bwt1, struct wavelet_tree* bwt2, int count);

#endif /* MAPPER_H_ */
