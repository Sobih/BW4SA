#include "../../include/mum.h"
#include "../../include/maximal_repeats.h"
#include "../../include/utils.h"
#include <stdio.h>
// swap function in utils.h

int compare_ints(int* a, int* b) {
	return *a - *b;
}

int compare_triplets_pos1(triplet* first, triplet* second) {

	printf("first: %d second: %d\n", first->pos1, second->pos1);
	return first->pos1 - second->pos1;
}

int compare_triplets_pos2(triplet* first, triplet* second) {
	return first->pos2 - second->pos2;
}

int compare_max_repeat_nodes(max_repeat_node* first, max_repeat_node* second) {
	if (first->normal->i != second->normal->i) {
		return first->normal->i - second->normal->i;
	} else {
		return first->normal->j - second->normal->j;
	}
}



void compare_quicksort(void* arr, unsigned int entry_size, unsigned int a, unsigned int b, int (*compare)(void* first, void* second)) {
	if (a >= b)
		return;

	//printf("TESTING\n");
	void* key = (arr + (a * entry_size));
	int i = a + 1, j = b;
	
	while (i < j) {
		
		//int w = compare((arr + (j * entry_size)), key);
		//printf("w: %d\n", w);
		while (i < j && compare((arr + (j * entry_size)), key) >= 0) {
			j--;
			//printf("j: %d\n", j);
		}
			

		while (i < j && compare((arr + (i * entry_size)), key) <= 0) {
				
			i++;
			//printf("i: %d\n", i);
		}
			
		//printf("i: %d j: %d\n", i, j);
		if (i < j) {	
			//printf("SWAPPING");		
			swap(arr, entry_size, i, j);
		}

	}

	//int x = compare((arr + (a * entry_size)), (arr + (i * entry_size)));
	//printf("x: %d\n", x);
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
