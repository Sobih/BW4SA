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

/**
 * @brief	A simple structure for storing a mapped string, the
 * 			alphabet it is using and the length of the mapped
 * 			string.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct {
	unsigned int* mapped_string;
	char_mapping* alphabet;
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
 * @param	string		The string that will be used to map the alphabet.
 * @return	An array of mapped characters.
 * @see		#char_mapping
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char_mapping* map_alphabet(const char* string);

/**
 * @brief	Compresses a string to a series of 32-bit integers.
 *
 * This function takes a string and the alphabet used by the string
 * as input, and maps the string to a series of 32-bit integers using
 * the bit values assigned by the alphabet of the string.
 *
 * @param	string		The string that is to be compressed.
 * @param	alphabet	The alphabet and assigned bit values of the string.
 * @return	A struct containing the compressed string, the length of the
 * 			compressed string and its alphabet.
 * @see		#map_bit_string_to_string
 * @see		#map_alphabet
 * @see		#bit_string
 * @see		#char_mapping
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
bit_string* map_string_to_bit_string(const char* string, const char_mapping* alphabet);

/**
 * @brief	Decompresses the given bit string to a human readable
 * 			string.
 *
 * This function takes a previously compressed string and decompresses
 * it to a human readable format.
 *
 * @param	bit_string		The previously compressed string that
 * 							should be decompressed.
 * @return	A normal c-string.
 * @see		#map_string_to_bit_string
 * @see		#bit_string
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char* map_bit_string_to_string(const bit_string* bit_string);

#endif /* BIT_ARRAY_H_ */
