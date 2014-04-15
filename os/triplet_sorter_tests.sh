#!/bin/bash

gcc -std=c99 -o src/iterate/triplet_sorter_test.o -I libs/DBWT libs/DBWT/*.c src/utils.c src/bwt/*.c src/array/bit_vector.c src/backward-search/*.c  src/iterate/*.c tests/iterate/check_triplet_sorter.c `pkg-config --cflags --libs check` -lm

./src/iterate/triplet_sorter_test.o
