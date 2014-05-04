/**
 * @file	backward_search.h
 * @brief	Contains functions for performing backward searches on
 * 			strings in wavelet tree-form.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */

#ifndef BACKWARD_SEARCH_H_
#define BACKWARD_SEARCH_H_

struct interval;
struct wavelet_tree;

/**
 * @brief	A function for finding the interval of given string in given BWT.
 * @param 	bwt 	BWT of the string to be looked up, given in wavelet tree-
 * 					form.*
 * @param 	string 	The string to be searched inside the BWT, given in wavelet
 * 					tree-form.
 * @param	target	The interval-structure where the results should be stored.
 * 					If NULL, a new interval-structure will be allocated and
 * 					returned.
 * @return 			The interval of the searched string inside the BWT, or NULL
 * 					if it can't be found.
 * @see		wavelet_tree.h
 * @see		structs.h#interval
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct interval* backward_search(const struct wavelet_tree* bwt, const struct wavelet_tree* string, struct interval* target);

/**
 * @brief	Finds the interval of a given letter of an interval in a BWT.
 * @param 	bwt 	BWT of a string, given in wavelet tree-form.
 * @param 	inter 	Interval to be searched inside BWT.
 * @param	c		Character to be looked for inside the interval.
 * @param 	target 	The interval-structure where the results should be stored.
 * 					If NULL, a new interval-structure will be allocated and
 * 					returned.
 * @return 			The interval of the searched character inside the BWT, or
 * 					NULL if it can't be found.
 * @see		#backward_search
 * @see		wavelet_tree.h
 * @see		structs.h#interval
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
struct interval* backward_search_interval(const struct wavelet_tree* bwt, const struct interval* inter, char c,
		unsigned int* c_array, struct interval* target);

#endif /* BACKWARD_SEARCH_H_ */
