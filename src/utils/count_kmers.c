/*
 * count_kmers.c
 *
 *  Created on: 24.6.2014
 *      Author: sobih
 */

#include "count_kmers.h"
#include "structs.h"
#include "../core/iterate.h"
#include "../../include/utils.h"
#include <stdio.h>
#include "../core/c_array.h"



#define END_STRING '$'
// Compute the K-mer complexity of a string S --> C(S,K)=The number of distinct K-mers in S.
void count_kmers(iterator_state* state, void* results){
	wavelet_tree* reverse_bwt = &state->reverse_bwts[0];
	alphabet_data* alpha_data = create_alphabet_interval(&state->current->reverse, reverse_bwt, 0);
	int* nKmers=(int*)results;
	*nKmers=*nKmers + 1 -(alpha_data->length);
//	printf("Length of alpha_data= %i  ... alphabet is %s\n", alpha_data->length,alpha_data->alphabet);
}


// The composition vector is: All words W of length K and their frequency in S.
// Compute the K-mer kernel of two strings S,T --> k(S,T,K)= Cosine of the composition vectors of S and T.
void update_kmer_kernel(iterator_state* state, void* results){
//	printf("****************Calling update_kmer_kernel function************************\n");
	kmer_kernel* kernel =(kmer_kernel*)results;
	kernel->calling_counter++;
	wavelet_tree* s_normal_bwt = &state->bwts[0];
	wavelet_tree* t_normal_bwt = &state->bwts[1];
	wavelet_tree* s_reverse_bwt = &state->reverse_bwts[0];
	wavelet_tree* t_reverse_bwt = &state->reverse_bwts[1];
	substring* s_current_string=&state->current[0];
	substring* t_current_string=&state->current[1];
	alphabet_data* s_child_alphabet, *t_child_alphabet;

//	printf("The substring length=%i\n",s_current_string->length);
//	printf("S reverse interval: %i .. %i\n",s_current_string->reverse.i, s_current_string->reverse.j);
//	printf("T reverse interval: %i .. %i\n",t_current_string->reverse.i, t_current_string->reverse.j);
	int s_freq=s_current_string->reverse.j- s_current_string->reverse.i+1;
	int t_freq=t_current_string->reverse.j- t_current_string->reverse.i+1;

	int s_child_freq_sum=0, t_child_freq_sum=0;
	int* s_child_freq, *t_child_freq;

	if(s_freq>0){
		s_child_alphabet = create_alphabet_interval(&s_current_string->reverse, s_reverse_bwt, 0);
		s_child_freq=malloc(s_child_alphabet->length * sizeof(int*));
		for(int i=0;i<s_child_alphabet->length;i++){

			s_child_freq[i]=s_reverse_bwt->rank(s_reverse_bwt, s_child_alphabet->alphabet[i], s_current_string->reverse.i, s_current_string->reverse.j);
//			printf("Child frequency %i\n",s_child_freq[i]);
//			printf("S right extension %c .Frequency= %i\n",s_child_alphabet->alphabet[i],s_child_freq[i]);
			s_child_freq_sum+=pow(s_child_freq[i],2);
//			printf("s_child_freq[%c]=%i s_child_freq_sum=%i\n",s_child_alphabet->alphabet[i],s_child_freq[i],s_child_freq_sum);
		}
	}
	if(t_freq>0){
		t_child_alphabet = create_alphabet_interval(&t_current_string->reverse, t_reverse_bwt, 0);
		t_child_freq=malloc(t_child_alphabet->length* sizeof(int*));
		for(int i=0;i<t_child_alphabet->length;i++){
			t_child_freq[i]=t_reverse_bwt->rank(t_reverse_bwt, t_child_alphabet->alphabet[i], t_current_string->reverse.i, t_current_string->reverse.j);
//			printf("T right extension %c .Frequency= %i\n",t_child_alphabet->alphabet[i],t_child_freq[i]);
	//		printf("Child frequency (%c) of T_parent (%s): %i\n",t_alpha_data->alphabet[i],t_parent,t_child_freq[i]);
			t_child_freq_sum+=pow(t_child_freq[i],2);
	//		printf("t_child_freq[%c]=%i\n",t_alpha_data->alphabet[i],t_child_freq[i]);
		}
	}
	int i=0,j=0;
	int s_t_child_freq_sum=0;
	if(s_freq>0 && t_freq>0 && s_child_alphabet->length >0 && t_child_alphabet->length >0){
//		printf("Calculating N \n");
		if(s_child_alphabet->alphabet[0]==t_child_alphabet->alphabet[0] && s_child_alphabet->alphabet[0]==END_STRING){
			i++;
			j++;
		}
		while(i<s_child_alphabet->length && j<t_child_alphabet->length){
	//		printf("char[S]=%c , char[T]=%c \n",s_child_alpha_data->alphabet[i],t_alpha_data->alphabet[j]);
			if(s_child_alphabet->alphabet[i]==t_child_alphabet->alphabet[j]){
				s_t_child_freq_sum+=s_child_freq[i]*t_child_freq[j];
				i++;
				j++;
			}else if(s_child_alphabet->alphabet[i]<t_child_alphabet->alphabet[j]){
				i++;
			}else{
				j++;
			}
		}
	}

//	printf("s_child_freq_sum=%i \n",s_child_freq_sum);
//	printf("t_child_freq_sum=%i \n",t_child_freq_sum);
//	printf("s_t_child_freq_sum=%i \n",s_t_child_freq_sum);
	kernel->n+=(s_freq*t_freq)-s_t_child_freq_sum;
//	printf("s_freq=%i  ,t_freq=%i  , s_t_child_freq_sum=%i ,n=%i\n",s_freq,t_freq,s_t_child_freq_sum,kernel->n);
	kernel->ds+=pow(s_freq,2)-s_child_freq_sum;
	kernel->dt+=pow(t_freq,2)-t_child_freq_sum;
//	printf("N=%i , Ds=%i , Dt=%i \n",kernel->n,kernel->ds,kernel->dt);

//	printf("*******************************\n");
}

double compute_kmer_kernel(kmer_kernel* kernel){
	kernel->cosine=(double)kernel->n/sqrt((double)(kernel->ds*kernel->dt));
	printf("*************Statistics***************\n");
	printf("The update_kmer_kernel function was called: %i times\n",kernel->calling_counter);
	printf("N=%i      Ds=%i     Dt=%i\n", kernel->n,kernel->ds, kernel->dt);
	printf("The Cosine Similarity= : %f \n",kernel->cosine);
	return kernel->cosine;
}

kmer_kernel* initialize_kmer_kernel(int s_len, int t_len, int kmer_len){
	kmer_kernel* kernel=malloc(sizeof(kmer_kernel));
	kernel->kmer_len=kmer_len;
	kernel->n=0;
	kernel->ds=s_len+1-kmer_len;
	kernel->dt=t_len+1-kmer_len;
	kernel->cosine=0;
	kernel->calling_counter=0;
	return kernel;
}
