#include "../../include/mum.h"
#include "../../include/maximal_repeats.h"
#include "../../include/utils.h"
#include <stdio.h>
// swap function in utils.h

int compare_triplets_pos1(void* first, void* second) {
	triplet* f = (triplet*)first;
	triplet* s = (triplet*)second;
	return f->pos1 - s->pos1;
}

int compare_triplets_pos2(void* first, void* second) {
	triplet* f = (triplet*)first;
	triplet* s = (triplet*)second;
	return f->pos2 - s->pos2;
}

int compare_max_repeat_nodes(void* first, void* second) {
	max_repeat_node* f = (max_repeat_node*)first;
	max_repeat_node* s = (max_repeat_node*)second;
	if (f->normal->i != s->normal->i) {
		return f->normal->i - s->normal->i;
	} else {
		return f->normal->j - s->normal->j;
	}
}



void compare_quicksort(void* arr, unsigned int entry_size, unsigned int a, unsigned int b, int (*compare)(void* first, void* second)) {
	if (a >= b)
		return;

	void* key = (arr + (a * entry_size));
	int i = a + 1, j = b;
	
	while (i < j) {

		while (i < j && compare((arr + (j * entry_size)), key) >= 0) 
			j--;

		while (i < j && compare((arr + (i * entry_size)), key) <= 0) 			
			i++;

		if (i < j) 	
			swap(arr, entry_size, i, j);
	}


	if (compare((arr + (a * entry_size)), (arr + (i * entry_size))) > 0) {

		swap(arr, entry_size, a, i);
		compare_quicksort(arr, entry_size, a, i-1, compare);
		compare_quicksort(arr, entry_size, i + 1, b, compare);
	} else {
		compare_quicksort (arr, entry_size, a+1, b, compare);
	}
}

void compare_quick_sort(void* arr, unsigned int arr_size, unsigned int entry_size, int (*compare)(void* first, void* second)) {
	if (arr == 0 || arr_size == 0 || entry_size == 0)
		return;

	compare_quicksort(arr, entry_size, 0, arr_size-1, compare);

}
