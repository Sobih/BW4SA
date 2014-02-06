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

#define		END		UINT_MAX

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
	unsigned int bit_value = 1;

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

/**
 * @brief	Finds an entry in a mapped alphabet using a char.
 * @param	start		The beginning of the alphabet.
 * @param	c			The letter which is to be found in the
 * 						alphabet.
 * @return	Returns the index of the character in the alphabet or
 * 			-1 if it can't be found.
 * @see		#find_by_bit_value
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int find_by_char(const char_mapping* start, char c) {
	for (int i = 1; i <= start->bit_value; ++i)
		if (start[i].character == c)
			return i;

	//none found
	return -1;
}

/**
 * @brief	Finds an entry in a mapped alphabet using a bit value.
 * @param	start		The beginning of the alphabet.
 * @param	bit_value	The mapped bit value for which an entry should
 * 						be found.
 * @return	Returns the index of the mapped bit value in the alphabet
 * 			or -1 if it can't be found.
 * @see		#find_by_char
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int find_by_bit_value(const char_mapping* start, unsigned int bit_value) {
	for (int i = 1; i <= start->bit_value; ++i)
		if (start[i].bit_value == bit_value)
			return i;

	//none found
	return -1;
}

/**
 * @brief	Maps a character to the specified position inside an
 * 			unsigned 32-bit integer.
 * @param	bit_value		The bit value of the character, determined
 * 							by the alphabet.
 * @param	target			The target 32-bit integer where the char
 * 							mapping should be inserted.
 * @param	place			The placement inside the integer.
 * @param	bits_per_char	The amount of bits used per character.
 * @see		#map_string_to_bit_string
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void map_to_int(unsigned int bit_value, unsigned int* target, int place, unsigned int bits_per_char) {
	unsigned int clear_mask = 0;

	for (int i = 0; i < bits_per_char; ++i)
		clear_mask = (clear_mask << 1) + 1;

	clear_mask = ~ (clear_mask << (place * bits_per_char));

	unsigned int mark_mask = bit_value << (place * bits_per_char);

	//clear bits at correct location and mark new bits
	*target &= clear_mask;
	*target |= mark_mask;
}

bit_string* map_string_to_bit_string(const char* string, const char_mapping* alphabet) {
	//parameters not initialized
	if (string == 0 || alphabet == 0)
		return 0;

	//string length == 0
	if (strlen(string) == 0) {
		bit_string* ret = calloc(1, sizeof(bit_string));
		ret->length = 0;
		ret->alphabet = (char_mapping*) alphabet;
		ret->mapped_string = 0;
		return ret;
	}

	int bits_per_char = ceil(log10(alphabet[0].bit_value) / log10(2));
	int chars_in_int = floor((sizeof(int) * 8) / bits_per_char);
	int string_index = 0, string_length = strlen(string);
	int array_size = ceil((float)string_length / (float)chars_in_int);

	//too many bits needed to map char
	if (bits_per_char > 32)
		return 0;

	unsigned int* char_array = calloc(array_size, sizeof(int));
	int alphabet_index;

	for (int i = 0; string_index < string_length; ++i) {
		char_array[i] = 0;

		//map as many characters as possible into current array location
		for (int j = 0; j < chars_in_int && string_index < string_length; ++j) {
			alphabet_index = find_by_char(alphabet, string[string_index]);

			//map current char into current array location
			map_to_int(alphabet[alphabet_index].bit_value, (char_array + i), j,
					bits_per_char);

			string_index++;
		}
	}

	//create a bit_string struct to store the results
	bit_string* ret = calloc(1, sizeof(bit_string));

	ret->alphabet = (char_mapping*) alphabet;
	ret->length = array_size;
	ret->mapped_string = char_array;

	return ret;
}

char* map_bit_string_to_string(const bit_string* bit_string) {
	//parameter not initialized
	if (bit_string == 0)
		return 0;

	//length == 0
	if (bit_string->length == 0) {
		char* ret = calloc(1, sizeof(char));
		ret[0] = 0;
		return ret;
	}

	int bits_per_char = ceil(log10(bit_string->alphabet[0].bit_value) / log10(2));
	int chars_in_int = floor((sizeof(int) * 8) / bits_per_char);
	int string_length = chars_in_int * bit_string->length + 1;
	char* string = calloc(string_length, sizeof(char));

	unsigned int current_substr, current_char;
	int string_index = 0, alphabet_index;

	//create mask to mark the current substring
	unsigned int mask = 0;

	for (int i = 0; i < bits_per_char; ++i)
		mask = (mask << 1) + 1;

	unsigned int orig_mask = mask;

	for (int i = 0; i < bit_string->length; ++i) {
		current_substr = bit_string->mapped_string[i];

		//decode all chars from current int
		for (int j = 0; j < chars_in_int; ++j) {
			current_char = (current_substr & mask) >> (bits_per_char * j);
			alphabet_index = find_by_bit_value(bit_string->alphabet, current_char);

			if (alphabet_index != -1)
				string[string_index] = bit_string->alphabet[alphabet_index].character;

			//update mask to take next int
			mask = mask << bits_per_char;
			string_index++;
		}

		mask = orig_mask;
	}

	//append NULL to end of string
	string[string_index] = 0;

	return string;
}
