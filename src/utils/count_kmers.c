/*
 * count_kmers.c
 *
 *  Created on: 24.6.2014
 *      Author: sobih
 */

#include "count_kmers.h"


#define END_STRING '$'
// Compute the K-mer complexity of a string S --> C(S,K)=The number of distinct K-mers in S.
void count_kmers(iterator_state* state, void* results){
	wavelet_tree* reverse_bwt = &state->reverse_bwts[0];
	alphabet_data* alpha_data = create_alphabet_interval(&state->current->reverse, reverse_bwt, 0);
	int* nKmers=(int*)results;
	*nKmers=*nKmers + 1 -(alpha_data->length);
//	printf("Length of alpha_data= %i  ... alphabet is %s\n", alpha_data->length,alpha_data->alphabet);
}

void update_kmers_freq_matrix(iterator_state* state, void* results){
	kmer_freq_matrix* freq_matrix=(kmer_freq_matrix*)results;
	substring* s_current_string=&state->current[0];
	wavelet_tree* reverse_bwt = &state->reverse_bwts[0];
	int kmer_len=s_current_string->length;
	int freq=s_current_string->normal.j-s_current_string->normal.i+1;
	int row, column;
	if( kmer_len > freq_matrix->max_kmer_length){
		row=freq_matrix->max_kmer_length;
	}else{
		row=kmer_len-1;
	}
	if(freq > freq_matrix->max_freq){
		column=freq_matrix->max_freq;
	}else{
		column=freq-1;
	}
	freq_matrix->freq_matrix[row][column]=freq_matrix->freq_matrix[row][column]+1;
	char* whole_alphabet = reverse_bwt->get_alphabet(reverse_bwt);
	unsigned int whole_alphabet_length = reverse_bwt->get_alphabet_length(reverse_bwt);
	for(int i = 0; i < whole_alphabet_length; i++) {
		freq=reverse_bwt->rank(reverse_bwt, whole_alphabet[i], s_current_string->reverse.i, s_current_string->reverse.j);
		if( freq> 0){
			if(freq > freq_matrix->max_freq){
				column=freq_matrix->max_freq;
			}else{
				column=freq-1;
			}
			freq_matrix->freq_matrix[row][column]=freq_matrix->freq_matrix[row][column]-1;
		}
	}
}

void compute_substring_complexity(struct iterator_state* state, void* results){
	substring* current_substring = state->current;
	wavelet_tree* reverse_bwt = &state->reverse_bwts[0];
	alphabet_data* alpha_data = create_alphabet_interval(&current_substring->reverse, reverse_bwt, 0);
	long int* nKmers=(long int*)results;
	*nKmers=*nKmers + current_substring->length -(alpha_data->length* current_substring->length);
}

