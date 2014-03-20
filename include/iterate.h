#ifndef ITERATE_H_
#define ITERATE_H_

struct interval;
struct bit_vec;
struct substring_struct;

/**
* @brief creates vector runs from given string
*
* @param string normal string (rbwt is generated from it)
*
* @return pointer to runs vector
*
* @author Topi Paavilainen
*
* @bug no known bugs
**/
struct bit_vec* create_runs_vector(char* string);

/**
* @brief function that determines if given interval in given reverse-bwt is right-maximal or not.
*
* @param runs bit_vector runs
*
* @param interval interval to be searched
*
* @return 1 if given interval is right-maximal, 0 if not. If interval is not correct function returns 0
*
* @author Topi Paavilainen
*
* @bug no known bugs
**/
int is_reverse_interval_right_maximal(struct bit_vec* runs, struct interval* interval);

/**
 * @brief Iterate goes through all right maximals in the given string and calls the callback-function on each of them.
 * @param string base string to be iterated on
 * @param address of the callback function
 */
void iterate(char* string, void (*callback) (struct substring_struct* substr));

void double_iterate(char* string1, char* string2, void (*callback)(struct substring_struct* substr1, struct substring_struct* substr2));

//an additional iterate function. Works just like normal iterate, but passes few extra parameters to the callback function
void iterate_for_tree_drawing(char* string, void (*callback)(struct substring_struct* substr, struct substring_struct* prev_substr, char c));

#endif
