/**
 * @file	bit_vector.c
 * @brief	Implementation of the bit vector structure.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */

#include <stdlib.h>
#include "../../include/bit_vector.h"

/**
 * @brief	A function for marking a specific bit in a bit vector.
 *
 * This function marks a bit at position pos in the vector supplied
 * as parameter. It is pointed to by every bit vector struct for easy
 * access. The algorithm returns NULL if the vector is NULL or if pos
 * is larger than the amount of bits stored in the vector.
 *
 * @param	vector		The bit vector in which the bit to be
 * 						manipulated lies.
 * @param	pos			The position of the bit inside the vector.
 * @return	The same vector supplied as parameter, or NULL if any
 * 			internal conflicts occur.
 * @see		#unmark_bit_vector_bit
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
struct bit_vec* mark_bit_vector_bit(struct bit_vec* vector, unsigned int pos) {
	unsigned int i = pos / 32;

	if (i > vector->length)
		return 0;

	vector->vector[i] |= (1 << (pos % 32));

	return vector;
}

/**
 * @brief	A function for unmarking a bit inside a bitvector.
 *
 * This function unmarks a bit at position pos in the vector supplied
 * as parameter. It is pointed to by every bit vector struct for easy
 * access. The algorithm returns NULL if the vector is NULL or if pos
 * is larger than the amount of bits stored in the vector.
 *
 * @param	vector		The bit vector in which the bit to be
 * 						manipulated lies.
 * @param	pos			The position of the bit inside the vector.
 * @return	The same vector supplied as parameter, or NULL if any
 * 			internal conflicts occur.
 * @see		#mark_bit_vector_bit
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
struct bit_vec* unmark_bit_vector_bit(struct bit_vec* vector, unsigned int pos) {
	unsigned int i = pos / 32;

	if (i > vector->length)
		return 0;

	vector->vector[i] &= ~ (1 << (pos % 32));

	return vector;
}

/**
 * @brief	A function for checking if a bit is flagged.
 *
 * This function checks if the bit at position pos is set in the
 * vector supplied as parameter. It returns 1 if the bit is flagged,
 * and 0 if the bit is not flagged or if pos is out of range.
 *
 * @param	vector		The vector that is to be checked.
 * @param	pos			The position of the bit inside the vector.
 * @return	1 if the bit is found, 0 if it is not or if any internal
 * 			errors occur.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
int is_bit_marked(struct bit_vec* vector, unsigned int pos) {
	unsigned int i = pos / 32;

	if (i > vector->length)
		return 1;

	unsigned int correct_val = (1 << (pos % 32));

	return (vector->vector[i] & correct_val) == correct_val ? 1 : 0;
}

struct bit_vec* init_bit_vector(struct bit_vec* vector, unsigned int nbits) {
	if (vector == 0 || nbits == 0)
		return 0;

	//init variables
	vector->length = (nbits + 31) / 32;
	vector->mark_bit = &mark_bit_vector_bit;
	vector->unmark_bit = &unmark_bit_vector_bit;
	vector->is_bit_marked = &is_bit_marked;

	//init vector to all zeros
	if ((vector->vector = calloc(vector->length, sizeof(unsigned int))) == 0)
		return 0;

	for (int i = 0; i < vector->length; ++i)
		vector->vector[i] = 0;

	return vector;
}

void free_bit_vector(struct bit_vec* vector) {
	free(vector->vector);
	free(vector);
}
