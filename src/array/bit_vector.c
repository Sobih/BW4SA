/**
 * @file	bit_vector.c
 * @brief	Implementation of the bit vector structure.
 * @author	Max Sandberg (REXiator), Topi Paavilainen
 * @bugs	No known bugs.
 */

#include <stdlib.h>
#include "../../include/utils.h"
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
bit_vector* mark_bit_vector_bit(bit_vector* vector, unsigned int pos) {
	unsigned int i = pos / BITS_PER_INT;

	if (i > vector->length)
		return 0;

	vector->vector[i] |= (1 << (pos % BITS_PER_INT));

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
bit_vector* unmark_bit_vector_bit(bit_vector* vector, unsigned int pos) {
	unsigned int i = pos / BITS_PER_INT;

	if (i > vector->length)
		return 0;

	vector->vector[i] &= ~ (1 << (pos % BITS_PER_INT));

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
int is_bit_marked(const bit_vector* vector, unsigned int pos) {
	unsigned int i = pos / BITS_PER_INT;

	if (i > vector->length)
		return 1;

	unsigned int correct_val = (1 << (pos % BITS_PER_INT));

	return (vector->vector[i] & correct_val) == correct_val ? 1 : 0;
}

/**
 * @brief	A simple rank-implementation.
 *
 * This function returns the number of marked bits in the vector up
 * to and including the position pos.
 *
 * @param	vector		The vector that bits are going to be calculated
 * 						for.
 * @param	end			The position after which the count should stop.
 * @param	start		The position where the count should start.
 * @return	The number of marked bits from start up to and including end.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
unsigned int rank_query(const bit_vector* vector, unsigned int start, unsigned int end) {
	unsigned int vec_length = vector->get_length(vector);

	if (vector == 0 || start >= vec_length || start > end)
		return 0;

	if (end >= vec_length)
		end = vec_length - 1;

	bit_vector* vec = (bit_vector*) vector;
	unsigned int count = 0;

	for (int i = start; i <= end; ++i)
		if (vec->is_bit_marked(vec, i))
			count++;

	return count;
}

/**
 * @brief	Returns the length of the bit vector, i.e. the number of bits in it.
 * @param	vector	The vector whose length is to be checked.
 * @return			The length of the bit vector, or the number of bits in it.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
unsigned int get_bit_vector_length(const bit_vector* vector) {
	return vector->length * BITS_PER_INT - vector->filler_bits;
}
	
bit_vector* init_bit_vector(bit_vector* vector, unsigned int nbits) {
	if (vector == 0)
		return 0;

	if (nbits == 0)
		nbits++;

	//init variables
	vector->length = (nbits + BITS_PER_INT - 1) / BITS_PER_INT;
	vector->filler_bits = vector->length * BITS_PER_INT - nbits;
	vector->mark_bit = &mark_bit_vector_bit;
	vector->unmark_bit = &unmark_bit_vector_bit;
	vector->is_bit_marked = &is_bit_marked;
	vector->rank = &rank_query;
	vector->get_length = &get_bit_vector_length;

	//init vector to all zeros
	if ((vector->vector = calloc(vector->length, BITS_PER_INT / 8)) == 0)
		return 0;

	return vector;
}

void free_bit_vector(bit_vector* vector) {
	free(vector->vector);
	free(vector);
}
