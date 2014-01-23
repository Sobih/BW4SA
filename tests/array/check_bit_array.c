/*
 * check_bit_array.c
 *
 *  Created on: 21.1.2014
 *      Author: Max Sandberg
 */

#include <check.h>
#include "../../include/bit_array.h"

START_TEST (test_alphabet_mapping) {
	char* string = "asufgvakjsvfakuyftkjbvqygkjavjggjfaysggaaysgfysuuuysgfsuaguygsaygfugaysfguasygfu";

	char_mapping* mapping = map_alphabet(string);
	unsigned int length = mapping->bit_value;

	for (int i = 0; i < length + 1; ++i)
		sprintf("%c\t%d\n", mapping[i].character, mapping[i].bit_value);
}
END_TEST

int main() {
	return 0;
}
