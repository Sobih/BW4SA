gcc -std=c99 -o src/iterate/iterate_test.o src/iterate/iterate.c tests/iterate/check_iterate.c `pkg-config --cflags --libs check`

src/iterate/iterate_test.o
