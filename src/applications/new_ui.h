/*
 * new_ui.h
 *
 *  Created on: 2.7.2014
 *      Author: sobih
 */

#ifndef NEW_UI_H_
#define NEW_UI_H_
#include "distinct_substrings.h"
#include "triplet_sorter.h"
#include "../core/s_to_bwt.h"
#include "../core/bwt_to_s.h"
#include "../core/rbwt.h"
#include "../core/c_array.h"
#include "../../include/core.h"
#include "../../include/utils.h"
#include "../../include/applications.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "../utils/count_kmers.h"

void new_ui(int argc, char** argv);
char* readFile(char* fileName);
#endif /* NEW_UI_H_ */
