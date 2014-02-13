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
int is_bit_marked(const struct bit_vec* vector, unsigned int pos) {
	unsigned int i = pos / 32;

	if (i > vector->length)
		return 1;

	unsigned int correct_val = (1 << (pos % 32));

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
 * @param	pos			The position after which the count should stop.
 * @return	The number of marked bits up to and including pos.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
unsigned int rank_query(const struct bit_vec* vector, unsigned int pos) {
	struct bit_vec* vec = (struct bit_vec*) vector;
	unsigned int count = 0;

	for (int i = 0; i < (vec->length * 32); ++i)
		if (vec->is_bit_marked(vec, i))
			count++;

	return count;
}

/**
 * @brief	A rank query for given interval.
 *
 * This function returns number of flagged bits in bits from start to end
 * (including start and end bits)
 *
 * @param	vector		The vector that bits are going to be calculated
 * 						for.
 * @param	start		The position where count starts from.
 * @param	end			The position where count ends.
 * @return	The number of marked bits from (and including) start to (and including) end.
 * @author	Topi Paavilainen
 * @bugs	No known bugs.
 */
unsigned int rank_query_interval(const struct bit_vec* vector, unsigned int start, unsigned int end) {
	unsigned int count = 0;
	
	if (start > vector->length * 32 || end > vector->length * 32 || start >= end)
		return 0;

	for (int i = start; i <= end; i++)
		if (vector->is_bit_marked(vector, i)) count ++;

	return count;
}
	

struct bit_vec* init_bit_vector(struct bit_vec* vector, unsigned int nbits) {
	if (vector == 0)
		return 0;

	if (nbits == 0)
		nbits++;

	//init variables
	vector->length = (nbits + 31) / 32;
	vector->mark_bit = &mark_bit_vector_bit;
	vector->unmark_bit = &unmark_bit_vector_bit;
	vector->is_bit_marked = &is_bit_marked;
	vector->rank = &rank_query;
	vector->rank_interval = &rank_query_interval;

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
