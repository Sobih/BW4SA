/*
 * map_bwt_to_s.h
 *
 *  Created on: 27.2.2014
 *      Author: lvapaaka
 */

#ifndef MAP_BWT_TO_S_H_
#define MAP_BWT_TO_S_H_

struct wavelet_tree;

int* map_create_suffix_array_from_bwt(const struct wavelet_tree* bwt);

#endif /* MAP_BWT_TO_S_H_ */
