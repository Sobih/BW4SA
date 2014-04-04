/**
 * @file	rbwt.h
 * @brief	A collection of functions for creating the BWT of the reverse of a string.
 * @author	Paula Lehtola, Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef RBWT_H_
#define RBWT_H_

struct wavelet_tree;

/**
 * @brief	Reverses the direction of a string.
 * @param	string	The c-string to be reversed.
 * @param	target	A c-string where the result should be stored. If <code>NULL</code>, a
 * 					new c-string will be allocated and returned.
 * @param	length	Length of the string to be reversed (and thus also the length
 * 					of the reversed string).
 * @return			The reversed string.
 * @author	Paula Lehtola, Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char* reverse_string(const char* string, char* target, unsigned int length);

/**
 * @brief	Creates the BWT of the reverse of the given string.
 * @param	string	The c-string to be reversed and have a BWT created for.
 * @return			The BWT of the reversed string represented as a wavelet tree.
 * @author	Paula Lehtola, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct wavelet_tree* reverse_bwt(const char* string);


#endif /* RBWT_H_ */
