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
	if (!(f = fopen("test.txt", "w+"))) {
		return 1;
	}
	fputs("abracadabra",f);

	fclose(f);

	bwt("test.txt");

	return 0;
}
