#!/bin/bash

gcc -std=c99 -o src/bwt/s_to_bwt.o src/bwt/s_to_bwt.c tests/bwt/check_s_to_bwt.c libs/DBWT/*.c -I libs/DBWT/ -I src/bwt `pkg-config --cflags --libs check`

./src/bwt/s_to_bwt.o
