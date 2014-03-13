/*
 * mapper.c
 *
 *  Created on: 13.3.2014
 *      Author: lvapaaka
 */

#include "../../include/maximal_repeats.h"
#include <stdlib.h>
#include <string.h>

void map_maximal_repeats_to_string(max_repeat_node** nodes, char* bwt) {

	int i;
	int count = get_max_repeats_nodes_index();

	for (i = 0; i < count; i++) {
		long n = strlen(bwt) - 1;
		int k;
		Interval* interval = malloc(sizeof(Interval));
		interval->i = 0;
		interval->j = 0;

		for (k = 1; k <= n; k++) {
			if (nodes[i]->normal->i == interval->i) {
				nodes[i]->normal->i = (n - k) +1;
				break;
			}
			interval = backward_search_interval(bwt, interval, bwt[interval->i]);
		}
		free(interval);

	}

}

