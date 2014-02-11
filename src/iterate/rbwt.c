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

/** 
 * @brief	reverses a string	
 * @param 	string 	a string to be reversed
 * @return 	the reversed string
 * @see 	rbwt.h
 * @author 	Paula Lehtola
 * @bug 	No known bugs.
 */

char *reverse_string(char *string) {
	const int len = strlen(string);
	int i;
	char *rev = malloc(len+1);
	for (i = 0; i < len; i++) {
		rev[i] = string[len-i-1];
	}
	rev[len] = '\0';

	return rev;
}

/** 
 * @brief	bwt for a reversed string
 * @param 	string to be reversed and BWT'ed
 * @return 	bwt of the reversed string
 * @see 	rbwt.h
 * @author 	Paula Lehtola
 * @bug 	No known bugs.
 */

char *reverse_bwt(char *string) {
	char *rev = reverse_string(string);
	char *bwt = s_to_BWT(rev);
	free(rev);
	return bwt;
}



