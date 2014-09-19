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

typedef struct kmer_kernel {
	long int n;
	long int ds;
	long int dt;
	unsigned int kmer_len;
	double cosine;
	unsigned long int calling_counter;
} kmer_kernel;

#endif /* STRUCTS_H_ */
