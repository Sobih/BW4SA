#ifndef BW4SA_H_
#define BW4SA_H_

#define		MAX_REPEATS		0
#define		MUM				1
#define		MEM				2
#define		DOT_TREE		3

#define BITS_PER_INT	(sizeof(unsigned int) * 8)

/**
 * @brief	Unsigned int typedefed as the type of iterate that is to be performed.
 * @author	Max Sandberg (REXiator)
 */
typedef 	unsigned int	iterate_t;

/**
 * @brief	A struct for storing an arbitrary two-parameter interval.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct interval
{
	int i;
	int j;
} interval;

/**
 * @brief	A struct for storing intervals of an arbitrary substring inside
 * 			a string as well as the length of the substring.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct substring
{
	interval normal;
	interval reverse;
	int length;
} substring;

/**
 * @brief	A simple structure for storing the starting indices of a MUM inside
 * 			two BWTs and the length of the MUM.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct triplet {
	unsigned int pos1;
	unsigned int pos2;
	unsigned int length;
} triplet;

/**
 * @brief	A simple struct for storing an alphabet as a string and its length.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct alphabet_data {
	char* alphabet;
	unsigned int length;
} alphabet_data;

/**
 * @brief	A simple stack-structure for storing substrings.
 *
 * Can hold any amount of data, array size is automatically doubled if memory gets full.
 *
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug 	No known bugs.
 */
typedef struct substring_stack
{
	struct substring* array;
	int array_size;
	int array_ptr;
} substring_stack;

/**
 * @brief	A structure for storing the bit vector and its
 * 			manipulation-functions.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct bit_vector {
	unsigned int* vector;
	unsigned int length;
	unsigned int filler_bits;

	/**
	 * @brief	Function pointer to a function that flags the bit at position <code>pos</code>
	 * 			inside the bit vector <code>vector</code>.
	 * @param	vector	A bit vector that is to be manipulated.
	 * @param	pos		The position of the bit that is to be flagged.
	 * @return			The manipulated bit vector.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	struct bit_vector* (*mark_bit) (struct bit_vector* vector, unsigned int pos);

	/**
	 * @brief	Function pointer to a function that unflags the bit at position <code>pos</code>
	 * 			inside the bit vector <code>vector</code>.
	 * @param	vector	A bit vector that is to be manipulated.
	 * @param	pos		The position of the bit that is to be unflagged.
	 * @return			The manipulated bit vector.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	struct bit_vector* (*unmark_bit) (struct bit_vector* vector, unsigned int pos);

	/**
	 * @brief	Function pointer to a function that checks if the bit at position <code>pos</code>
	 * 			is marked inside the bit vector <code>vector</code>.
	 * @param	vector	A bit vector that is to be checked.
	 * @param	pos		Position of the bit whose state is to be checked.
	 * @return			<code>1</code> if the bit is set, <code>0</code> otherwise.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	int (*is_bit_marked) (const struct bit_vector* vector, unsigned int pos);

	/**
	 * @brief	Function pointer to a function that counts the number of set bits inside
	 * 			a vector inside the interval start -> end.
	 * @param	vector	The vector whose set bits is to be counted.
	 * @param	start	The index inside the vector from which the count should start.
	 * @param	end		The index inside the vector where the count should end.
	 * @return			The number of set bits between start and end, or 0 if start > end
	 * 					or <code>vector</code> is uninitialized.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	unsigned int (*rank) (const struct bit_vector* vector, unsigned int start, unsigned int end);

	/**
	 * @brief	Function pointer to a function that returns the number of bits used
	 * 			by the bit vector supplied as parameter.
	 * @param	vector	The vector for which a length should be determined.
	 * @return			The number of bits used by the vector supplied as parameter.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	unsigned int (*get_length) (const struct bit_vector* vector);
} bit_vector;

/**
 * @brief	A simple struct for storing a node of a wavelet tree.
 *
 * This struct stores all the necessary data of a node inside a
 * wavelet tree, including the bit vector, the alphabet used and
 * locations of its children (if any).
 *
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct wavelet_node {
	char* string;
	bit_vector vector;
	char* alphabet;
	unsigned int alphabet_length;
	unsigned int children[2];
} wavelet_node;

/**
 * @brief	A struct for storing a wavelet tree.
 *
 * This structure stores all the nodes of a wavelet tree, as well
 * as function pointers to operations possible on the tree. Such
 * operations include length of the root node, rank and char at.
 *
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct wavelet_tree {
	/**
	 * @brief	Returns the number of bits used by the bit vector of the root node
	 * 			(= length of the string from which the tree was created).
	 * @param	tree	The tree for which the length should be determined.
	 * @return			Returns the length of the original string.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	unsigned int (*get_num_bits) (const struct wavelet_tree* tree);

	/**
	 * @brief	Returns the length of the alphabet used by the root node.
	 * @param	tree	The tree for which the alphabet length should be determined.
	 * @return			The length of the alphabet.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	unsigned int (*get_alphabet_length) (const struct wavelet_tree* tree);

	/**
	 * @brief	Returns the alphabet used by the root node.
	 * @param	tree	The tree whose alphabet is to be returned.
	 * @return			The alphabet used by the root node of the tree.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	char* (*get_alphabet) (const struct wavelet_tree* tree);

	/**
	 * @brief	Counts the number of occurrences of a character inside an
	 * 			interval of the string used to create the tree.
	 * @param	tree	The tree for which the count should be done.
	 * @param	c		The character to be counted.
	 * @param	start	The starting index of the count.
	 * @param	end		The ending index of the count.
	 * @return			The number of occurrences of character <code>c</code>
	 * 					between indices start and end inside the wavelet tree.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	int (*rank) (const struct wavelet_tree* tree, char c, int start, int end);

	/**
	 * @brief	Returns the character at index <code>index</code> inside the
	 * 			original string.
	 * @param	tree	The wavelet tree for which the character should be
	 * 					determined.
	 * @param	index	The index of the character to be determined.
	 * @return			The character at index <code>index</code> inside
	 * 					the tree, or <code>NULL</code> if index > length of
	 * 					string or index < 0.
	 * @author	Max Sandberg (REXiator)
	 * @bug		No known bugs.
	 */
	char (*char_at) (const struct wavelet_tree* tree, int index);

	unsigned int num_nodes;
	wavelet_node* nodes;
} wavelet_tree;

