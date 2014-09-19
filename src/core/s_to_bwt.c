/**
 * @file	s_to_bwt.c
 * @brief	Implementation of the function for creating a BWT from a c-string.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "s_to_bwt.h"
#include "../utils/wavelet_tree.h"
#include "../../libs/DBWT/dbwt.h"
#include <stdlib.h>
#include <string.h>

wavelet_tree* s_to_bwt (uchar* string) {
	unsigned int last;
	long n = strlen(string);
	uchar* d = dbwt_bwt(string, n, &last, 0);
	d = realloc(d, (n + 2) * sizeof(uchar));
	d[last] = '$';
	d[n + 1] = 0;
//	printf("The bwt is: %s\n",d);
	return create_wavelet_tree(d);
}

