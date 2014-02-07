/*
 * s_to_bwt.c
 *
 *  Created on: 24.1.2014
 *      Author: lvapaaka
 */

#include "dbwt.h"
#include <stdlib.h>
#include <string.h>

uchar* s_to_BWT(uchar *string) {
	unsigned int * _last;
	unsigned int last;
	long n = strlen(string);
	uchar *d = calloc(n + 2, sizeof(uchar));
	d = dbwt_bwt(string, n, &last, 0);
	d[last] = '$';
	d[n + 1] = 0;
	//(*_last) = last;
	return d;
}

