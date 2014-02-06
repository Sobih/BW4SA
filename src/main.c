
/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "iterate/rbwt.c"

void print(char *string)
{
	int i;
	int len = strlen(string);
	for (i = 0; i < len; i++) {
		printf("%c", string[i]);
	}
	printf("\n");


}


int main(void) {

	char *s = reverse_string("kissa");
	print(s);

	return 0;


}
