
#ifndef BACKWARD_SEARCH_H_
#define BACKWARD_SEARCH_H_

/**
* Struct for intervals in bwt
**/
typedef struct interval
{
	int i;
	int j;
} Interval;

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
Interval* backward_search(const char* bwt, const char* string);

/**
 * @brief Counts the number of occurrences of the given character in the given string before the given index.
 *
 * @param index search for c from 0 to (index -1)
 * @param c character to be counted
 * @param string the string searched
 * @author Lassi Vapaakallio, Neo Lehtola
 * @return how many occurrences of the character c
 */
int rank(const int index, const char c, const char* string);

#endif /* BACKWARD_SEARCH_H_ */
