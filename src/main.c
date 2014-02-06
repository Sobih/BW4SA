
/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "dbwt.h"

int main(void) {
	uchar *c = calloc(100, sizeof(uchar));
	c = "abracadabraaaaaaaaa";
	long n = strlen(c);

	printf("%li\n",n);

	unsigned int *last = &c + 500;

	printf("%d\n", last);

	uchar *d = calloc(100,sizeof(uchar));

	d = dbwt_bwt(c,n,last,0);

	printf("%s\n%s\n", c,d);

	printf("%d\n", last);

	free(d);

	return 0;
}