int update_s_t_children_freq(alphabet_data* s_child_alphabet, alphabet_data* t_child_alphabet,int* s_child_freq, int* t_child_freq){
	int s_t_child_freq_sum=0;
	int i=0,j=0;
	if(s_child_alphabet->alphabet[0]==t_child_alphabet->alphabet[0] && s_child_alphabet->alphabet[0]==END_STRING){
			i++;
			j++;
	}
	while(i<s_child_alphabet->length && j<t_child_alphabet->length){
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
	return s_t_child_freq_sum;
}

int update_children_freq(wavelet_tree* reverse_bwt , substring* current_string, alphabet_data* child_alphabet, int* child_freq){
	int child_freq_sum=0;
	for(int i=0;i<child_alphabet->length;i++){
		child_freq[i]=reverse_bwt->rank(reverse_bwt, child_alphabet->alphabet[i], current_string->reverse.i, current_string->reverse.j);
		child_freq_sum+=pow(child_freq[i],2);
	}
	return child_freq_sum;
}

void update_freq(iterator_state* state, generalized_st_node_freq* gst_node_freq){
	wavelet_tree* s_reverse_bwt = &state->reverse_bwts[0];
	wavelet_tree* t_reverse_bwt = &state->reverse_bwts[1];
	substring* s_current_string=&state->current[0];
	substring* t_current_string=&state->current[1];
	alphabet_data* s_child_alphabet, *t_child_alphabet;
	gst_node_freq->s_freq=s_current_string->reverse.j- s_current_string->reverse.i+1;
	gst_node_freq->t_freq=t_current_string->reverse.j- t_current_string->reverse.i+1;

	int* s_child_freq, *t_child_freq;
	if(gst_node_freq->s_freq>0){
		s_child_alphabet = create_alphabet_interval(&s_current_string->reverse, s_reverse_bwt, 0);
		s_child_freq=malloc(s_child_alphabet->length * sizeof(int*));
		gst_node_freq->s_children_freq_sum=update_children_freq(s_reverse_bwt , s_current_string, s_child_alphabet, s_child_freq);
	}
	if(gst_node_freq->t_freq>0){
		t_child_alphabet = create_alphabet_interval(&t_current_string->reverse, t_reverse_bwt, 0);
		t_child_freq=malloc(t_child_alphabet->length * sizeof(int*));
		gst_node_freq->t_children_freq_sum=update_children_freq(t_reverse_bwt , t_current_string, t_child_alphabet, t_child_freq);
	}
	if(gst_node_freq->s_freq > 0 && gst_node_freq->t_freq> 0 && s_child_alphabet->length > 0 && t_child_alphabet->length > 0){
		gst_node_freq->s_t_children_freq_sum=update_s_t_children_freq(s_child_alphabet,t_child_alphabet,s_child_freq,t_child_freq);
	}
}
// The composition vector is: All words W of length K and their frequency in S.
// Compute the K-mer kernel of two strings S,T --> k(S,T,K)= Cosine of the composition vectors of S and T.
void update_kmer_kernel(iterator_state* state, void* results){
//	printf("****************Calling update_kmer_kernel function************************\n");
	kmer_kernel* kernel =(kmer_kernel*)results;
	kernel->calling_counter++;
	generalized_st_node_freq* gst_node_freq=kernel->gst_node_freq;
	update_freq(state, gst_node_freq);
	kernel->n+=(gst_node_freq->s_freq*gst_node_freq->t_freq)-gst_node_freq->s_t_children_freq_sum;
	kernel->ds+=pow(gst_node_freq->s_freq,2)-gst_node_freq->s_children_freq_sum;
	kernel->dt+=pow(gst_node_freq->t_freq,2)-gst_node_freq->t_children_freq_sum;
	initialize_generalized_st_node_freq(kernel->gst_node_freq);
//	printf("*******************************\n");
}

void update_substring_kernel(iterator_state* state, void* results){
//	printf("****************Calling update_substring_kernel function************************\n");
	kmer_kernel* kernel =(kmer_kernel*)results;
	kernel->calling_counter++;
	substring* s_current_string=&state->current[0];
	substring* t_current_string=&state->current[1];
	generalized_st_node_freq* gst_node_freq=kernel->gst_node_freq;
	update_freq(state, gst_node_freq);
	kernel->n+=s_current_string->length*((gst_node_freq->s_freq*gst_node_freq->t_freq)-gst_node_freq->s_t_children_freq_sum);
	kernel->ds+=s_current_string->length*(pow(gst_node_freq->s_freq,2)-gst_node_freq->s_children_freq_sum);
	kernel->dt+=t_current_string->length*(pow(gst_node_freq->t_freq,2)-gst_node_freq->t_children_freq_sum);
	initialize_generalized_st_node_freq(kernel->gst_node_freq);
//	printf("*******************************\n");
}
double compute_kmer_kernel(kmer_kernel* kernel){
	if(kernel->ds==0 || kernel->dt==0)
		kernel->cosine=0;
	else
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
	kernel->gst_node_freq=initialize_generalized_st_node_freq(0);
	return kernel;
}

kmer_kernel* initialize_substring_kernel(int s_len, int t_len){
	kmer_kernel* kernel=malloc(sizeof(kmer_kernel));
	kernel->kmer_len=0;
	kernel->n=0;
	kernel->ds=s_len*(s_len+1)/2;
	kernel->dt=t_len*(t_len+1)/2;
	kernel->cosine=0;
	kernel->calling_counter=0;
	kernel->gst_node_freq=initialize_generalized_st_node_freq(0);
	return kernel;
}

kmer_freq_matrix* initialize_kmer_freq_matrix(int max_freq, int max_kmer_length){
	kmer_freq_matrix* freq_matrix=malloc(sizeof(kmer_freq_matrix));
	if(max_freq==0)
		max_freq=20;
	if(max_kmer_length==0)
		max_kmer_length=20;
	freq_matrix->max_freq=max_freq;
	freq_matrix->max_kmer_length=max_kmer_length;
	freq_matrix->freq_matrix=malloc(sizeof(int*)*(freq_matrix->max_kmer_length+1));
	for(int i=0;i<=freq_matrix->max_kmer_length;i++){
		freq_matrix->freq_matrix[i]=malloc(sizeof(int)*(freq_matrix->max_freq+1));
		for(int j=0;j<=freq_matrix->max_freq;j++){
			freq_matrix->freq_matrix[i][j]=0;
		}
	}
	return freq_matrix;
}

void sum_kmers_freq_matrix(kmer_freq_matrix* freq_matrix, int sequence_length){
	for(int j=0;j<=freq_matrix->max_freq;j++){
		for(int i=freq_matrix->max_kmer_length;i>0;i--){
			freq_matrix->freq_matrix[i-1][j]=freq_matrix->freq_matrix[i][j]+freq_matrix->freq_matrix[i-1][j];
		}
	}
	for(int i=freq_matrix->max_kmer_length;i>=0;i--){
		freq_matrix->freq_matrix[i][0]=freq_matrix->freq_matrix[i][0]+(sequence_length-i);
	}
}

char* getSeparator(int num){
	char* s=malloc(10);
	if(num<0){

	}
	else if(num<10){
		s="---|--";
	}else if(num<100){

	}else if(num <1000){

	}else if(num <10000){

	}else if(num <100000){

	}else{

	}
	return s;
}
void print_kmers_freq_matrix(kmer_freq_matrix* freq_matrix){

	char* dash=malloc(10*(freq_matrix->max_kmer_length+2));
	dash[0]='\0';
	dash[1]=' ';
	printf(" ");
	for(int i=1;i<=freq_matrix->max_freq+1;i++){
		printf("  |  %i",i);
		strcat(dash,"---|--");
	}
	strcat(dash,"---|\n");
	printf("  |\n%s",dash);
	for(int i=0;i<=freq_matrix->max_kmer_length;i++){
		printf("%i",i+1);
		for(int j=0;j<=freq_matrix->max_freq;j++){
			printf("  |  %i",freq_matrix->freq_matrix[i][j]);
		}
		printf("  |\n%s",dash);
	}
}
generalized_st_node_freq* initialize_generalized_st_node_freq(generalized_st_node_freq* gst_node_freq){
	if(gst_node_freq==0)
		gst_node_freq=malloc(sizeof(generalized_st_node_freq));
	gst_node_freq->s_freq=0;
	gst_node_freq->t_freq=0;
	gst_node_freq->s_children_freq_sum=0;
	gst_node_freq->t_children_freq_sum=0;
	gst_node_freq->s_t_children_freq_sum=0;
	return gst_node_freq;
}

kullback_leibler_vector* init_kullback_leibler_vector(int max_kmer){
	kullback_leibler_vector* kl_vector=malloc(sizeof(kullback_leibler_vector));
	kl_vector->length=max_kmer-2;
	double* vector=malloc(sizeof(double)*kl_vector->length);
	for(int i=0;i<kl_vector->length;i++)
		vector[i]=0;
	kl_vector->vector=vector;
	return kl_vector;
}

void createString(substring* source, substring* target, char extension){
	if(target==0)
		target=malloc(sizeof(substring));
	target->string=malloc(source->length+2);
	target->string[0]=extension;
	if(source->length>0){
		printf("Old substring: %s  ,",source->string);
		strcat(target->string,source->string);
	}
	target->string[source->length+1]='\0';
	printf("new substring: %s\n",target->string);
}

kullback_leibler_vector* compute_kl_divergence(iterator_state* state, int max_kmer){
	kullback_leibler_vector* kl_vector=init_kullback_leibler_vector(max_kmer);
	wavelet_tree* bwt = &state->bwts[0], *reverse_bwt = &state->reverse_bwts[0];
	interval* normal = &state->normals[0], *reverse = &state->reverses[0];
	bit_vector* runs = &state->runs_vectors[0], *reverse_runs = &state->reverse_runs_vectors[0];
	substring_stack* stack = &state->stacks[0];
	int bwt_length = bwt->get_num_bits(bwt), i;
	//Initialize first intervals. In the start both intervals are the whole bwt
	normal->i = 0;
	normal->j = bwt_length - 1;
	reverse->i = 0;
	reverse->j = bwt_length - 1;
	//create starting substring
	substring* substr = create_substring(normal, reverse, 0, 0);
	substring* temp, *mid_substring=0, *mid_left_substring;
	int max_length=max_kmer-2;
	int freq_w,freq_w1,freq_w2, freq_w3;
	char* whole_alphabet = bwt->get_alphabet(bwt);
	unsigned int whole_alphabet_length = bwt->get_alphabet_length(bwt);
	unsigned int* c_array = malloc((whole_alphabet_length + 1) * sizeof(unsigned int));
	c_array[0]=0;
	c_array[1]=0;
	int kl_vector_idx=0;
	int left_max=0;
	for (i = 1; i < whole_alphabet_length; i++) {
		freq_w1=bwt->rank(bwt, whole_alphabet[i], substr->normal.i, substr->normal.j); //  F(W[1..l-1])
		c_array[i+1]=freq_w1+c_array[i];
		if(freq_w1>0){
			normal = backward_search_interval(bwt, &substr->normal,whole_alphabet[i], normal);
			reverse = create_reverse_interval(&substr->reverse, normal,c_array, i, reverse);
			createString(substr, mid_substring, whole_alphabet[i] );
			mid_substring= create_substring(normal, reverse, substr->length + 1,mid_substring);
			push(stack, mid_substring);
		}
	}
	while (1) {
		temp = pop(stack);
		if (temp == NULL)
			break;
		mid_substring= create_substring(&temp->normal, &temp->reverse, temp->length, mid_substring);
		mid_substring->string=temp->string;
		freq_w2=mid_substring->normal.j - mid_substring->normal.i + 1; // F(W[2..l-1])
		if(is_interval_maximal(reverse_runs, &mid_substring->reverse)){
			left_max=0;
			if(is_interval_maximal(runs, &mid_substring->normal)){
				left_max=1;
			}
			for (i = 1; i < whole_alphabet_length; i++) {
				freq_w1=bwt->rank(bwt, whole_alphabet[i], mid_substring->normal.i, mid_substring->normal.j); //  F(W[1..l-1])
				c_array[i+1]=freq_w1+c_array[i];
				if(freq_w1>0){
					normal = backward_search_interval(bwt, &mid_substring->normal,whole_alphabet[i], normal);
					reverse = create_reverse_interval(&mid_substring->reverse, normal,c_array, i, reverse);
					createString(mid_substring, mid_left_substring, whole_alphabet[i] );
					mid_left_substring= create_substring(normal, reverse, mid_substring->length + 1,mid_left_substring);
					push(stack, mid_left_substring);
					if(left_max){
						kl_vector_idx=mid_substring->length-1;
						for(int j = 1; j < whole_alphabet_length; j++) {
							freq_w=reverse_bwt->rank(reverse_bwt, whole_alphabet[j], mid_left_substring->reverse.i, mid_left_substring->reverse.j); // F(W[1..l])
							if(freq_w> 0){
								freq_w3=reverse_bwt->rank(reverse_bwt, whole_alphabet[j], mid_substring->reverse.i, mid_substring->reverse.j);//F(W[2..l])
								kl_vector->vector[kl_vector_idx]=kl_vector->vector[kl_vector_idx]+(freq_w* log((double)(freq_w*freq_w2)/((double)(freq_w1*freq_w3))));
								printf("Left extension=%c , right extension=%c\n",whole_alphabet[i],whole_alphabet[j]);
								printf("String is %s %c\n",mid_left_substring->string, whole_alphabet[j]);
								printf("F(W[1..l])=%i, F(W[2..l-1])=%i, F(W[1..l-1])=%i, F(W[2..l])=%i\n",freq_w,freq_w2,freq_w1,freq_w3);
								printf("kl[%i]=%f\n",kl_vector_idx,kl_vector->vector[kl_vector_idx]);
							}
						}
					}
				}
			}
		}
	}
	free(substr);
	return kl_vector;
}
void print_kl_divergence(kullback_leibler_vector* kl_vector){
	for(int i=0;i<kl_vector->length;i++){
		printf("KL[%i]=%f\n",i+3,kl_vector->vector[i]);
	}
}
