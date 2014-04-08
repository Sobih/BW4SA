/*
 * structs.h
 *
 *  Created on: 20.3.2014
 *      Author: lvapaaka
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct interval
{
	int i;
	int j;
} interval;

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
