/**
 * @file	bwt_to_s.h
 * @brief	A function to convert BWT back to an original string. 
 *
 * @author	Paula Lehtola, Lassi Vapaakallio
 * @bug		No known bugs
 */

#ifndef BWT_TO_S_H_
#define BWT_TO_S_H_

/**
 * @brief A function to convert a BWT of a string back to an original string.
 *
 * This function takes a BWT of a string as an input and converts it back to the original string  
 * (without $)
 *
 * @param bwt		The bwt of a string
 * @return string	The original string
 * @author 			Paula Lehtola, Lassi Vapaakallio
 * @bug				No known bugs
 */

char* bwt_to_s(char* bwt); 


#endif /* BWT_TO_S_H_ */
