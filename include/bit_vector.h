/**
 * @file	bit_vector.h
 * @brief	An array structure for storing strings compressed into
 * 			integers.
 *
 * This contains functions for creating, modifying and manipulating
 * vector-like constructs that are intended for storing strings of
 * text as compressed integers.
 *
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef BIT_VECTOR_H_
#define BIT_VECTOR_H_

#include <limits.h>

#define BITS_PER_INT	(sizeof(unsigned int) * 8)

/**
 * @brief	A structure for storing the bit vector and its
 * 			manipulation-functions.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
typedef struct bit_vector {
	unsigned int* vector;
	unsigned int length;
	unsigned int filler_bits;

	/**
	 * @brief	Function pointer to a function that flags the bit at position <code>pos</code>
	 * 			inside the bit vector <code>vector</code>.
	 * @param	vector	A bit vector that is to be manipulated.
	 * @param	pos		The position of the bit that is to be flagged.
	 * @return			The manipulated bit vector.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	struct bit_vector* (*mark_bit) (struct bit_vector* vector, unsigned int pos);

	/**
	 * @brief	Function pointer to a function that unflags the bit at position <code>pos</code>
	 * 			inside the bit vector <code>vector</code>.
	 * @param	vector	A bit vector that is to be manipulated.
	 * @param	pos		The position of the bit that is to be unflagged.
	 * @return			The manipulated bit vector.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	struct bit_vector* (*unmark_bit) (struct bit_vector* vector, unsigned int pos);

	/**
	 * @brief	Function pointer to a function that checks if the bit at position <code>pos</code>
	 * 			is marked inside the bit vector <code>vector</code>.
	 * @param	vector	A bit vector that is to be checked.
	 * @param	pos		Position of the bit whose state is to be checked.
	 * @return			<code>1</code> if the bit is set, <code>0</code> otherwise.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	int (*is_bit_marked) (const struct bit_vector* vector, unsigned int pos);

	/**
	 * @brief	Function pointer to a function that counts the number of set bits inside
	 * 			a vector inside the interval start -> end.
	 * @param	vector	The vector whose set bits is to be counted.
	 * @param	start	The index inside the vector from which the count should start.
	 * @param	end		The index inside the vector where the count should end.
	 * @return			The number of set bits between start and end, or 0 if start > end
	 * 					or <code>vector</code> is uninitialized.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	unsigned int (*rank) (const struct bit_vector* vector, unsigned int start, unsigned int end);

	/**
	 * @brief	Function pointer to a function that returns the number of bits used
	 * 			by the bit vector supplied as parameter.
	 * @param	vector	The vector for which a length should be determined.
	 * @return			The number of bits used by the vector supplied as parameter.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	unsigned int (*get_length) (const struct bit_vector* vector);
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
bit_vector* init_bit_vector(bit_vector* vector, unsigned int nbits);

/**
 * @brief	Frees the bit vector and all its internal variables.
 * @param	vector		The vector that is to be destroyed.
 * @author	Max Sandberg (REXiator)
 * @bugs	No known bugs.
 */
void free_bit_vector(bit_vector* vector);

#endif /* BIT_VECTOR_H_ */
