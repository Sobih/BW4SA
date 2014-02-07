#include "../../include/bit_vector.h"
#include "../../include/iterate.h"
#include <stdlib.h>
#include <string.h>

char* to_rbwt(char* string);

bit_vector* create_runs_vector(char* string)
{
	char* rbwt = to_rbwt(string);
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
char* to_rbwt(char* string)
{
	return "abdbc$rraaaa";
}

