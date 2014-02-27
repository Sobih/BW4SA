
#ifndef BACKWARD_SEARCH_H_
#define BACKWARD_SEARCH_H_

#include "wavelet_tree.h"

/**
* Struct for intervals in bwt
**/
typedef struct interval
{
	int i;
	int j;
} interval;

/**
* @brief function that finds interval of given string from given bwt
* 
* @param bwt of the string
*
* @param string to be searched
* 
* @return interval of searched string
*
**/
interval* backward_search(const wavelet_node* bwt, const struct wavelet_node* string);

/**
 * @brief finds the interval of a given letter in an interval.
 *
 * @param bwt of the string
 *
 * @param interval to be searched
 *
 * @param left extension character
 *
 * @return interval of searched left extension
 *
 */
interval* backward_search_interval(const wavelet_node* bwt, const interval* interval, char c);

#endif /* BACKWARD_SEARCH_H_ */
