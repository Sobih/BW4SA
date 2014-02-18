/*
 * s_to_bwt.h
 *
 *  Created on: 24.1.2014
 *      Author: lvapaaka
 */

#ifndef S_TO_BWT_H_
#define S_TO_BWT_H_
#ifndef uchar
typedef unsigned char uchar;
#endif

/**
 * Performs Burrows-Wheeler transform on the given string.
 *
 * @param string the string on which the Burrows-Wheeler transform is applied to.
 * @return the BWT of the string
 */
uchar* s_to_BWT(uchar *string);

#endif /* S_TO_BWT_H_ */
