#!/bin/bash

gcc -std=c99 -o src/iterate/iterate_test.o -I libs/DBWT libs/DBWT/*.c src/utils.c src/bwt/*.c src/array/bit_vector.c src/backward-search/*.c  src/iterate/*.c tests/iterate/check_iterate.c `pkg-config --cflags --libs check` -lm

./src/iterate/iterate_test.o

