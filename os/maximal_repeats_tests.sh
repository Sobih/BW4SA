#!/bin/bash

gcc -std=c99 -o src/core/maximal_repeats_test.o -I libs/DBWT libs/DBWT/*.c src/utils/*.c src/core/*.c tests/applications/check_maximal_repeats.c tests/utils_for_tests.c`pkg-config --cflags --libs check` -lm

./src/core/maximal_repeats_test.o
