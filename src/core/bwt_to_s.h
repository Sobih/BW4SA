/**
 * @file	bwt_to_s.h
 * @brief	A function to convert BWT back to an original string. 
 *
 * @author	Paula Lehtola, Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs
 */

#ifndef BWT_TO_S_H_
#define BWT_TO_S_H_

struct wavelet_tree;

/**
 * @brief A function to convert a BWT of a string back to an original string.
 *
 * This function takes a BWT of a string in wavelet tree form as an input and
 * converts it back to the original string (without $) in c-string form.
 *
 * @param 	bwt		The bwt of a string, represented as a wavelet tree.
 * @return 			The original string.
 * @author 	Paula Lehtola, Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

char* bwt_to_s(const struct wavelet_tree* bwt);


#endif /* BWT_TO_S_H_ */
