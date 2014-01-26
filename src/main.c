/*
 * main.c
 *
 *  Created on: 16.1.2014
 *      Author: lvapaaka
 */

#include "count_substrings.h"
#include <stdio.h>
#include <stdlib.h>

void print_list(char **args, int len)
{
    int i=0;
    for (;i<len;++i)
        puts(args[i]);

}



int main(void) {
	/*printf("HELLO, WORLD! \n");*/

	/*printf("%d",count_substrings("abracadabra",11));*/

	//printf("%d\n", lcp("NA", "NANA", 3, 5));

    /*char *args[] =
    {
        "this", "is", "a", "test", "of", "quicksort", "with", "strings"
    };

    srand((unsigned)time(NULL));
    quicksort(args, sizeof(args)/sizeof(*args));
	*/
	//char **args = create_suffixes("ABRACADABRA");
	
	/*int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < sizeof(args[i]); j++) {
			printf("%c", args[i][j]);
		}
		printf("\n");
	}*/
    //print_list(args, 11);


	printf("%d\n", distinct_substrings("BANANA"));

	return 0;
}