/**
 * @brief	A structure for storing the internal state of an iterator.
 * @author	Max Sandberg (REXiator)
 */
typedef struct iterator_state {
	/**
	 * @brief	The number of strings that the iterator is iterating over.
	 */
	unsigned int num_strings;
	/**
	 * @brief	The current extension character in the iteration process.
	 */
	char current_extension;
	/**
	 * @brief	All BWT's used by this iterator.
	 */
	wavelet_tree* bwts;
	/**
	 * @brief	All BWT's of the reversed strings used by this iterator.
	 */
	wavelet_tree* reverse_bwts;
	/**
	 * @brief	All runs vectors used by this iterator.
	 */
	bit_vector* runs_vectors;
	/**
	 * @brief	All runs vectors of the reverse strings used by this iterator.
	 */
	bit_vector* reverse_runs_vectors;
	/**
	 * @brief	All substring stacks used by this iterator.
	 */
	substring_stack* stacks;
	/**
	 * @brief	Current alphabets over intervals inside the BWT's.
	 */
	alphabet_data* alpha_datas;
	/**
	 * @brief	The common alphabet shared by all strings. <code>NULL</code> if
	 * 			only one string.
	 */
	alphabet_data* common_alphabet;
	/**
	 * @brief	All the intervals on the BWT's that are used in this iteration by the
	 * 			iterator.
	 */
	interval* normals;
	/**
	 * @brief	All the intervals on the reverse BWT's that are used in this iteration
	 * 			by the iterator.
	 */
	interval* reverses;
	/**
	 * @brief	All the substrings that have been found in this iteration step.
	 */
	substring* current;
	/**
	 * @brief	All the substrings that have been found in the previous iteration step.
	 */
	substring* prev;
	/**
	 * @brief	All the c-arrays used by the iterator in this iteration.
	 */
	unsigned int** c_arrays;
	/**
	 * @brief	Length of the shortest string the callback function will process
	 */
	int threshold;
} iterator_state;

