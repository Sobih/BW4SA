
#ifndef RBWT_H_
#define RBWT_H_

struct wavelet_tree;

char* reverse_string(const char* string, char* target, unsigned int length);

struct wavelet_tree* reverse_bwt(const char* string);


#endif /* RBWT_H_ */
