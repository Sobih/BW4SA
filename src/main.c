/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/bwt_to_s.h"

#include "../include/iterate.h"
#include "iterate/print_node.h"

int main(void) {
	char* test = "lol";
	char* test2 = "aaoaalaaaoaaaoaa";
	double_iterate(test, test2, &print_double_node);
	return 0;
}
