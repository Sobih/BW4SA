

/**
 * @brief Generates array C of given string. This is still a rather slow version of algorithm, but
 * with small alphabets this should not be a problem.
 * 
 * @param string from the C-array will be generated
 *
 * @return array C which contains starting indexes of each distinct character. last index of the array is -1, to indicate end of the array.
 *
 * @author Topi Paavilainen
 *
 * @bug no known bugs
 */
int* create_c_array(const char* string);

char* get_alphabet(const char* string);
