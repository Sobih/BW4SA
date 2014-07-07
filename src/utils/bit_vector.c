/**
 * @file	bit_vector.c
 * @brief	Implementation of the bit vector structure.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "bit_vector.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
// WARNING: works only for 32 bit integers
int hamming_weight(int v){
	v = v - ((v >> 1) & 0x55555555);                    // reuse input as temporary
	v = (v & 0x33333333) + ((v >> 2) & 0x33333333);     // temp
	return ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
}

bit_vector* compute_rank_support(bit_vector* vector){
	free(vector->rank_precalc); // Free previous precalc if any
	unsigned int n_blocks = vector->get_length(vector)/BLOCK_SIZE;
	unsigned int words_per_block = BLOCK_SIZE/BITS_PER_INT;
	vector->rank_precalc = malloc(sizeof(int) * n_blocks);
	for(unsigned int block_idx = 0; block_idx < n_blocks; block_idx++){
		vector->rank_precalc[block_idx] = block_idx == 0 ? 0 : vector->rank_precalc[block_idx-1];
		unsigned int  block_start = block_idx*words_per_block;
		for(unsigned int word_idx = block_start; word_idx < block_start + words_per_block; word_idx++){
			//printf("Precalc: %d\n",hamming_weight((vector->vector)[word_idx]));
			vector->rank_precalc[block_idx] += hamming_weight((vector->vector)[word_idx]);
		}
	}
	return vector;
}

/**
 * @brief	A function for marking a specific bit in a bit vector.
 *
 * This function marks a bit at position pos in the vector supplied
 * as parameter. It is pointed to by every bit vector struct for easy
 * access. The algorithm returns NULL if the vector is NULL or if pos
 * is larger than the amount of bits stored in the vector.
 *
 * @param	vector	The bit vector in which the bit to be
 * 					manipulated lies.
 * @param	pos		The position of the bit inside the vector.
 * @return			The same vector supplied as parameter, or NULL if any
 * 					internal conflicts occur.
 * @see		#unmark_bit_vector_bit
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
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
 * @param	vector	The bit vector in which the bit to be
 * 					manipulated lies.
 * @param	pos		The position of the bit inside the vector.
 * @return			The same vector supplied as parameter, or NULL if any
 *		 			internal conflicts occur.
 * @see		#mark_bit_vector_bit
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
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
 * @param	vector	The vector that is to be checked.
 * @param	pos		The position of the bit inside the vector.
 * @return			1 if the bit is found, 0 if it is not or if any internal
 *		 			errors occur.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int is_bit_marked(const bit_vector* vector, unsigned int pos) {
	unsigned int i = pos / BITS_PER_INT;

	if (i > vector->length)
		return 1;

	unsigned int correct_val = (1 << (pos % BITS_PER_INT));

	return (vector->vector[i] & correct_val) == correct_val ? 1 : 0;
}

unsigned int max(unsigned int a, unsigned int b){
	return a > b ? a : b;
}

unsigned int rank_using_precalc(const bit_vector* vector, unsigned int pos){
	unsigned int rank = 0;
	unsigned int block_idx = pos / BLOCK_SIZE;
	unsigned int pos_word_idx = pos / BITS_PER_INT;
	if(block_idx != 0){
		rank += vector->rank_precalc[block_idx-1];
	}

	unsigned int words_per_block = BLOCK_SIZE/BITS_PER_INT;
	unsigned int block_start = block_idx*words_per_block;
	for(unsigned int word_idx = block_start; word_idx < pos_word_idx; word_idx++){
		rank += hamming_weight((vector->vector)[word_idx]);
	}
	unsigned int last_word_leftover = (pos % BITS_PER_INT) + 1;
	unsigned int last_word = (vector->vector)[pos_word_idx];
	//printf("block_idx, pos_word_idx, words_per_block, block_start, last_word_leftover, last_word: %d %d %d %d %d %d\n", block_idx, pos_word_idx, words_per_block, block_start, last_word_leftover, last_word);
	for(unsigned int i = 0; i < last_word_leftover; i++){
		rank += (last_word & (1 << i)) != 0 ? 1 : 0;
	}
	return rank;
}

/**
 * @brief	A simple rank-implementation.
 *
 * This function returns the number of marked bits in the vector up
 * to and including the position pos.
 *
 * @param	vector	The vector that bits are going to be calculated
 * 					for.
 * @param	end		The position after which the count should stop.
 * @param	start	The position where the count should start.
 * @return			The number of marked bits from start up to and including end.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
unsigned int rank_query(const bit_vector* vector, unsigned int start, unsigned int end) {
	unsigned int vec_length = vector->get_length(vector);

	if (vector == 0 || start >= vec_length || start > end)
		return 0;

	if (end >= vec_length)
		end = vec_length - 1;

	bit_vector* vec = (bit_vector*) vector;
	unsigned int count = 0;

	if(!vector->rank_precalc){ // Use the naive method
		printf("No precalc!\n");
		for (int i = start; i <= end; ++i)
			if (vec->is_bit_marked(vec, i))
				count++;
		return count;
	}


	if(start == 0) return rank_using_precalc(vector,end);
	else return rank_using_precalc(vector,end) - rank_using_precalc(vector,start-1);
}

/**
 * @brief	Returns the length of the bit vector, i.e. the number of bits in it.
 * @param	vector	The vector whose length is to be checked.
 * @return			The length of the bit vector, or the number of bits in it.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
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
	vector->rank_precalc = 0; // NULL
	vector->compute_rank_support = &compute_rank_support;
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
	free(vector->rank_precalc);
}
