#!/bin/bash

gcc -std=c99 -o src/iterate/rbwt.o src/iterate/rbwt.c src/bwt/s_to_bwt.c -I src/bwt -I libs/DBWT/ libs/DBWT/*.c tests/iterate/check_rbwt.c `pkg-config --cflags --libs check`

./src/iterate/rbwt.o
