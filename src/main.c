/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/bwt_to_s.h"

#include "../include/iterate.h"
#include "../include/maximal_repeats.h"

int main(void) {
	char* test = "hattivatti";
	iterate(test, &search_maximal_repeats);
	maximals_print_nodes();
	return 0;
}
