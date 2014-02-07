#ifndef ITERATE_H_
#define ITERATE_H_

/**
* @brief struct that describes a substring in BWT
**/
typedef struct substring_struct
{
	int i;
	int j;
	int i_reverse;
	int j_reverse;
	int length;
}substring;	

#endif /* ITERATE_H_ */
