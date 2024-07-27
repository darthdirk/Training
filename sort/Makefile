CC=gcc
CFLAGS=-Wall -g
EXE=qsort qsort2

all: $(EXE)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXE) *.dSYM *.o~