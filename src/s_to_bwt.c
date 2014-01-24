/*
 * s_to_bwt.c
 *
 *  Created on: 24.1.2014
 *      Author: lvapaaka
 */

#include "dbwt.h"
#include <stdio.h>
#include <string.h>

/**
 * Parses the result file into a string.
 *
 * Currently limited to 100 characters.
 *
 * @return first line of output.bw as a string
 */
char* get_BWT_from_result_file_as_string(){
	FILE* f;
	char* c = calloc(100,sizeof(char));
	if (!(f = fopen("output.bw", "r")))
		return "";
	fgets(c,100,f);
	fclose(f);

	return c;
}

/**
 * Converts a string into a file and inputs that to function bwt in the DBWT library.
 *
 * @param input char array to be used in bwt
 */
void generate_result_file_from_string(char *input) {
	FILE* f;
	if (!(f = fopen("input.txt", "w+")))
		return;
	fputs(input, f);
	fclose(f);

	bwt("input.txt");
}

/**
 * Performs Burrows-Wheeler transform on the given string.
 *
 * @param string the string on which the Burrows-Wheeler transform is applied to.
 * @return the BWT of the string
 */
char* s_to_BWT(char *string) {
	generate_result_file_from_string(string);
	string = get_BWT_from_result_file_as_string();
	return string;
}




