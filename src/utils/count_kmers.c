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
	printf("N=%f      Ds=%f     Dt=%f\n", kernel->n,kernel->ds, kernel->dt);
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

substring* createString(substring* source, substring* target, char extension){
	if(target==0){
		target=malloc(sizeof(substring));
	}
	else{
		//free(target->string);
	}
//	printf("Ya welad elmaras\n");
	target->string=malloc(source->length+2);
//	printf("Ya welad elmaraaa\n");
	target->string[0]=extension;
	if(source->length>0){
		strcat(target->string,source->string);
//		printf("Ya welad elmaraaassssssssss\n");
//		printf("Old substring: %s  ,",source->string);
//		printf("Ya welad elmaraaassssssssss 111\n");
	}
//	printf("Ya welad elmaraaaaqqq\n");
	target->string[source->length+1]='\0';
//	printf("new substring: %s\n",target->string);
	return target;
}

kullback_leibler_vector* compute_kl_divergence(iterator_state* state, int max_kmer){
	kullback_leibler_vector* kl_vector=init_kullback_leibler_vector(max_kmer);
	wavelet_tree* bwt = &state->bwts[0], *reverse_bwt = &state->reverse_bwts[0];
	interval* normal = &state->normals[0], *reverse = &state->reverses[0];
	bit_vector* runs = &state->runs_vectors[0], *reverse_runs = &state->reverse_runs_vectors[0];
	substring_stack* stack = &state->stacks[0];
	int bwt_length = bwt->get_num_bits(bwt);
	//Initialize first intervals. In the start both intervals are the whole bwt
	normal->i = 0;
	normal->j = bwt_length - 1;
	reverse->i = 0;
	reverse->j = bwt_length - 1;
	//create starting substring
	substring* temp = create_substring(normal, reverse, 0, 0);
	substring* mid_substring=0, *mid_left_substring=0;
	int freq_w,freq_w1,freq_w2, freq_w3;
	char* whole_alphabet = bwt->get_alphabet(bwt);
	unsigned int whole_alphabet_length = bwt->get_alphabet_length(bwt);
	unsigned int* c_array = malloc((whole_alphabet_length + 1) * sizeof(unsigned int));
	c_array[0]=0;
	int kl_vector_idx=0;
	int left_max=0;
	for (int i = 0; i < whole_alphabet_length; i++) {
		freq_w1=bwt->rank(bwt, whole_alphabet[i], temp->normal.i, temp->normal.j); //  F(W[1..l-1])
		c_array[i+1]=freq_w1+c_array[i];
		if(freq_w1>0 && whole_alphabet[i]!=END_STRING){
			normal = backward_search_interval(bwt, &temp->normal,whole_alphabet[i], normal);
			reverse = create_reverse_interval(&temp->reverse, normal,c_array, i, reverse);
			mid_substring=createString(temp, mid_substring, whole_alphabet[i] );
			mid_substring= create_substring(normal, reverse, temp->length + 1,mid_substring);
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
			for (int i = 0; i < whole_alphabet_length; i++) {
				freq_w1=bwt->rank(bwt, whole_alphabet[i], mid_substring->normal.i, mid_substring->normal.j); //  F(W[1..l-1])
				c_array[i+1]=freq_w1+c_array[i];
				if(freq_w1>0 && whole_alphabet[i]!=END_STRING){
					normal = backward_search_interval(bwt, &mid_substring->normal,whole_alphabet[i], normal);
					reverse = create_reverse_interval(&mid_substring->reverse, normal,c_array, i, reverse);
					mid_left_substring=createString(mid_substring, mid_left_substring, whole_alphabet[i] );
					mid_left_substring= create_substring(normal, reverse, mid_substring->length + 1,mid_left_substring);
					push(stack, mid_left_substring);
					if(left_max){
						kl_vector_idx=mid_substring->length-1;
						for(int j = 0; j < whole_alphabet_length; j++) {
							freq_w=reverse_bwt->rank(reverse_bwt, whole_alphabet[j], mid_left_substring->reverse.i, mid_left_substring->reverse.j); // F(W[1..l])
							if(freq_w> 0 && whole_alphabet[j]!=END_STRING){
								freq_w3=reverse_bwt->rank(reverse_bwt, whole_alphabet[j], mid_substring->reverse.i, mid_substring->reverse.j);//F(W[2..l])
								kl_vector->vector[kl_vector_idx]=kl_vector->vector[kl_vector_idx]+(freq_w* log((double)(freq_w*freq_w2)/((double)(freq_w1*freq_w3))));
								//printf("Left extension=%c , right extension=%c\n",whole_alphabet[i],whole_alphabet[j]);
								printf("String is %s%c\n",mid_left_substring->string, whole_alphabet[j]);
								printf("F(W[1..l])=%i, F(W[2..l-1])=%i, F(W[1..l-1])=%i, F(W[2..l])=%i\n",freq_w,freq_w2,freq_w1,freq_w3);
								//printf("kl[%i]=%f\n",kl_vector_idx,kl_vector->vector[kl_vector_idx]);
							}
						}
					}
				}
			}
		}
	}
	free(temp);
	free(mid_substring);
	free(mid_left_substring);
	return kl_vector;
}
void print_kl_divergence(kullback_leibler_vector* kl_vector){
	for(int i=0;i<kl_vector->length;i++){
		printf("KL[%i]=%f\n",i+3,kl_vector->vector[i]);
	}
}

