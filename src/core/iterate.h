#ifndef ITERATE_H_
#define ITERATE_H_

struct substring;

/**
 * @brief Iterate goes through all right maximals in the given string and calls the callback-function on each of them.
 * @param string base string to be iterated on
 * @param address of the callback function
 */
void iterate(char* string, void (*callback) (struct substring* substr));

void double_iterate(char* string1, char* string2, void (*callback)(struct substring* substr1, struct substring* substr2));

//an additional iterate function. Works just like normal iterate, but passes few extra parameters to the callback function
//void iterate_for_tree_drawing(char* string, void (*callback)(substring* substr, substring* prev_substr, char c));

#endif
