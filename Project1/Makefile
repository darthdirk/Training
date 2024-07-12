# Compiler
CC := gcc

# Compiler flags
CFLAGS := -g -Wextra 

all: survey

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

survey: survey.o

clean:
	rm -f *.o survey