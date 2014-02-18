#include "dbwt.h"
#include "../../include/backward_search.h"
#include <stdlib.h>
#include <string.h>

uchar* bwt_to_s(uchar* bwt) 
{
	long n = strlen(bwt);
	uchar* string = calloc(n+1, sizeof(uchar));
	int i;	

	Interval* interval = malloc(sizeof(Interval));
	interval->i = 0;
	interval->j = 0;
	Interval* result = backward_search_interval(bwt, interval, '$');
	string[0] = '$';

	for (i = 1; i < n; i++) {
		//result = backward_search_interval(bwt, result, ?);
		// mites se kirjain, jota haettu intervalli edustaa, palautetaan?
	}
	
	



}
