
/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/rbwt.h"
#include "bwt/s_to_bwt.h"

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

	//char *s = reverse_string("MISSISSIPPI");
	char *s = reverse_bwt("ABRACADABRA$");
	print(s);

	return 0;


}
