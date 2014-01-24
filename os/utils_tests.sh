#!/bin/bash

gcc -std=c99 -o src/utils.o src/utils.c tests/check_utils.c `pkg-config --cflags --libs check`

./src/utils.o