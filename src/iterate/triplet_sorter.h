#ifndef TRIPLET_SORTER_H_
#define TRIPLET_SORTER_H_

int compare_ints(int a, int b);
int compare_triplets_pos1(triplet first, triplet second);
int compare_triplets_pos2(triplet first, triplet second);
int compare_max_repeat_nodes(max_repeat_node first, max_repeat_node second);

void compare_quick_sort(void* arr, unsigned int arr_size, unsigned int entry_size, int (*compare)(void* first, void* second));

#endif /* TRIPLET_SORTER_H_ */
