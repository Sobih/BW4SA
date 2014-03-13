/*
 * mapper.c
 *
 *  Created on: 13.3.2014
 *      Author: lvapaaka
 */

#include "../../include/maximal_repeats.h"
#include "../../include/mum.h"
#include <stdlib.h>
#include <string.h>

void map_maximal_repeats_to_string(max_repeat_node** nodes, char* bwt) {

	int i;
	int count = get_max_repeats_nodes_index();
	long n = strlen(bwt) - 1;
	int k;
	Interval* interval = malloc(sizeof(Interval));
	interval->i = 0;
	interval->j = 0;

	for (i = 0; i < count; i++) {
		for (k = 1; k <= n; k++) {
			if (nodes[i]->normal->i == interval->i) {
				nodes[i]->normal->i = (n - k) + 1;
				break;
			}
			interval = backward_search_interval(bwt, interval,
					bwt[interval->i]);
		}
		free(interval);

	}

}

void map_mum_triplets_to_string(triplet* nodes, char* bwt1, char* bwt2, int count) {
	int i, k, j;
	long n = strlen(bwt1) - 1;
	long n2 = strlen(bwt2) - 1;
	Interval* interval = malloc(sizeof(Interval));
	interval->i = 0;
	interval->j = 0;
	Interval* interval2 = malloc(sizeof(Interval));
	interval2->i = 0;
	interval2->j = 0;
	for (i = 0; i < count; i++) {
		for (k = 1; k <= n; k++) {
			if (nodes[i].pos1 == interval->i) {
				nodes[i].pos1 = (n - k) + 1;
				break;
			}
			interval = backward_search_interval(bwt1, interval,
					bwt1[interval->i]);
		}
		for (j = 1; j <= n2; j++) {
			if (nodes[i].pos2 == interval2->i) {
				nodes[i].pos2 = (n2 - j) + 1;
				break;
			}
			interval2 = backward_search_interval(bwt2, interval2,
					bwt2[interval2->i]);
		}
	}
}

