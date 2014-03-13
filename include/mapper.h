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

void map_maximal_repeats_to_string(max_repeat_node** nodes, char* bwt);

void map_mum_triplets_to_string(triplet* nodes, char* bwt1, char* bwt2, int count);

#endif /* MAPPER_H_ */