/**
 * @brief	A struct for storing the parameters given to iterate.
 * @author	Max Sandberg (REXiator)
 */
typedef struct parameter_struct {
	iterate_t iterate_type;
	void (*callback) (iterator_state* state, void* results);
	void* ret_data;
	char** strings;
	int threshold;
} parameter_struct;

/**
 * @brief	A structure for storing the results of an iteration when finding
 * 			maximal unique matches.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct mum_results {
	triplet* data;
	unsigned int length;
	unsigned int allocated_length;
} mum_results;

/**
 * @brief	A structure for storing the results of an iteration when finding
 * 			maximal exact matches.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct mem_results {
	triplet* data;
	unsigned int length;
	unsigned int allocated_length;
	void* params;
} mem_results;

/**
 * @brief	A simple struct for storing data on a maximal repeat substring.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct max_repeat_node
{
	interval normal;
	int length;
} max_repeat_node;

/**
 * @brief	A struct for storing the results of the callback function given
 * 			to iterate.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
typedef struct max_repeat_results {
	max_repeat_node* data;
	unsigned int length;
	unsigned int allocated_length;
} max_repeat_results;

/**
 * @brief A struct for mapping the bwt positions to original positions.
 * @author Paula Lehtola
*/
typedef struct mapped_pair {
	unsigned int bwt_pos;
	unsigned int orig_pos;
} mapped_pair;

/**
 * @brief A struct for listing all occurrences of maximal repeats.
 * @author Paula Lehtola, Lassi Vapaakallio
*/

typedef struct max_repeat_with_indexes {
	unsigned int* indexes;
	unsigned int length;
	unsigned int interval_size;
} max_repeat_with_indexes;

/**
 * @brief	Maps the BWT indexes to indexes in the original string in all found maximal repeats.
 *
 * Updates the normal.i value to index in the original string.
 *
 * @param	nodes			An array of all maximal repeat substrings inside the BWT.
 * @param	bwt				The BWT of the original string, in wavelet tree form.
 * @param	nodes_length	Length of the nodes-array.
 * @param	bit_vec			Bit vector which tells where the maximals repeats start
 * @return					A list of maximal repeats with all occurrences
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator), Paula Lehtola
 * @bug		No known bugs.
 */
max_repeat_with_indexes* map_maximal_repeats_to_string(struct max_repeat_node* nodes, struct wavelet_tree* bwt, int nodes_length, struct bit_vector* bit_vec);

