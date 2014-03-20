//this main function is only for tree drawing

#include "../../include/draw_tree.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
		draw_suffix_tree(argv[1], "suffix_tree.gv");
	}
	else{
		draw_suffix_tree(argv[1], argv[2]);
	}
	return 0;
}
