/**
 * @file	structs.h
 * @brief	A collection of structs used widely in the library.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

/**
 * @brief	A struct for storing an arbitrary two-parameter interval.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct interval
{
	int i;
	int j;
} interval;

/**
 * @brief	A struct for storing intervals of an arbitrary substring inside
 * 			a string as well as the length of the substring.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct substring
{
	char* string;
	interval normal;
	interval reverse;
	int length;
} substring;

/**
 * @brief	A simple structure for storing the starting indices of a MUM inside
 * 			two BWTs and the length of the MUM.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct triplet {
	unsigned int pos1;
	unsigned int pos2;
	unsigned int length;
} triplet;



typedef struct generalized_st_node_freq {
	int s_freq;
	int t_freq;
	int s_children_freq_sum;
	int t_children_freq_sum;
	int s_t_children_freq_sum;
} generalized_st_node_freq;

typedef struct kmer_kernel {
	double n;
	double ds;
	double dt;
	unsigned int kmer_len;
	double cosine;
	unsigned long int calling_counter;
	generalized_st_node_freq* gst_node_freq;
} kmer_kernel;


typedef struct kmer_freq_matrix {
	int** freq_matrix;
	short unsigned int max_freq; // row length
	short unsigned int max_kmer_length; // column length

} kmer_freq_matrix;

typedef struct kullback_leibler_vector{
	double* vector;
	int length;
}kullback_leibler_vector;


#endif /* STRUCTS_H_ */
