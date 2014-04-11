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

typedef struct triplet {
	unsigned int pos1;
	unsigned int pos2;
	unsigned int length;
} triplet;

#endif /* STRUCTS_H_ */