substring* update_substring_interval(wavelet_tree* bwt, substring* current_substring, char c, int c_array_idx, unsigned int* c_array, substring* target){
//	printf("update_substring_interval Start\n");
	if (target == 0)
		target = malloc(sizeof(substring));
	backward_search_interval(bwt, &current_substring->normal,c, &target->normal);
	create_reverse_interval(&current_substring->reverse, &target->normal,c_array, c_array_idx, &target->reverse);
//	target=createString(current_substring, target, c);
	target->length=current_substring->length + 1;
//	printf("New intervals are: [%i,%i]   [%i,%i]\n",target->normal.i,target->normal.j,target->reverse.i,target->reverse.j);
//	printf("update_substring_interval End\n");
	return target;
}

void update_markovian_freq(wavelet_tree* bwt, substring* mid_left_substring,  substring* mid_substring,
		bwt_interval_alphabets* w_interval_alphabets, bwt_interval_alphabets* mid_right_interval_alphabets,bwt_interval_alphabets** w_alphabets_array,
		int* freq_w, double* word_prob, double* kernelD){
//	printf("update_markovian_freq Start\n");
//	printf("*******************************Getting right extension intervals***************************\n");
	w_interval_alphabets=init_bwt_interval_alphabets(0,0,w_interval_alphabets);
	w_interval_alphabets=bwt->get_interval_alphabets(bwt, 0, mid_left_substring->reverse.i, mid_left_substring->reverse.j, w_interval_alphabets, 0, bwt->get_alphabet_length(bwt)-1);
//	printf("**************************************************************************************************\n");

	w_alphabets_array=merge_bwt_interval_alphabets(w_interval_alphabets,mid_right_interval_alphabets,w_alphabets_array);
	bwt_interval_alphabets* w_merged_alphabets=w_alphabets_array[0];
	bwt_interval_alphabets* mid_right_merged_alphabets=w_alphabets_array[1];
	char c;
	for(int i=0;i<w_merged_alphabets->length;i++){
		c=w_merged_alphabets->alphabets_vector[i];
		freq_w[1]=mid_right_merged_alphabets->alphabets_freq[i];//F(W[2..l])
		if(freq_w[1]> 0 && c!=END_STRING){
			freq_w[0]=w_merged_alphabets->alphabets_freq[i]; // F(W[1..l])
//			if(freq_w[0]==0)
//				printf("Got Zero");
			word_prob[i]=((double)(freq_w[0]*freq_w[2])/(double)(freq_w[1]*freq_w[3]))-1;
			(*kernelD)+=pow(word_prob[i],2);
		}else{
			word_prob[i]=0;
		}
//		printf("String 1:%s%c F([1..l])=%i   F([2..l-1])=%i  F([1..l-1])=%i   F([2..l])=%i     "
//		"P(W)=%f\n",mid_left_substring1->string,alphabet[j],freq_w_1,freq_w2_1,freq_w1_1,freq_w3_1,word_prob1[counter1]);
	}
//	printf("update_markovian_freq End\n");
}

