/**
 * @file	print_node.c
 * @brief	Implementation of the printing of substrings.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "print_node.h"
#include "structs.h"
#include <stdio.h>

void print_node(substring* node){
	printf("Interval in normal BWT: [%d,%d]\n",node->normal.i,node->normal.j);
	printf("Interval in BWT of the reverse of the string: [%d,%d]\n",node->reverse.i,node->reverse.j);
	printf("Length of substring (same as depth): %d\n:",node->length);
}

void print_double_node(substring* node1, substring* node2){
	printf("Node 1:\n");
	print_node(node1);
	printf("Node 2:\n");
	print_node(node2);
}
