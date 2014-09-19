/**
 * @file	c_array.c
 * @brief	Implementation of the algorithms related to the c-array.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#include "c_array.h"

//#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "../utils/structs.h"
//#include "../utils/utils.h"
#include "../utils/wavelet_tree.h"
//#include "backward_search.h"


static const short int BITS_SIZE=8;
static const short int NUM_OF_CHARS=128;


unsigned int* create_c_array(const wavelet_tree* string, const interval* inter, const char* alphabet,
		unsigned int alphabet_length, unsigned int* target) {
	if (string == 0)
		return 0;

	if (!alphabet) {
		alphabet = string->get_alphabet(string);
		alphabet_length = string->get_alphabet_length(string);
	}

	unsigned int start = 0, end = INT_MAX;
	alphabet_data* data = 0;

	if (inter) {
		start = inter->i;
		end = inter->j;
		data = create_alphabet_interval(inter, string, 0);
		alphabet = data->alphabet;
		alphabet_length = data->length;
	}

	if (target == 0)
		target = malloc((alphabet_length + 1) * sizeof(unsigned int));

	target[0] = 0;

	for(int i = 0; i < alphabet_length - 1; i++) {
		//count number of occurrences of each character
		target[i + 1] = string->rank(string, alphabet[i], start, end);

		//add previous count to each number
		target[i + 1] += target[i];
	}

	if (data) {
		free(data->alphabet);
		free(data);
	}

	return target;
}

alphabet_data* create_alphabet_interval(const interval* inter, const wavelet_tree* string, alphabet_data* target) {
	if (inter == 0 || string == 0 || inter->i > inter->j)
		return 0;

	char* whole_alphabet = string->get_alphabet(string);
	unsigned int whole_alphabet_length = string->get_alphabet_length(string);
	char* new_alphabet = malloc(sizeof(char)*(whole_alphabet_length+1)); // +1 for the null terminator

	if (target == 0)
		target = malloc(sizeof(alphabet_data));
	else
		free(target->alphabet);

	/* Find the characters that are present in the interval */
	int nChars = 0;
	for(int i = 0; i < whole_alphabet_length; i++) {
		if(string->rank(string, whole_alphabet[i], inter->i, inter->j) > 0){
			new_alphabet[nChars] = whole_alphabet[i];
			nChars++;
		}
	}
	new_alphabet[nChars] = 0;
	target->length = nChars;
	target->alphabet = new_alphabet;

	return target;
}


void reinitialize_alphabet_bit_vector(alphabet_bit_vector* alpha_bit_vector){
	for(int i=0;i<alpha_bit_vector->length;i++){
		alpha_bit_vector->bit_vector[i]=0;
	}
}
alphabet_bit_vector* initialize_alphabet_bit_vector(alphabet_bit_vector* alpha_bit_vector){
	if(alpha_bit_vector==0)
		alpha_bit_vector=malloc(sizeof(alphabet_bit_vector));
	alpha_bit_vector->length=NUM_OF_CHARS/(sizeof(int)*BITS_SIZE);
	int* bit_vector=malloc(alpha_bit_vector->length);
	for(int i=0;i<alpha_bit_vector->length;i++){
		bit_vector[i]=0;
	}
	alpha_bit_vector->bit_vector=bit_vector;
	return alpha_bit_vector;
}

alphabet_bit_vector* mark_alphabet_bits(alphabet_data* alphabet, alphabet_bit_vector* alpha_bit_vector){
	if(alpha_bit_vector->length==0)
		alpha_bit_vector=initialize_alphabet_bit_vector(alpha_bit_vector);
	else
		reinitialize_alphabet_bit_vector(alpha_bit_vector);
	if(alphabet==0)
		return alpha_bit_vector;
	short int INT_BITS=sizeof(int)*BITS_SIZE;
	int idx=0;
	int shift=0;
	char c=0;
	for(int i=0;i< alphabet->length;i++){
		c=alphabet->alphabet[i];
		idx=(c-1)/INT_BITS;
		shift=(c-1)%INT_BITS;
		alpha_bit_vector->bit_vector[idx] = (1 << shift)|alpha_bit_vector->bit_vector[idx] ;
	}
//	printf("mark_alphabet_bits Done\n");
//	printBinary(alpha_bit_vector->bit_vector, alpha_bit_vector->length);
	return alpha_bit_vector;
}

alphabet_bit_vector* mark_alphabet_bit(char c, alphabet_bit_vector* alpha_bit_vector){
	short int INT_BITS=sizeof(int)*BITS_SIZE;
	int idx=(c-1)/INT_BITS;
	int shift=(c-1)%INT_BITS;
	alpha_bit_vector->bit_vector[idx] = (1 << shift)|alpha_bit_vector->bit_vector[idx] ;
	return alpha_bit_vector;
}

alphabet_bit_vector* unmark_alphabet_bit(char c, alphabet_bit_vector* alpha_bit_vector){
	short int INT_BITS=sizeof(int)*BITS_SIZE;
	int idx=(c-1)/INT_BITS;
	int shift=(c-1)%INT_BITS;
	alpha_bit_vector->bit_vector[idx] = (~(1 << shift))&alpha_bit_vector->bit_vector[idx] ;
	return alpha_bit_vector;
}

int get_alphabet_bit(char c, alphabet_bit_vector* alpha_bit_vector){
	short int INT_BITS=sizeof(int)*BITS_SIZE;
	int idx=(c-1)/INT_BITS;
	int shift=(c-1)%INT_BITS;
	return (alpha_bit_vector->bit_vector[idx] >> shift) & 1 ;
}
