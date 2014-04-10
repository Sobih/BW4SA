#!/bin/bash

gcc -std=c99 -o src/applications/triplet_sorter_test.o -I libs/DBWT libs/DBWT/*.c src/utils/*.c  src/core/*.c src/applications/*.c tests/iterate/check_triplet_sorter.c `pkg-config --cflags --libs check` -lm

./src/applications/triplet_sorter_test.o
