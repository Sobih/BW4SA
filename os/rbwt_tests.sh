#!/bin/bash

gcc -std=c99 -o src/core/rbwt.o src/core/rbwt.c src/core/s_to_bwt.c -I src/bwt -I libs/DBWT/ libs/DBWT/*.c tests/core/check_rbwt.c src/utils/wavelet_tree.c src/utils/bit_vector.c src/utils/utils.c `pkg-config --cflags --libs check` -lm


./src/core/rbwt.o
