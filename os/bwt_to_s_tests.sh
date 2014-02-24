#!/bin/bash

gcc -std=c99 -o src/bwt/bwt_to_s.o tests/bwt/check_bwt_to_s.c src/bwt/*.c libs/DBWT/*.c -I libs/DBWT src/backward-search/*.c src/utils.c  `pkg-config --cflags --libs check`

./src/bwt/bwt_to_s.o
