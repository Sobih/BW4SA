#!/bin/bash

gcc -std=c99 -o src/applications/mum_test.o -I libs/DBWT libs/DBWT/*.c src/utils/*.c src/core/*.c src/applications/mum.c src/applications/maximal_repeats.c src/applications/mapper.c src/applications/mems.c src/applications/map_bwt_to_s.c tests/applications/check_mum.c  tests/utils_for_tests.c`pkg-config --cflags --libs check` -lm

./src/applications/mum_test.o