void* update_markovian_substring_kernel(iterator_state* state, void* results){
	printf("****************************************************************************\n");
	printf("update_markovian_substring_kernel\n");
	kmer_kernel* kernel =(kmer_kernel*)results;
	wavelet_tree* bwt1 = &state->bwts[0], *bwt2 = &state->bwts[1];
	wavelet_tree* rev_bwt1 = &state->reverse_bwts[0], *rev_bwt2 = &state->reverse_bwts[1];
	bit_vector* runs1 = &state->runs_vectors[0], *runs2 = &state->runs_vectors[1];
	bit_vector* rev_runs1 = &state->reverse_runs_vectors[0], *rev_runs2 = &state->reverse_runs_vectors[1];
	substring_stack* stack1 = &state->stacks[0], *stack2 = &state->stacks[1];
	unsigned int* c_array1 = state->c_arrays[0], *c_array2 = state->c_arrays[1];

	//Initialize first intervals. In the start both intervals are the whole bwt
	interval* normal1 = &state->normals[0], *normal2 = &state->normals[1];
	interval* reverse1 = &state->reverses[0], *reverse2 = &state->reverses[1];
	normal1->i = 0;
	normal1->j = bwt1->get_num_bits(bwt1) - 1;
	reverse1->i = 0;
	reverse1->j = bwt1->get_num_bits(bwt1) - 1;

	normal2->i = 0;
	normal2->j = bwt2->get_num_bits(bwt2) - 1;
	reverse2->i = 0;
	reverse2->j = bwt2->get_num_bits(bwt2) - 1;
	//create starting substring
	substring* temp1 = create_substring(normal1, reverse1, 0, 0);
	substring* temp2 = create_substring(normal2, reverse2, 0, 0);

	alphabet_data* union_alphabet=get_alphabets_union(bwt1->get_alphabet_length(bwt1), bwt1->get_alphabet(bwt1),
			bwt2->get_alphabet_length(bwt2), bwt2->get_alphabet(bwt2));
	substring* mid_substring1=0, *mid_left_substring1=0;
	substring* mid_substring2=0, *mid_left_substring2=0;
	int* freq_w1=malloc(sizeof(int)*4);
	int* freq_w2=malloc(sizeof(int)*4); //freq_w[0]=F(W[1..l]), freq_w[1]=//F(W[2..l]), freq_w[2]=F(W[2..l-1]), freq_w[3]=//F(W[1..l-1])
	unsigned int union_alphabet_length = union_alphabet->length;
	int num_of_words=union_alphabet_length;
	double* word_prob1=calloc(num_of_words,sizeof(double)),* word_prob2=calloc(num_of_words,sizeof(double));

	c_array1[0]=0;
	c_array2[0]=0;
	bwt_interval_alphabets* w1_mid_left_alphabets=init_bwt_interval_alphabets(bwt1->get_alphabet(bwt1),bwt1->get_alphabet_length(bwt1),0);
	bwt_interval_alphabets* w2_mid_left_alphabets=init_bwt_interval_alphabets(bwt2->get_alphabet(bwt2),bwt2->get_alphabet_length(bwt2),0);

	bwt_interval_alphabets* w1_interval_alphabets=init_bwt_interval_alphabets(bwt1->get_alphabet(bwt1),bwt1->get_alphabet_length(bwt1),0);
	bwt_interval_alphabets* w2_interval_alphabets=init_bwt_interval_alphabets(bwt2->get_alphabet(bwt2),bwt2->get_alphabet_length(bwt2),0);

	bwt_interval_alphabets* mid_right_interval_alphabets1=init_bwt_interval_alphabets(bwt1->get_alphabet(bwt1),bwt1->get_alphabet_length(bwt1),0);
	bwt_interval_alphabets* mid_right_interval_alphabets2=init_bwt_interval_alphabets(bwt2->get_alphabet(bwt2),bwt2->get_alphabet_length(bwt2),0);


	w1_mid_left_alphabets=bwt1->get_interval_alphabets(bwt1, 0, temp1->normal.i, temp1->normal.j, w1_mid_left_alphabets, 0, bwt1->get_alphabet_length(bwt1)-1);
	w2_mid_left_alphabets=bwt2->get_interval_alphabets(bwt2, 0, temp2->normal.i, temp2->normal.j, w2_mid_left_alphabets, 0, bwt2->get_alphabet_length(bwt2)-1);
	bwt_interval_alphabets** w1_w2_mid_left_alphabets_array=merge_bwt_interval_alphabets(w1_mid_left_alphabets,w2_mid_left_alphabets,0);
	bwt_interval_alphabets* w1_mid_left_merged_alphabets=w1_w2_mid_left_alphabets_array[0];
	bwt_interval_alphabets* w2_mid_left_merged_alphabets=w1_w2_mid_left_alphabets_array[1];

	bwt_interval_alphabets** w1_alphabets_array=0, **w2_alphabets_array=0;
	char c=0;

	for (int i = 0; i < w1_mid_left_merged_alphabets->length; i++) {
		c=w1_mid_left_merged_alphabets->alphabets_vector[i];
		freq_w1[2]=w1_mid_left_merged_alphabets->alphabets_freq[i];
		freq_w2[2]=w2_mid_left_merged_alphabets->alphabets_freq[i];
		c_array1[i+1]=freq_w1[2]+c_array1[i];
		c_array2[i+1]=freq_w2[2]+c_array2[i];
		if(c==END_STRING)
			continue;
		if(freq_w1[2]==0 && freq_w2[2]==0)
			continue;
		if(freq_w1[2]>0){
			mid_substring1=update_substring_interval(bwt1,temp1,c,i,c_array1,mid_substring1);
//			normal1 = backward_search_interval(bwt1, &temp1->normal,c, normal1);
//			reverse1 = create_reverse_interval(&temp1->reverse, normal1,c_array1, i, reverse1);
//			mid_substring1=createString(temp1, mid_substring1, c);
//			mid_substring1= create_substring(normal1, reverse1, temp1->length + 1,mid_substring1);
		}else{
			mid_substring1= create_dummy_substring(0);
		}
		if(freq_w2[2]>0){
//			normal2 = backward_search_interval(bwt2, &temp2->normal,c, normal2);
//			reverse2 = create_reverse_interval(&temp2->reverse, normal2,c_array2, i, reverse2);
//			mid_substring2=createString(temp2, mid_substring2, c );
//			mid_substring2= create_substring(normal2, reverse2, temp2->length + 1,mid_substring2);
			mid_substring2=update_substring_interval(bwt2,temp2,c,i,c_array2,mid_substring2);

		}else{
			mid_substring2= create_dummy_substring(0);
		}
//		printf("Pushing to stack 1 string:%s     interval[%i,%i]    reverse interval[%i,%i]\n", mid_substring1->string,mid_substring1->normal.i,
//				mid_substring1->normal.j,mid_substring1->reverse.i,mid_substring1->reverse.j);
//		printf("Pushing to stack 2 string:%s     interval[%i,%i]    reverse interval[%i,%i]\n", mid_substring2->string,mid_substring2->normal.i,
//				mid_substring2->normal.j,mid_substring2->reverse.i,mid_substring2->reverse.j);
		push(stack1, mid_substring1);
		push(stack2, mid_substring2);
	}
	int right_max1, right_max2, left_max1, left_max2;
	while (1) {
		temp1 = pop(stack1);
		temp2 = pop(stack2);
		if (temp1 == NULL && temp2==NULL)
			break;
		w1_mid_left_alphabets=init_bwt_interval_alphabets(0,0,w1_mid_left_alphabets);
		w2_mid_left_alphabets=init_bwt_interval_alphabets(0,0,w2_mid_left_alphabets);
//		printf("****************************************************************************\n");
//		printf("****************************************************************************\n");
//		printf("Poping from stack 1 string:%s interval[%i,%i]    reverse interval[%i,%i]    Stack_Pointer:%i \n", temp1->string,temp1->normal.i,temp1->normal.j,temp1->reverse.i,temp1->reverse.j, stack1->array_ptr);
//		printf("poping from stack 2 string:%s interval[%i,%i]    reverse interval[%i,%i]    Stack_Pointer:%i \n", temp2->string,temp2->normal.i,temp2->normal.j,temp2->reverse.i,temp2->reverse.j, stack2->array_ptr);
		mid_substring1= create_substring(&temp1->normal, &temp1->reverse, temp1->length, mid_substring1);
		mid_substring1->string=temp1->string;
		freq_w1[2]=mid_substring1->normal.j - mid_substring1->normal.i + 1; // F(W[2..l-1])

		mid_substring2= create_substring(&temp2->normal, &temp2->reverse, temp2->length, mid_substring2);
		mid_substring2->string=temp2->string;
		freq_w2[2]=mid_substring2->normal.j - mid_substring2->normal.i + 1; // F(W[2..l-1])

		right_max1=0,right_max2=0,left_max1=0,left_max2=0;
		if(is_interval_maximal(rev_runs1, &mid_substring1->reverse)){
			right_max1=1;
//			printf("*******************************Getting S left extension intervals***************************\n");
			w1_mid_left_alphabets=bwt1->get_interval_alphabets(bwt1, 0, mid_substring1->normal.i, mid_substring1->normal.j, w1_mid_left_alphabets, 0, bwt1->get_alphabet_length(bwt1)-1);
//			printf("****************************************************************************\n");
//			printf("****************************************************************************\n");
		}
		if(is_interval_maximal(rev_runs2, &mid_substring2->reverse)){
			right_max2=1;
//			printf("*******************************Getting T left extension intervals******************************\n");
			w2_mid_left_alphabets=bwt2->get_interval_alphabets(bwt2, 0, mid_substring2->normal.i, mid_substring2->normal.j, w2_mid_left_alphabets, 0, bwt2->get_alphabet_length(bwt2)-1);
//			printf("****************************************************************************\n");
//			printf("****************************************************************************\n");
		}
		if(right_max1 && is_interval_maximal(runs1, &mid_substring1->normal)){
			left_max1=1;
		}
		if(right_max2 && is_interval_maximal(runs2, &mid_substring2->normal)){
			left_max2=1;
		}
		if(right_max1 || right_max2){
//			printf("Hello 1\n");
			w1_w2_mid_left_alphabets_array=merge_bwt_interval_alphabets(w1_mid_left_alphabets,w2_mid_left_alphabets,w1_w2_mid_left_alphabets_array);
			w1_mid_left_merged_alphabets=w1_w2_mid_left_alphabets_array[0];
			w2_mid_left_merged_alphabets=w1_w2_mid_left_alphabets_array[1];
			mid_right_interval_alphabets1=init_bwt_interval_alphabets(0,0,mid_right_interval_alphabets1);
			mid_right_interval_alphabets2=init_bwt_interval_alphabets(0,0,mid_right_interval_alphabets2);
//			printf("Hello 2\n");
			if(left_max1){
//				printf("*******************************Getting S mid-to-right extension intervals***************************\n");
				mid_right_interval_alphabets1=rev_bwt1->get_interval_alphabets(rev_bwt1, 0, mid_substring1->reverse.i, mid_substring1->reverse.j, mid_right_interval_alphabets1, 0, bwt1->get_alphabet_length(bwt1)-1);
//				printf("**************************************************************************************************\n");
			}
			if(left_max2){
//				printf("*******************************Getting T mid-to-right extension intervals***************************\n");
				mid_right_interval_alphabets2=rev_bwt2->get_interval_alphabets(rev_bwt2, 0, mid_substring2->reverse.i, mid_substring2->reverse.j, mid_right_interval_alphabets2, 0, bwt2->get_alphabet_length(bwt2)-1);
//				printf("**************************************************************************************************\n");
			}
			for(int i=0;i<w1_mid_left_merged_alphabets->length;i++){

				freq_w1[3]=0, freq_w1[3]=0;
				c=w1_mid_left_merged_alphabets->alphabets_vector[i];
//				printf("Hello 3 %c\n",c);
//				printf("Current Left Extension: %c\n",c);
				if(right_max1)
					freq_w1[3]=w1_mid_left_merged_alphabets->alphabets_freq[i]; //F(W[1..l-1])
				if(right_max2)
					freq_w2[3]=w2_mid_left_merged_alphabets->alphabets_freq[i]; //F(W[1..l-1])
				c_array1[i+1]=freq_w1[3]+c_array1[i];
				c_array2[i+1]=freq_w2[3]+c_array2[i];
				if(c==END_STRING)
					continue;
				if(freq_w1[3]==0 && freq_w2[3]==0)
					continue;
				if(freq_w1[3]>0){
					mid_left_substring1=update_substring_interval(bwt1,mid_substring1,c,i,c_array1,mid_left_substring1);
					if(left_max1){
						update_markovian_freq(rev_bwt1,mid_left_substring1,mid_substring1,w1_interval_alphabets, mid_right_interval_alphabets1,w1_alphabets_array, freq_w1,word_prob1,&(kernel->ds));
					}
				}else{
					mid_left_substring1=create_dummy_substring(0);
				}
				if(freq_w2[3]>0){
					mid_left_substring2= update_substring_interval(bwt2,mid_substring2,c,i,c_array2,mid_left_substring2);
					if(left_max2){
						update_markovian_freq(rev_bwt2,mid_left_substring2,mid_substring2,w2_interval_alphabets, mid_right_interval_alphabets2,w2_alphabets_array, freq_w2,word_prob2,&(kernel->dt));
					}
				}
				else{
					mid_left_substring2=create_dummy_substring(0);
				}
				if(freq_w1[3]>0 || freq_w2[3]>0){
					push(stack1, mid_left_substring1);
					push(stack2, mid_left_substring2);
//					printf("Pushing to stack 1 string:%s     interval[%i,%i]    reverse interval[%i,%i]\n", mid_left_substring1->string,mid_left_substring1->normal.i,
//							mid_left_substring1->normal.j,mid_left_substring1->reverse.i,mid_left_substring1->reverse.j);
//					printf("Pushing to stack 2 string:%s     interval[%i,%i]    reverse interval[%i,%i]\n", mid_left_substring2->string,mid_left_substring2->normal.i,
//							mid_left_substring2->normal.j,mid_left_substring2->reverse.i,mid_left_substring2->reverse.j);
				}
				if(left_max1 && left_max2 && freq_w1[3]>0 && freq_w2[3]>0){
//					printf("left_max1=%i  left_max2=%i   Counter1=%i\n",left_max1,left_max2,counter1);
					for(int i=0;i<num_of_words;i++){
						kernel->n+=word_prob1[i]*word_prob2[i];
					}
				}
			}
		}
	}
	printf("DONE\n");
	free(mid_substring1);
	free(mid_substring2);
	free(mid_left_substring1);
	free(mid_left_substring2);
	free(word_prob1);
	free(word_prob2);
	free(w1_mid_left_alphabets);
	free(w2_mid_left_alphabets);
	free(w1_w2_mid_left_alphabets_array);
	compute_kmer_kernel(kernel);
	return kernel;
}
bwt_interval_alphabets* init_bwt_interval_alphabets(char* alphabet, int num_of_alphabets,bwt_interval_alphabets* interval_alphabets){
	if(interval_alphabets==0){
		interval_alphabets=malloc(sizeof(bwt_interval_alphabets));
		interval_alphabets->alphabets_freq=malloc(sizeof(int)*num_of_alphabets);
		interval_alphabets->alphabets_vector=malloc(sizeof(char)*(num_of_alphabets+1));
		int i=0;
		for(i=0; i<num_of_alphabets;i++){
			interval_alphabets->alphabets_vector[i]=alphabet[i];
			interval_alphabets->alphabets_freq[i]=0;
		}
		interval_alphabets->alphabets_vector[i]='\0';
		interval_alphabets->length=num_of_alphabets;
	}
	else{
		for(int i=0; i<interval_alphabets->length;i++){
			interval_alphabets->alphabets_freq[i]=0;
		}
	}
	return interval_alphabets;
}
bwt_interval_alphabets** merge_bwt_interval_alphabets(bwt_interval_alphabets* bwt1_interval_alphabets, bwt_interval_alphabets* bwt2_interval_alphabets, bwt_interval_alphabets** bwt_interval_alphabets_array){
	int alpha_data1_length=bwt1_interval_alphabets->length, alpha_data2_length=bwt2_interval_alphabets->length;
	char *alpha_data1=bwt1_interval_alphabets->alphabets_vector, *alpha_data2=bwt2_interval_alphabets->alphabets_vector;
	if(bwt_interval_alphabets_array==0){
		alphabet_data* union_alphabet=get_alphabets_union(alpha_data1_length,alpha_data1, alpha_data2_length,alpha_data2);
		bwt_interval_alphabets_array=malloc(sizeof(bwt_interval_alphabets*)*2);
		bwt_interval_alphabets_array[0]=malloc(sizeof(bwt_interval_alphabets));
		bwt_interval_alphabets_array[1]=malloc(sizeof(bwt_interval_alphabets));
		bwt_interval_alphabets_array[0]->alphabets_vector=union_alphabet->alphabet;
		bwt_interval_alphabets_array[1]->alphabets_vector=union_alphabet->alphabet;
		bwt_interval_alphabets_array[0]->length=union_alphabet->length;
		bwt_interval_alphabets_array[1]->length=union_alphabet->length;
		bwt_interval_alphabets_array[0]->alphabets_freq=malloc(sizeof(int)*bwt_interval_alphabets_array[0]->length);
		bwt_interval_alphabets_array[1]->alphabets_freq=malloc(sizeof(int)*bwt_interval_alphabets_array[1]->length);
	}
	int index1=0, index2=0;
	int *alpha_data1_freq=bwt1_interval_alphabets->alphabets_freq, *alpha_data2_freq=bwt2_interval_alphabets->alphabets_freq;
	for(int i=0;i<bwt_interval_alphabets_array[0]->length;i++){
		if(bwt_interval_alphabets_array[0]->alphabets_vector[i]==alpha_data1[index1]){
			bwt_interval_alphabets_array[0]->alphabets_freq[i]=alpha_data1_freq[index1];
			index1++;
		}else {
			bwt_interval_alphabets_array[0]->alphabets_freq[i]=0;
		}
		if(bwt_interval_alphabets_array[1]->alphabets_vector[i]==alpha_data2[index2]){
			bwt_interval_alphabets_array[1]->alphabets_freq[i]=alpha_data2_freq[index2];
			index2++;
		}else {
			bwt_interval_alphabets_array[1]->alphabets_freq[i]=0;
		}
	}
	return bwt_interval_alphabets_array;
}

