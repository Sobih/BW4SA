/**
 * @file	s_to_bwt.h
 * @brief	A function for determining the BWT of a c-string.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef S_TO_BWT_H_
#define S_TO_BWT_H_
#ifndef uchar
typedef unsigned char uchar;
#endif /* UCHAR */

struct wavelet_tree;

/**
 * @brief	Performs Burrows-Wheeler transform on the given string.
 * @param 	string 	The string on which the Burrows-Wheeler transform is applied.
 * @return 			The BWT of the string, represented as a wavelet tree.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct wavelet_tree* s_to_bwt(uchar* string);

#endif /* S_TO_BWT_H_ */
