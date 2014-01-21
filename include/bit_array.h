/*
 * bit_array.h
 *
 *  Created on: 21.1.2014
 *      Author: Max Sandberg
 */

#ifndef BIT_ARRAY_H_
#define BIT_ARRAY_H_

typedef struct {
	char character;
	unsigned int bit_value;
} char_mapping;

char_mapping* map_alphabet(const char* string);


#endif /* BIT_ARRAY_H_ */
