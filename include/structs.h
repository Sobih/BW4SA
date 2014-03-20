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
} Interval;

typedef struct substring_struct
{
	Interval* normal;
	Interval* reverse;
	int length;
} substring;

#endif /* STRUCTS_H_ */