/**
 * @brief	Maps the BWT indexes to indexes in the original string in all found MUMs.
 *
 * Updates the position values in both strings to indexes in the original string.
 *
 * @param	nodes			An array of all triplets returned after iteration.
 * @param	bwt1			BWT of the first string.
 * @param	bwt2			BWT of the second string.
 * @param	nodes_length	Length of the array of nodes.
 * @param 	vecs			Bit vector containing the starting position of MUMs in both strings
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void map_mum_triplets_to_string(struct triplet* nodes,
		struct wavelet_tree* bwt1, struct wavelet_tree* bwt2, int nodes_length, struct bit_vector** vecs);

/**
 * @brief	Maps the BWT indexes to indexes in the original string in all found MEMs.
 *
 * Updates the position values in both strings to indexes in the original string.
 *
 * @param	nodes			An array of all triplets returned after iteration.
 * @param	bwt1			BWT of the first string.
 * @param	bwt2			BWT of the second string.
 * @param	nodes_length	Length of the array of nodes.
 * @param 	vecs			Bit vector containing the starting position of MEMs in both strings
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void map_mem_triplets_to_string(struct triplet* nodes,
		struct wavelet_tree* bwt1, struct wavelet_tree* bwt2, int nodes_length, struct bit_vector** vecs);

/**
 * @brief	An initialization function that creates a parameter struct that
 * 			instructs iterate to search for maximal repeats.
 * @param	string	The string that should be iterated over.
 * @return			An initialized parameter struct ready to be passed to
 * 					iterate.
 * @see		iterate.h#parameter_struct
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
parameter_struct* initialize_for_max_repeats(char* string, int threshold);

/**
 * @brief	The function given as callback to iterate for finding maximal repeats.
 *
 * Determines if a node is a maximal repeat and adds it to a list.
 *
 * @param 	state		The internal state of the iterator.
 * @param	results		A pointer to a region of memory where previous results for
 * 						this function can be found. Can safely be cast to <code>max_repeat_results</code>
 * 						if iterate was initialized using <code>initialize_for_max_repeats()</code>.
 * @see		#initialize_for_max_repeats
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void search_maximal_repeats(iterator_state* state, void* results);

/**
 * @brief	Prints the substring the interval represents.
 *
 * First uses the mapper-function <code>map_maximal_repeats_to_string()</code> and then prints
 * the substring based on the mapped index to stdout.
 *
 * @param	string		The original c-string.
 * @param	results		Results of iterating over the c-string to find maximal repeats.
 * @param	state		The internal state of the iterator performing the search.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_maximal_repeat_substrings(char* string, max_repeat_results* results, iterator_state* state);

/**
 * @brief	Creates a bit vectors based on the given string, where marked bits
 * 			correspond to starting indexes of maximal repeats inside the string.
 *
 * @param	results		The results of an iteration over a set of strings.
 * @param	state		Internal state of the iterator that performed the search.
 * @return 				Bit vectors with starts of Maximal repeats marked.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
bit_vector* max_repeat_make_bit_vector(max_repeat_results* results, iterator_state* state);

/**
 * @brief	An initialization function that creates a parameter struct that
 * 			instructs iterate to search for maximal exact matches.
 * @param	strings		An array of pointers to strings that are to be
 * 						iterated over.
 * @param	max_number_mems
 * 						Number of slots of memory allocated for triplets. This number has
 * 						to be at least as large as expected number of MEMs.
 * @return				An initialized parameter struct ready to be passed
 * 						to iterate.
 * @author	Max Sandberg (REXiator), Topi Paavilainen
 * @bug		No known bugs.
 */
parameter_struct* initialize_for_mems(char** strings, int max_number_mems);

/**
 * @brief	Callback function given to double_iterate that determines if a substring is a MEM (Maximal Exact Match)
 * @param	state		The internal state of the iterator.
 * @param	results		A pointer to a region of memory containing the previous results of
 * 						this callback function. Can safely be cast to <code>mem_results</code>
 * 						if iterate was initialized using <code>initialize_for_mems()</code>.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void search_mems(iterator_state* state, void* results);

/**
 * @brief	Prints the indexes of the MEM in both strings, as well as the substring itself,
 * 			to stdout.
 * @param	string		The string that is to be searched inside the MEM.
 * @param	results		Results of the iteration over a set of strings.
 * @param	state		The internal state of the iterator that performed the search.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_mems(char* string, mem_results* results, iterator_state* state);

/**
 * @brief	Creates a list of two bit vectors based on the given strings, where marked bits
 * 			correspond to starting indexes of MEM's inside the strings.
 *
 * @param	results		The results of an iteration over a set of strings.
 * @param	state		Internal state of the iterator that performed the search.
 * @return 				Bit vectors with starts of MEMs marked.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
bit_vector** mem_make_bit_vectors(mem_results* results, iterator_state* state);

/**
 * @brief	An initialization function that creates a parameter struct that
 * 			instructs iterate to search for maximal unique matches.
 * @param	strings		An array of pointers to strings that are to be
 * 						iterated over.
 * @param	max_number_mums
 * 						number of slots of memory allocated for triplets. This number has
 * 						to be at least as large as expected number of MUMs.
 * @return				An initialized parameter struct ready to be passed
 * 						to iterate.
 * @author	Max Sandberg (REXiator), Topi Paavilainen
 * @bug		No known bugs.
 */
