#ifndef C_ARRAY_H_
#define C_ARRAY_H_

struct wavelet_tree;
struct interval;

typedef struct alphabet_data {
	char* alphabet;
	unsigned int length;
} alphabet_data;

/**
 * @brief Generates array C of given string. This is still a rather slow version of algorithm, but
 * with small alphabets this should not be a problem.
 * 
 * @param string from the C-array will be generated
 *
 * @return array C which contains starting indexes of each distinct character. 
 *
 * @author Topi Paavilainen
 *
 * @bug no known bugs
 */
unsigned int* create_c_array(const struct wavelet_tree* string, const struct interval* inter,
		const char* alphabet, unsigned int alphabet_length, unsigned int* target);

/**
 * @brief Generates the alphabet of given string in the substring determined by interval struct
 * 
 * @param interval 
 *
 * @param string which the alphabet will be generated from
 *
 * @return alphabet of given interval
 *
 * @author Topi Paavilainen
 *
 * @bug no known bugs
 */
alphabet_data* create_alphabet_interval(const struct interval* interval, const struct wavelet_tree* string,
		alphabet_data* target);

#endif
