/*
 * main.c
 *
 *  Created on: 16.1.2014
 *      Author: lvapaaka
 */

void print_list(char *args[], int len)
{
    int i=0;
    for (;i<len;++i)
        puts(args[i]);
}

#include "count_substrings.h"
#include <stdio.h>

int main(void) {
	/*printf("HELLO, WORLD! \n");*/

	/*printf("%d",count_substrings("abracadabra",11));*/

	//printf("%d\n", lcp("NA", "NANA", 3, 5));

    char *args[] =
    {
        "this", "is", "a", "test", "of", "quicksort", "with", "strings"
    };

    srand((unsigned)time(NULL));
    quicksort(args, sizeof(args)/sizeof(*args));
    print_list(args, sizeof(args)/sizeof(*args));

	return 0;
}
