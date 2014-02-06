/*
- input: string
- käännetään merkkijono
- tehdään käännetylle merkkijonolle bwt
*/

#include <string.h>

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

