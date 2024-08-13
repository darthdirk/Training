CC=gcc
CFLAGS=-g
LDFLAGS=-lm


all: quadsolver badcolorizer

quadsolver: example1.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

badcolorizer: example2.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f quadsolver badcolorizer