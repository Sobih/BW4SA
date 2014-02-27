/*
 * maximal_repeats.h
 *
 *  Created on: 26.2.2014
 *      Author: lvapaaka
 */

#ifndef MAXIMAL_REPEATS_H_
#define MAXIMAL_REPEATS_H_

#include "iterate.h"

/**
 * Initializes the BWT for the file so that callback doesn't require passing it on.
 */
void max_repeats_initialize_bwt(char* bwt);

/**
 * The function given to callback. Dtermines if a node is a maximal repeat and adds it to a list.
 */
void search_maximal_repeats(substring* node);

/**
 * Returns the list of maximal repeat nodes.
 */
substring* get_nodes();

/**
 * Prints what substring the maximal repeat is and the indexes (in sorted order) it occurs at.
 */
void maximals_print_nodes(char* string);

#endif /* MAXIMAL_REPEATS_H_ */
