/*
 * main.c
 *
 *  Created on: 16.1.2014
 *      Author: lvapaaka
 */

#include "s_to_bwt.h"

int main(void) {
	printf("HELLO, WORLD!\n");

	char *c = calloc(100,sizeof(char));

	c = "gttccacccaaccaaaccaaacccccccccccccccc";

	printf(s_to_BWT(c));
	printf("\n");

	return 0;
}
