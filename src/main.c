/*
 * main.c
 *
 *      Author: lvapaaka
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/bwt_to_s.h"

#include "../include/iterate.h"
#include "../include/mum.h"

int main(void) {
	char* test = "abracadabra";
	char* test2 = "abracadabra";
	double_iterate(test, test2, &search_mums);
	print_mums();
	return 0;
}
