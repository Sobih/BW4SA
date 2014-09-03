/*
 * count_kmers.h
 *
 *  Created on: 24.6.2014
 *      Author: sobih
 */

#ifndef COUNT_KMERS_H_
#define COUNT_KMERS_H_


struct substring;
struct iterator_state;
struct kmer_kernel;

void count_kmers(struct iterator_state* state, void* results);
struct kmer_kernel* initialize_kmer_kernel(int s_len, int t_len, int kmer_len);
void update_kmer_kernel(struct iterator_state* state, void* results);
double compute_kmer_kernel(struct kmer_kernel* kernel);

#endif /* COUNT_KMERS_H_ */
