
/**
* @brief This is an additional interface for c-array, which is only used for testing! do not use this elsewhere.
* @author Topi Paavilainen
**/
#include "../../include/backward_search.h"

int* create_c_array(const char* string);

int get_index(const char* alphabet, const char c);

char* get_alphabet(const char* string);

int* create_c_array_interval(const Interval* interval, char* bwt);

char* create_alphabet_interval(const Interval* interval, char* bwt);
