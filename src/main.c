/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/bwt_to_s.h"
#include "../include/draw_tree.h"
#include "../include/iterate.h"
#include "iterate/print_node.h"

int main(void) {
	char* test = "abracadabra";
	draw_suffix_tree(test);
	return 0;
}
