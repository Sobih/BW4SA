#!/bin/bash

gcc -std=c99 -o src/iterate/iterate_test.o src/iterate/rbwt.c src/bwt/s_to_bwt.c -I src/bwt -I libs/DBWT/ libs/DBWT/*.c src/array/bit_vector.c src/iterate/iterate.c tests/iterate/check_iterate.c `pkg-config --cflags --libs check` -lm

./src/iterate/iterate_test.o
