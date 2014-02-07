#ifndef ITERATE_H_
#define ITERATE_H_

#include "backward_search.h";

typedef struct substring_struct
{
	Interval* normal;
	Interval* reverse;
	int length;
} substring;	

#endif