parameter_struct* initialize_for_mums(char** strings, int threshold);

/**
 * @brief	Callback function given to double_iterate that determines if a substring is a MUM.
 * @param	state		The internal state of the iterator.
 * @param	results		A pointer to a region of memory containing the previous results of
 * 						this callback function. Can safely be cast to <code>mum_results</code>
 * 						if iterate was initialized using <code>initialize_for_mums()</code>.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		Doesn't differentiate between the $-characters.
 */
void search_mums(iterator_state* state, void* results);

/**
 * @brief	Prints the indexes of the MUM in both strings, as well as the substring itself,
 * 			to stdout.
 * @param	string		The string that is to be searched inside the MUM.
 * @param	results		Results of the iteration over a set of strings.
 * @param	state		The internal state of the iterator that performed the search.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_mums(char* string, mum_results* results, iterator_state* state);

/**
 * @brief	Prints the bit vectors of the strings which show where MUMs occur to stdout.
 *
 * Every time a MUM is found, the BWT index of the MUM is marked on both strings' bit vectors.
 *
 * @param	string1		The first string for which a bit vector is to be printed.
 * @param	string2		The first string for which a bit vector is to be printed.
 * @param	results		The results of the iteration over the two strings.
 * @param	state		Internal state of the iterator that performed the search.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void mum_print_bit_vectors(char* string1, char* string2, mum_results* results, iterator_state* state);

/**
 * @brief	Creates a list of two bit vectors based on the given strings, where marked bits
 * 			correspond to starting indexes of MUM's inside the strings.
 *
 * @param	results		The results of an iteration over a set of strings.
 * @param	state		Internal state of the iterator that performed the search.
 * @return 				Bit vectors with starts of MUMs marked.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
bit_vector** mum_make_bit_vectors(mum_results* results, iterator_state* state);

/**
 * @brief	Initializes the iterator's internal state.
 * @param	strings		A list of pointers to strings that are to be iterated over.
 * @param	num_strings	The number of strings inside the list.
 * @return				An initialized <code>iterator_state</code>-pointer.
 * @see		#iterator_state
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
iterator_state* initialize_iterator(char** strings, unsigned int num_strings);

/**
 * @brief	Frees an <code>iterator_state</code>-structure and all it's resources.
 * @param	state	The structure to be freed.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_iterator_state(iterator_state* state);

/**
 * @brief	Frees a <code>parameter_struct</code>-structure and all it's resources,
 * 			except for the return data.
 * @param	params	The structure to be freed.
 * @author	Max Sandberg (REXiator)
 * @bug		Throws errors if strings have not been allocated on the heap.
 */
void free_parameter_struct(parameter_struct* params);

