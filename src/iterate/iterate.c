#include "../../include/bit_vector.h"
#include "../../include/iterate.h"
#include "../../include/rbwt.h"
#include "../../include/backward_search.h"
#include "../../include/c_array.h"
#include "../bwt/s_to_bwt.h"
#include "substring_stack.h"
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

Interval* update_reverse_interval(Interval* interval, const char* alphabet, const int* c_array, const char c);

void iterate(char* string){
	unsigned char* bwt = s_to_BWT(string);
	bit_vector* runs = create_runs_vector(string);

	substring_stack* stack = create_stack(10);
	substring* start = malloc(sizeof(substring));

	Interval* start_normal = malloc(sizeof(Interval));
	start_normal->i = 0;
	start_normal->j = strlen(bwt) - 1;

	Interval* start_reverse = malloc(sizeof(Interval));
	start_reverse->i = 0;
	start_reverse->j = strlen(bwt) - 1;

	start->normal = start_normal;
	start->reverse = start_reverse;

	push(stack,start);
	substring* new_substring;
	substring* substring;

	while(1){
		substring = pop(stack);
		if(substring == NULL){
			break;
		}
		// Determine characters that precede the interval
		char* alphabet = create_alphabet_interval(substring->normal,bwt);
		int* c_array = create_c_array_interval(substring->normal,bwt);

		int i;
		for(i = 0; i < strlen(alphabet);i++){
			Interval* normal = backward_search_interval(bwt,substring->normal,alphabet[i]);
			Interval* reverse = update_reverse_interval(substring->reverse, alphabet, c_array, alphabet[i]);
			if(is_reverse_interval_right_maximal(runs, reverse)) {
				new_substring = malloc(sizeof(substring));
				new_substring->normal = normal;
				new_substring->reverse = reverse;
				// callback function pointers
				push(stack,new_substring);
			} else {
				free(normal);
				free(reverse);
			}
		}
		free(alphabet);
		free(c_array);
	}
}

Interval* update_reverse_interval(Interval* interval, const char* alphabet, const int* c_array, const char c){
	Interval* updated = malloc(sizeof(Interval));
	int i = interval->i;
	int j = interval->j;

	int index_in_c = get_char_index(c_array, alphabet, c);

	updated->i = i + c_array[index_in_c];

	if(index_in_c == strlen(alphabet) - 1){
		updated->j = j;
	} else {
		updated->j = c_array[index_in_c + 1] - 1;
	}

	return updated;
}
