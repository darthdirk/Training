
CC=-gcc
CFLAGS=-g -Wall
BINS=librarytest libshuffle.so main

all: $(BINS)

libshuffle.o: libshuffle.c libshuffle.h
	$(CC) $(CFLAGS) -c libshuffle.c

libshuffle.so: libshuffle.c libshuffle.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ libshuffle.c -lc

librarytest: libshuffle.c libshuffle.o
	$(CC) $(CFLAGS) -o $@ $^

main: main.c
	$(CC) $(CFLAGS) -o $@ $^ -L. -libshuffle

clean:
	rm *.o $(BINS)