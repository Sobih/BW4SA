/**
 * @file	s_to_bwt.c
 * @brief	Implementation of the function for creating a BWT from a c-string.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "../../libs/DBWT/dbwt.h"
#include "../../include/wavelet_tree.h"
#include <stdlib.h>
#include <string.h>
#include "s_to_bwt.h"

wavelet_tree* s_to_BWT (uchar* string) {
	unsigned int last;
	long n = strlen(string);
	uchar* d = malloc((n + 1) * sizeof(uchar));
	d = dbwt_bwt(string, n, &last, 0);
	d = realloc(d, (n + 2) * sizeof(uchar));
	d[last] = '$';
	d[n + 1] = 0;

	return create_wavelet_tree(d);
}

