/**
 * @file	bit_array.c
 * @brief	Implementation of the bit array.
 * @see		bit_array.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "../../include/bit_array.h"
#include "../../include/utils.h"

/**
 * @brief	Constructs the mapping of the alphabet.
 * @param	alphabet	The alphabet used by the string, ordered lexicographically.
 * @param	length		Length of the alphabet-array.
 * @return				A mapped alphabet.
 * @see		bit_array.h#map_alphabet
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char_mapping* construct_mapping(const char* alphabet, unsigned int length) {
	char_mapping* mapping;
	unsigned int bit_value = 0;

	if ((mapping = calloc(length + 1, sizeof(char_mapping))) == 0)
		//allocation failed, return NULL
		return 0;

	//add starting value that defines length of array
	mapping[0].bit_value = length;
	mapping[0].character = 0;

	//create mapping
	for (int i = 0; i < length; ++i) {
		mapping[i + 1].character = alphabet[i];
		mapping[i + 1].bit_value = bit_value;

		bit_value++;
	}

	return mapping;
}

/**
 * @brief	Determines the alphabet used by the string.
 * @param	string	The string from which the alphabet should be deduced.
 * @return			The alphabet used by the string.
 * @see		bit_array.h#map_alphabet
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char* determine_alphabet(const char* string) {
	int chars_left = 10, alphabet_size = 0;
	unsigned int size = strlen(string);
	char* alphabet;

	if ((alphabet = calloc(chars_left, sizeof(char))) == 0)
		return 0;

	int exists;

	for (int i = 0; i < size; ++i) {
		exists = 0;

		for (int j = 0; j < alphabet_size; ++j) {
			//break if character already in alphabet
			if (strncmp(string + i, alphabet + j, 1) == 0) {
				exists = 1;
				break;
			}
		}

		//character doesn't exist in alphabet, insert it
		if (!exists) {

			if (chars_left == 0) {
				//expand alphabet array
				chars_left = 10;

				if ((alphabet = realloc(alphabet, alphabet_size + chars_left)) == 0)
					//realloc failed, return NULL
					return 0;
			}

			//add to alphabet
			chars_left--;
			alphabet[alphabet_size] = *(string + i);
			alphabet_size++;
		}
	}

	//add null-marker
	if (chars_left == 0)
		//expand alphabet array
		if ((alphabet = realloc(alphabet, alphabet_size + 1)) == 0)
			//realloc failed, return NULL
			return 0;

	//add to alphabet
	alphabet[alphabet_size] = 0;

	return alphabet;
}

char_mapping* map_alphabet(const char* string) {
	//string not initialized, return NULL
	if (string == 0)
		return 0;

	char* alphabet;

	if ((alphabet = determine_alphabet(string)) == 0)
		//return null if alphabet couldn't be determined
		return 0;

	//sort constructed alphabet into lexicographic order
	unsigned int length = strlen(alphabet);
	quick_sort(alphabet, length, sizeof(char));

	char_mapping* mapping = construct_mapping(alphabet, length);

	//delete alphabet
	free(alphabet);

	return mapping;
}

char_mapping* find_by_char(char_mapping* start, char c) {
	for (int i = 1; i < start->bit_value; ++i)
		if (start[i].character == c)
			return (start + i);

	//none found
	return 0;
}

char_mapping* find_by_bit_value(char_mapping* start, unsigned int bit_value) {
	for (int i = 1; i < start->bit_value; ++i)
		if (start[i].bit_value == bit_value)
			return (start + i);

	//none found
	return 0;
}

void map_to_int(unsigned int bit_value, int* target, int place, unsigned int bits_per_char) {
	unsigned int clear_mask = ~ ((bits_per_char * bits_per_char - 1) << place);
	unsigned int mark_mask = bit_value << place;

	//clear bits at correct location and mark new bits
	*target &= clear_mask;
	*target |= mark_mask;
}

unsigned int* map_string_to_int_array(const char* string, char_mapping* alphabet) {
	int bits_per_char = ceil(log10(alphabet[0].bit_value) / log10(2));
	int chars_in_int = floor(bits_per_char / sizeof(int));
	int string_index = 0, string_length = strlen(string);
	int array_size = chars_in_int * string_length + 1;

	//too many bits needed to map char
	if (bits_per_char > 32)
		return 0;

	unsigned int* char_array = calloc(array_size, sizeof(int));

	for (int i = 0; string_index < string_length; ++i) {
		char_array[i] = 0;

		//map as many characters as possible into current array location
		for (int j = 0; j < chars_in_int && string_index < string_length; ++j) {
			//map current char into current array location
			map_to_int(find_by_char(alphabet, string[string_index])->bit_value, (char_array + i),
					j, bits_per_char);

			string_index++;
		}
	}

	//add NULL to the end to indicate end of array
	char_array[array_size - 1] = NULL;

	return char_array;
}

char* map_int_array_to_string(const unsigned int* char_array, char_mapping* alphabet) {
	int bits_per_char = ceil(log10(alphabet[0].bit_value) / log10(2));
	int chars_in_int = floor(bits_per_char / sizeof(int)), array_size = 0;

	//count length of array
	while (1) {
		if (char_array[array_size] == NULL)
			break;

		array_size++;
	}

	int string_length = chars_in_int * array_size + 1;
	char* string = calloc(string_length, sizeof(char));

	unsigned int current_substr, current_char;
	unsigned int mask = bits_per_char * bits_per_char - 1;
	int string_index = 0;

	for (int i = 0; i < array_size; ++i) {
		current_substr = char_array[i];

		//decode all chars from current int
		for (int j = 0; j < chars_in_int; ++j) {
			current_char = (current_substr & mask) >> (bits_per_char * j);
			string[string_index] = find_by_bit_value(alphabet, current_char)->character;

			//update mask to take next int
			mask = mask << bits_per_char;
			string_index++;
		}
	}

	//append NULL to end of string
	string[string_length - 1] = 0;

	return string;
}
