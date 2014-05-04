#!/bin/bash

gcc -std=c99 -o src/utils/print_node.o -I libs/DBWT libs/DBWT/*.c src/utils/*.c src/core/*.c tests/utils/check_print_node.c `pkg-config --cflags --libs check` -g -lm

./src/utils/print_node.o 
