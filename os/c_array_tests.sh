gcc -std=c99 -o src/backward-search/c_array.o src/backward-search/c_array.c tests/backward-search/check_c_array.c src/utils.c src/array/bit_vector.c src/wavelet_tree/wavelet_tree.c `pkg-config --cflags --libs check` -lm

src/backward-search/c_array.o
