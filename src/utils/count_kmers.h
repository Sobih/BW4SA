/*
 * count_kmers.h
 *
 *  Created on: 24.6.2014
 *      Author: sobih
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structs.h"
#include "../core/iterate.h"
#include "../../include/utils.h"
#include "../core/c_array.h"
#include "../utils/bit_vector.h"
#include "../utils/structs.h"
#include "../utils/wavelet_tree.h"
#include "../core/backward_search.h"
#include "../core/substring_stack.h"


#ifndef COUNT_KMERS_H_
#define COUNT_KMERS_H_


struct substring;
struct iterator_state;
struct kmer_kernel;

void count_kmers(struct iterator_state* state, void* results);
struct kmer_freq_matrix* initialize_kmer_freq_matrix(int max_freq, int max_kmer_length);
void update_kmers_freq_matrix(struct iterator_state* state, void* results);
void sum_kmers_freq_matrix(struct kmer_freq_matrix* freq_matrix, int sequence_length);
void print_kmers_freq_matrix(struct kmer_freq_matrix* freq_matrix);
void compute_substring_complexity(struct iterator_state* state, void* results);
struct generalized_st_node_freq* initialize_generalized_st_node_freq(struct generalized_st_node_freq* gst_node_freq);
struct kmer_kernel* initialize_kmer_kernel(int s_len, int t_len, int kmer_len);
struct kmer_kernel* initialize_substring_kernel(int s_len, int t_len);
void update_kmer_kernel(struct iterator_state* state, void* results);
void update_substring_kernel(struct iterator_state* state, void* results);
double compute_kmer_kernel(struct kmer_kernel* kernel);
struct kullback_leibler_vector* compute_kl_divergence(struct iterator_state* state, int max_kmer);
void print_kl_divergence(kullback_leibler_vector* kl_vector);
void* update_markovian_substring_kernel(struct iterator_state* state, void* results);
struct bwt_interval_alphabets* init_bwt_interval_alphabets(char* alphabet, int num_of_alphabets,struct bwt_interval_alphabets* interval_alphabets);
struct bwt_interval_alphabets** merge_bwt_interval_alphabets(struct bwt_interval_alphabets* bwt1_interval_alphabets, struct bwt_interval_alphabets* bwt2_interval_alphabets, struct bwt_interval_alphabets** bwt_interval_alphabets_array);
#endif /* COUNT_KMERS_H_ */
