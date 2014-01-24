/*
 * s_to_bwt.c
 *
 *  Created on: 24.1.2014
 *      Author: lvapaaka
 */

#include "dbwt.h"
#include <stdio.h>
#include <string.h>

char* get_BWT_from_result_file_as_string(){
	FILE* f;
	char* c = calloc(100,sizeof(char));

	if (!(f = fopen("output.bw", "r"))) {
		return "";
	}

	fgets(c,100,f);

	fclose(f);

	return c;
}

void generate_result_file_from_string(char *input) {
	FILE* f;

	if (!(f = fopen("input.txt", "w+"))) {
		return;
	}
	fputs(input, f);

	fclose(f);

	bwt("input.txt");
}

char* s_to_BWT(char *string) {
	generate_result_file_from_string(string);

	char *result = get_BWT_from_result_file_as_string();

	return result;
}




