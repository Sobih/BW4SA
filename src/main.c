/*
 * main.c
 *
 *  Created on: 16.1.2014
 *      Author: lvapaaka
 */

#include "dbwt.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	printf("HELLO, WORLD!");
	FILE *f;
	char c[50];
	if (!(f = fopen("test.txt", "a"))) {
		return 1;
	}
	fgets(c, 50, "abracadabra");
	fputs(c, f);
	fclose(f);

	bwt("test.txt");

	return 0;
}
