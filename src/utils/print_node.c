/**
 * @file	print_node.c
 * @brief	Implementation of the printing of substrings.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "print_node.h"
#include "structs.h"
#include "../core/iterate.h"
#include <stdio.h>

void print_node(iterator_state* state, void* results){
	substring* node = state->current;
	printf("Interval in normal BWT: [%d,%d]\n",node->normal.i,node->normal.j);
	printf("Interval in BWT of the reverse of the string: [%d,%d]\n",node->reverse.i,node->reverse.j);
	printf("Length of substring (same as depth): %d\n:",node->length);
}