/**
 * @brief	The main iteration function.
 *
 * Determines what kind of iterate-function to call based on the parameters sent
 * to it. Should always be initialized using one of the initialization-functions
 * found in any of the files in the <code>applications</code>-folder.
 *
 * @param	parameters	The parameters used to determine what kind of iteration
 * 						to perform.
 * @return				The internal state of the iterator after the iteration
 * 						is done.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
iterator_state* iterate(parameter_struct* parameters);

/**
 * @brief 	A function for iterating through right maximal substrings of a string.
 *
 * Creates a BWT of a string and iterates through substrings of it. If the substring is right
 * maximal, the callback function given as parameter will be called on the substring.
 *
 * @param 	state 		The internal variables used by the iteration function.
 * @param 	callback 	Function pointer to a callback function that is to be called on each
 * 						right maximal substring.
 * @param	result		A pointer to a region of memory where the callback-function can
 * 						store its results.
 * @return				Returns a pointer to the results of the iteration process.
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void* single_iterate(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result);

/**
 * @brief	A function for simultaneously iterating over two strings.
 * @param	state		The internal variables used by the iteration function.
 * @param	callback	The callback function to be called whenever matching substrings
 * 						inside both strings are found to be right maximal.
 * @param	result		A pointer to a region of memory where the callback-function can
 * 						store its results.
 * @return				Returns a pointer to the results of the iteration process.
 * @see		#iterate
 * @author	Lassi Vapaakallio, Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void* double_iterate(iterator_state* state, void (*callback)(iterator_state* state, void* results),
		void* result);

/**
 * @brief	Initializes the bit vector given as a parameter to a size of nbits.
 *
 * Initializes the bit vector given as a parameter to a size of nbits. Returns
 * NULL if the vector given is NULL, nbits is 0 or the necessary space can't
 * be successfully allocated.
 *
 * @param	vector		The vector that is to be initialized.
 * @param	nbits		The amount of bits that should be allocated to the vector.
 * @return	The initialized vector, or NULL if any error occurred.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
bit_vector* init_bit_vector(bit_vector* vector, unsigned int nbits);

/**
 * @brief	Frees the bit vector and all its internal variables.
 * @param	vector		The vector that is to be destroyed.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_bit_vector(bit_vector* vector);

/**
 * @brief	Prints all the information about a substring in a readable form
 * 			to stdout.
 * @param 	state 		Internal state of the iterator where the current node is pulled from
 * @param 	results		Not used, just there to conform to callback
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_node(iterator_state* state, void* results);

/**
 * @brief	Simple swap-function.
 *
 * Swaps the position of two entries in an array.
 *
 * @param	arr			Pointer to the array is to be manipulated.
 * @param	entry_size	Size of the entries that are to be swapped.
 * @param	i			Index of the first entry.
 * @param	j			Index of the second entry.
 * @see		utils.h#quick_sort
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void swap(void* arr, unsigned int entry_size, int i, int j, void* swap_area);

/**
 * @brief	Standard generic quicksort-implementation.
 *
 * This is a standard quicksort-algorithm that can be used for any data-type.
 * It sorts the contents of an array in ascending order.
 *
 * @param	arr			Pointer to the array to be sorted.
 * @param	arr_size	Size of the array to be sorted.
 * @param	entry_size	Size of the individual entries in the array.
 * @return				Returns the sorted array.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void quick_sort(void* arr, unsigned int arr_size, unsigned int entry_size);

/**
 * @brief	Quicksort for an array of strings
 * @param	strings 	An array of pointers to strings.
 * @param	arr_size	Size of the array to be sorted.
 * @see		utils.h#quick_sort
 * @author	Paula Lehtola, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void string_quick_sort(char **strings, unsigned int arr_size);

/**
 * @brief	Determines the alphabet used by a string.
 *
 * Determines the alphabet used by a string. The alphabet of a string is
 * defined as the characters used in the string, including all special
 * characters.
 *
 * @param	string	The string from which the alphabet should be deduced.
 * @return			The alphabet used by the string.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char* determine_alphabet(const char* string);

/**
 * @brief	A generic implementation of a standard binary search-algorithm.
 * @param	arr			A pointer to an array of any type upon which the
 * 						search is to be done.
 * @param	key			A pointer to a value that is to be found inside the
 * 						array.
 * @param	entry_size	The size of the type of the key.
 * @param	max			The maximum index that is to be searched.
 * @param	min			The minimum index that is to be searched.
 * @return				Returns the index of the key inside the array, or -1
 * 						if the array doesn't contain the key.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
int binary_search(const void* arr, const void* key, unsigned int entry_size,
		int max, int min);

/**
 * @brief	Prints the bits of an unsigned integer to stdout.
 * @param	mask	The unsigned integer whose bits are to be printed.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_bits(unsigned int mask);

/**
 * @brief	A simple function that prints a bit vector and its contents to
 * 			stdout.
 * @param	vector	The bit vector that is to be printed.
 * @see		bit_vector.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_bit_vector(bit_vector* vector);

/**
 * @brief	A simple function that prints a node in a wavelet tree to stdout.
 * @param	node	The node that is to be printed.
 * @see		wavelet_tree.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_wavelet_node(wavelet_node* node);

/**
 * @brief	Prints an entire wavelet tree to stdout.
 *
 * Prints the contents of an entire wavelet tree, printing one level
 * of depth at a time.
 *
 * @param	tree	The wavelet tree to be printed.
 * @see		wavelet_tree.h
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void print_wavelet_tree(wavelet_tree* tree);

/**
 * @brief	Returns a substring of a string starting at <code>position</code> with length
 * 			<code>length</code>.
 * @param	string		The whole string.
 * @param	position	Starting position of the substring.
 * @param	length		Length of the substring.
 * @return				A substring of the string supplied as parameter.
 * @author	Lassi Vapaakallio, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
char* substring_from_string(char* string, int position, int length);

/**
 * @brief 	Creates a runs-vector from given string.
 *
 * A runs-vector is a bit vector where marked bits correspond to the character
 * at the same location in the string being equal to its' preceding character.
 *
 * @param 	string 	The string from which the vector should be created,
 * 					represented as a wavelet tree.
 * @param	target	A bit vector where the results should be stored. If <code>NULL</code>,
 * 					a new bit vector will be created and returned.
 * @return 			<code>target</code>, or a pointer to a newly allocated bit vector.
 * @author 	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug 		No known bugs.
 */
