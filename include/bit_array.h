/**
 * @file	bit_array.h
 * @brief	An array structure for storing strings compressed into
 * 			longs.
 *
 * This contains functions for creating, modifying and manipulating
 * array-like constructs that are intended for storing strings of
 * text as compressed longs.
 *
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef BIT_ARRAY_H_
#define BIT_ARRAY_H_

/**
 * @brief	A simple structure for storing characters and their
 * 			mapped bit values.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct {
	char character;
	unsigned int bit_value;
} char_mapping;

typedef struct {
	unsigned int* mapped_string;
	unsigned int length;
} bit_string;

/**
 * @brief	Maps characters to bit values used for compression.
 *
 * This function takes a string as input, orders it lexicographically
 * and assigns bit values to the determined alphabet. This is done
 * to preserve as much memory as possible, i.e. if the alphabet is
 * large, the mapping will reduce the amount of bytes needed to
 * compress strings that use the alphabet.
 *
 * @param	string	The string that will be used to map the alphabet.
 * @return	An array of mapped characters.
 * @see		#char_mapping
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char_mapping* map_alphabet(const char* string);

unsigned int* map_string_to_int_array(const char* string, char_mapping* alphabet);

char* map_int_array_to_string(const unsigned int* char_array, char_mapping* alphabet);

#endif /* BIT_ARRAY_H_ */
