/**
 * @file	c_array.h
 * @brief	A collection of functions for creating c-arrays and shortened alphabets.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef C_ARRAY_H_
#define C_ARRAY_H_

struct wavelet_tree;
struct interval;

/**
 * @brief	A simple struct for storing an alphabet as a string and its length.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct alphabet_data {
	char* alphabet;
	unsigned int length;
} alphabet_data;

/**
 * @brief	Generates array C of given string in wavelet tree form.
 *
 * A c-array is an array of indexes to the starting location inside a BWT of each distinct
 * character used by the BWT, ordered lexicographically.
 *
 * @param 	string 			The string in wavelet tree form from which a c-array should
 * 							be generated.
 * @param	inter			An interval of the substring from which the c-array should
 * 							be generated. If <code>NULL</code>, the entire string is used.
 * @param	alphabet		    The alphabet used by the string. If <code>NULL</code>, the alphabet
 * 							of the wavelet tree is used.
 * @param	alphabet_length	Length of the alphabet supplied as parameter. If the alphabet
 * 							is <code>NULL</code>, this parameter will be disregarded.
 * @param	target			An unsigned integer array where the results should be stored.
 * 							If target is <code>NULL</code>, a new array will be allocated
 * 							and returned instead.
 * @return 					Array C which contains starting indexes of each distinct
 * 							character used in the alphabet.
 * @author 	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug 	No known bugs.
 */
unsigned int* create_c_array(const struct wavelet_tree* string, const struct interval* inter,
		const char* alphabet, unsigned int alphabet_length, unsigned int* target);

/**
 * @brief 	Generates the alphabet of a substring of a string.
 * @param 	inter	The starting and ending indices of the substring inside the string,
 * 					stored in an <code>interval</code>-struct.
 * @param 	string 	The string, in wavelet tree form, from which the substring is to
 * 					be determined.
 * @param	target	The structure where the results should be stored. If <code>NULL</code>,
 * 					a new <code>alphabet_data</code>-struct will be allocated and returned.
 * @return 			The alphabet used by the substring.
 * @author 	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug 	No known bugs.
 */
alphabet_data* create_alphabet_interval(const struct interval* inter, const struct wavelet_tree* string,
		alphabet_data* target);


alphabet_data* create_all_alphabet_vector(alphabet_data* current_alphabet);

#endif

