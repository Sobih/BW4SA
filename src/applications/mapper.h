/**
 * @file	mapper.h
 * @brief	A collection of functions for mapping iteration results onto their
 * 			original strings.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator), Paula Lehtola
 * @bug		No known bugs.
 */

#ifndef MAPPER_H_
#define MAPPER_H_

struct max_repeat_node;
struct triplet;
struct wavelet_tree;
struct bit_vector;

/**
 * @brief A struct for mapping the bwt positions to original positions.
 * @author Paula Lehtola
 * @bugs No known bugs.
*/
typedef struct mapped_pair {
	unsigned int bwt_pos;
	unsigned int orig_pos;

} mapped_pair;

/**
 * @brief A struct for listing all occurrences of maximal repeats.
 * @author Paula Lehtola, Lassi Vapaakallio
 * @bugs No known bugs.
*/

typedef struct max_repeat_indexes {
	unsigned int* indexes;
	unsigned int length;
	unsigned int interval_size; 


} max_repeat_indexes;

/**
 * @brief	Maps the BWT indexes to indexes in the original string in all found maximal repeats.
 *
 * Updates the normal.i value to index in the original string.
 *
 * @param	nodes	An array of all maximal repeat substrings inside the BWT.
 * @param	bwt		The BWT of the original string, in wavelet tree form.
 * @param	count	Length of the nodes-array.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator), Paula Lehtola
 * @bug		No known bugs.
 */
void map_maximal_repeats_to_string(struct max_repeat_node* nodes, struct wavelet_tree* bwt,
		int count, struct bit_vector* bit_vec);

/**
 * @brief	Maps the BWT indexes to indexes in the original string in all found MUMs.
 *
 * Updates the position values in both strings to indexes in the original string.
 *
 * @param	nodes	An array of all triplets returned after iteration.
 * @param	bwt1	BWT of the first string.
 * @param	bwt2	BWT of the second string.
 * @param	count	Length of the array of nodes.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void map_mum_triplets_to_string(struct triplet* nodes,
		struct wavelet_tree* bwt1, struct wavelet_tree* bwt2, int count);

#endif /* MAPPER_H_ */
