#include <string.h>

int get_index(char* alphabet, char c)
{
	int i;
	for(i=0;i<strlen(alphabet);i++){
		if(c == *(alphabet+i)){
			return i;
		}
	}
	return -1;
}

char* get_alphabet(char* string)
{
	//to be implemented :D
	int i;
	
	for(i=0;i<strlen(string);i++){
		
	}
	char* alphabet = "$ABCDR";
	return alphabet;
}

int * create_c_array(char* string)
{
	int i;
	char* alphabet = get_alphabet(string);
	int* carray = calloc(strlen(alphabet), sizeof(int));
	
	for(i=0;i<strlen(string);i++){
		int index = get_index(alphabet, string[i]);
		carray[index] += 1;
	}
	for(i=0;i<strlen(alphabet)-1;i++){
		carray[i+1] = carray[i+1] + carray[i];
	}
	
	return carray;
}

