/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "s_to_bwt.h"

int main(void) {

	unsigned char *c = "vaakapallo";

	unsigned char *d = calloc(strlen(c) + 1, sizeof(unsigned char));
	d = s_to_BWT(c);

	printf("%s\n", d);

	return 0;
}
