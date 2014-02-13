

/**
 * @brief Generates array C of given string. This is still a rather slow version of algorithm, but
 * with small alphabets this should not be a problem.
 * 
 * @param string from the C-array will be generated
 *
 * @return array C which contains starting indexes of each distinct character. 
 *
 * @author Topi Paavilainen
 *
 * @bug no known bugs
 */
int* create_c_array(const char* string);

/**
 * @brief Generates alphabet of given string. Alphabet is a string with all characters from the string ordered alphabetically
 * 
 * @param string which the alphabet will be generated from
 *
 * @return alphabet of all characters from given string
 *
 * @author Topi Paavilainen
 *
 * @bug no known bugs
 */
char* get_alphabet(const char* string);

/**
 * @brief Generates c-array from interval of a given string determined by given interval struct
 * 
 * @param interval 
 *
 * @param string which the c_array will be generated from
 *
 * @return c_array of given interval
 *
 * @author Topi Paavilainen
 *
 * @bug no known bugs
 */
int* create_c_array_interval(const Interval* interval, char* bwt);

/**
 * @brief Generates the alphabet of given string in the substring determined by interval struct
 * 
 * @param interval 
 *
 * @param string which the alphabet will be generated from
 *
 * @return alphabet of given interval
 *
 * @author Topi Paavilainen
 *
 * @bug no known bugs
 */
char* create_alphabet_interval(const Interval* interval, char* bwt);


