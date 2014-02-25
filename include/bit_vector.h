/**
 * @file	bit_vector.h
 * @brief	An array structure for storing strings compressed into
 * 			ints.
 *
 * This contains functions for creating, modifying and manipulating
 * vector-like constructs that are intended for storing strings of
 * text as compressed ints.
 *
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef MOD_BIT_ARRAY_H_
#define MOD_BIT_ARRAY_H_

#define BITS_PER_INT	(sizeof(unsigned int) * 8)

/**
 * @brief	A structure for storing the bit vector and its
 * 			manipulation-functions.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
typedef struct bit_vec {
	unsigned int* vector;
	unsigned int length;
	unsigned int filler_bits;

	struct bit_vec* (*mark_bit) (struct bit_vec* vector, unsigned int pos);
	struct bit_vec* (*unmark_bit) (struct bit_vec* vector, unsigned int pos);
	int (*is_bit_marked) (const struct bit_vec* vector, unsigned int pos);
	unsigned int (*rank) (const struct bit_vec* vector, unsigned int pos);
	unsigned int (*rank_interval) (const struct bit_vec* vector, unsigned int start, unsigned int end);
	unsigned int (*get_length) (const struct bit_vec* vector);
} bit_vector;

/**
 * @brief	Initializes the bit vector given as a parameter to a size of nbits.
 *
 * Initializes the bit vector given as a parameter to a size of nbits. Returns
 * NULL if the vector given is NULL, nbits is 0 or the necessary space can't
 * be successfully allocated.
 *
 * @param	vector		The vector that is to be initialized.
 * @param	nbits		The amount of bits that should be allocated to the vector.
 * @return	The initialized vector, or NULL if any error occurred.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
struct bit_vec* init_bit_vector(struct bit_vec* vector, unsigned int nbits);

/**
 * @brief	Frees the bit vector and all its internal variables.
 * @param	vector		The vector that is to be destroyed.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
void free_bit_vector(struct bit_vec* vector);

#endif /* MOD_BIT_ARRAY_H_ */
