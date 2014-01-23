all: dbwt
dbwt: dbwt.c queue.c queue.h sais.c utils.c utils.h
	gcc -o dbwt dbwt.c queue.c sais.c utils.c -m64 -D_LARGEFILE64_SOURCE=1 -D_FILE_OFFSET_BITS=64 -O9
