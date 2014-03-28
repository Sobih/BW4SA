#include "../../include/iterate.h"

int dist_substr_count = 0;


/*
typedef struct substring_struct
{
	Interval* normal;
	Interval* reverse;
	int length;
} substring;
*/

void search_distinct_substrings(substring* substr)
{
	dist_substr_count += substr->length;
	// the degree of the node is the size of the interval

}
