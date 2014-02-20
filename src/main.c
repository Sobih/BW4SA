/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/iterate.h"
#include "iterate/print_node.h"

int main(void) {
	char* test = "hattivatti";
	iterate(test, &print_node);
	printf("TIDDIDDII!\n");
	return 0;
}
