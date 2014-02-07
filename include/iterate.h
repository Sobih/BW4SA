#ifndef ITERATE_H_
#define ITERATE_H_

#include "backward_search.h"
#include "bit_vector.h"

typedef struct substring_struct
{
	Interval* normal;
	Interval* reverse;
	int length;
} substring;

/**
* @brief creates vector runs from given string WORK IN PROGRESS
**/
bit_vector* create_runs_vector(char* string);

#endif
