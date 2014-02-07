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

bit_vector* create_runs_vector(char* string);

#endif
