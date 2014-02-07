/*
 * print_node.c
 *
 *  Created on: 7.2.2014
 *      Author: lvapaaka
 */


#include "../../include/iterate.h"
#include <stdio.h>

void print_node(substring* node){
	printf("Interval in normal BWT: [%d,%d]\n",node->normal->i,node->normal->j);
	printf("Interval in BWT of the reverse of the string: [%d,%d]\n",node->reverse->i,node->reverse->j);
	printf("Length of substring (same as depth): %d\n:",node->length);
}
