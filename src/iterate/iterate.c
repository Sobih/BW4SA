#include "../../include/bit_vector.h"
#include "../../include/iterate.h"
#include "../../include/rbwt.h"
#include "../../include/backward_search.h"
#include <stdlib.h>
#include <string.h>

bit_vector* create_runs_vector(char* string)
{
	char* rbwt = reverse_bwt(string);
	bit_vector* runs = malloc(sizeof(bit_vector));
	init_bit_vector(runs, strlen(rbwt));
	
	runs->mark_bit(runs, 0);
	for(int i = 1; i < strlen(rbwt); i++) {
		if(rbwt[i-1] != rbwt[i]) {
			runs->mark_bit(runs, i);
		}
	}
	return runs;
}

int is_reverse_interval_right_maximal(bit_vector* runs, Interval* interval)
{
	if(interval->i >= interval->j) return 0;
	
	if(runs->rank_interval(runs, (interval->i)+1, interval->j) > 0)
	{
		return 1;
	}
	else return 0;
}
