/*
 * mapper.h
 *
 *  Created on: 13.3.2014
 *      Author: lvapaaka
 */

#ifndef MAPPER_H_
#define MAPPER_H_

#include "maximal_repeats.h"
#include "mum.h"

/**
 * @brief	Maps the BWT indexes to indexes in the original string in all found maximal repeats.
 *
 * Updates the normal.i value to index in the original string.
 *
 * @bug		No known bugs.
 */
void map_maximal_repeats_to_string(max_repeat_node* nodes, char* bwt);

/**
 * @brief	Maps the BWT indexes to indexes in the original string in all found MUMs.
 *
 * Updates the position values in both strings to indexes in the original string.
 *
 * @bug		No known bugs.
 */
void map_mum_triplets_to_string(triplet* nodes, char* bwt1, char* bwt2, int count);

#endif /* MAPPER_H_ */
