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
