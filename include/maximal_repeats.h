/*
 * maximal_repeats.h
 *
 *  Created on: 26.2.2014
 *      Author: lvapaaka
 */

#ifndef MAXIMAL_REPEATS_H_
#define MAXIMAL_REPEATS_H_

#include "iterate.h"

void max_repeats_initialize_bwt(char* bwt);

void search_maximal_repeats(substring* node);

substring* get_nodes();

void maximals_print_nodes(char* string);

#endif /* MAXIMAL_REPEATS_H_ */
