/*
 * s_to_bwt.c
 *
 *  Created on: 24.1.2014
 *      Author: lvapaaka
 */

#include "dbwt.h"
#include <stdio.h>
#include <string.h>

uchar* s_to_BWT(uchar *string) {
	unsigned int * _primary_idx;
	unsigned int last;
	long n = strlen(string);
	uchar *d = calloc(n + 2, sizeof(uchar));
	d = dbwt_bwt(string, n, &last, 0);
	d[last] = '$';
	d[n + 1] = 0;
	//(*_primary_idx) = last;
	return d;
//	generate_result_file_from_string(string);
//	string = get_BWT_from_result_file_as_string();
//	return string;
}

