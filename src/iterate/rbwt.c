/**
 * @file 	rbwt.c
 * @brief 	reverse bwt for naive implementation of right maximals
 * @see 	rbwt.h 
 * @author 	Paula Lehtola
 * @bug 	No known bugs.

 */

/*
- input: string
- käännetään merkkijono
- tehdään käännetylle merkkijonolle bwt
*/

#include <stdlib.h>
#include <string.h>
#include "../bwt/s_to_bwt.h"
#include "../../include/wavelet_tree.h"

/** 
 * @brief	reverses a string	
 * @param 	string 	a string to be reversed
 * @return 	the reversed string
 * @see 	rbwt.h
 * @author 	Paula Lehtola
 * @bug 	No known bugs.
 */
char* reverse_string(const char* string, char* target, unsigned int length) {
	for (int i = 0; i < length; i++)
		target[i] = string[length - i - 1];

	target[length] = '\0';

	return target;
}

/** 
 * @brief	bwt for a reversed string
 * @param 	string to be reversed and BWT'ed
 * @return 	bwt of the reversed string
 * @see 	rbwt.h
 * @author 	Paula Lehtola
 * @bug 	No known bugs.
 */
wavelet_tree* reverse_bwt(const char* string) {
	unsigned int length = strlen(string);
	uchar* rev = malloc(length * sizeof(uchar));
	rev = reverse_string(string, rev, length);
	wavelet_tree* bwt = s_to_BWT(rev);
	free(rev);
	return bwt;
}



