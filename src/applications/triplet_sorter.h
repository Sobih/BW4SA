#ifndef TRIPLET_SORTER_H_
#define TRIPLET_SORTER_H_

struct triplet;
struct max_repeat_node;

int compare_triplets_pos1(struct triplet first, struct triplet second);
int compare_triplets_pos2(struct triplet first, struct triplet second);
int compare_max_repeat_nodes(struct max_repeat_node first, struct max_repeat_node second);

void compare_quick_sort(void* arr, unsigned int arr_size, unsigned int entry_size, int (*compare)(void* first, void* second));

#endif /* TRIPLET_SORTER_H_ */