bit_vector* create_runs_vector(const wavelet_tree* string, bit_vector* target);

/**
 * @brief Creates a substring struct from interval and length.
 * @param interval in normal BWT
 * @param interval in the BWT of the reverse of the string
 * @param length of substring
 *
 * @return pointer to a new substring struct
 */
substring* create_substring(interval* normal, interval* reverse, int length, substring* target);

/**
 * Updates the interval in the BWT of the reverse of the string
 * @param inter 			interval of the mother node
 * @param normal 			updated BWT interval in this node
 * @param alphabet			alphabet of the interval
 * @param alphabet_length 	length of the alphabet in the interval
 * @param c_array 			C array of the interval
 * @param c 				extension character
 * @param target			A interval where the results should be stored. If <code>NULL</code>, a new interval will be created and returned.
 * @return a new updated Interval struct in the BWT of the reverse of the string
 */
interval* update_reverse_interval(interval* inter, interval* normal,
		const char* alphabet, unsigned int alphabet_length, const int* c_array,
		const char c, interval* target);

/**
 * @brief	An algorithm that creates a wavelet tree from a string.
 *
 * This algorithm recursively creates a wavelet tree from the string
 * supplied as parameter.
 *
 * @param	string	The string of characters from which a wavelet
 * 					tree is to be constructed.
 * @return			A structure containing the wavelet tree, or
 * 					NULL if the string is uninitialized.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
wavelet_tree* create_wavelet_tree(const char* string);

/**
 * @brief	A function for freeing the internal variables used by a
 * 			wavelet tree without freeing the tree itself.
 * @param	tree	The tree whose internals should be freed.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_wavelet_tree_internals(wavelet_tree* tree);

/**
 * @brief	Frees the memory used by an entire wavelet tree.
 *
 * This algorithm frees an entire wavelet tree. It also frees
 * the alphabet used by the wavelet tree, but leaves the
 * original string from which the tree was created intact.
 *
 * @param	tree	The wavelet tree to be freed.
 * @author	Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_wavelet_tree(wavelet_tree* tree);

/**
 * @brief 	Creates an empty stack with given initial size.
 * @param 	initial_size 	Initial stack size.
 * @return 					Pointer to the new empty stack.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
substring_stack* create_stack(int initial_size);

/**
 * @brief 	Pushes given element onto given stack.
 * @param 	stack 	The stack onto which the substring should be pushed.
 * @param 	substr	The substring to be pushed onto the stack.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void push(substring_stack* stack, substring* substr);

/**
 * @brief 	Pops and removes the top-most element from a stack.
 * @param 	stack	The stack from which the top-most element is to be popped.
 * @return 			A pointer to the popped substring.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
substring* pop(substring_stack* stack);

/**
 * @brief	Frees an entire stack structure and all data connected to it.
 * @param	stack	The stack to be freed.
 * @author	Topi Paavilainen, Max Sandberg (REXiator)
 * @bug		No known bugs.
 */
void free_stack(substring_stack* stack);

#endif /* BW4SA_H_ */
