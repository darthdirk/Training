# Compiler
CC := gcc

# Compiler flags
CFLAGS := -g -Wextra 

all: memVisual

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

memVisual: memVisual.o

clean:
	rm -f *.o memVisual