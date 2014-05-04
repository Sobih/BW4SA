#!/bin/bash

gcc -std=c99 -o src/applications/triplet_sorter_test.o -I libs/DBWT libs/DBWT/*.c src/utils/*.c  src/core/*.c src/applications/maximal_repeats.c src/applications/mapper.c src/applications/triplet_sorter.c tests/applications/check_triplet_sorter.c `pkg-config --cflags --libs check` -g -lm

./src/applications/triplet_sorter_test.o
