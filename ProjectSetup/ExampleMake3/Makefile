CC=gcc
CFLAGS=-g
# wildcard (find all .c files and put into SRC_FILES variable)
SRC_FILES=$(wildcard *.c)
# patsubst (anytime you see .c replace with .o)
OBJ_FILES=$(patsubst %.c,%.o,$(SRC_FILES))

PROGNAME=survey

all: $(PROGNAME)

$(PROGNAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(PROGNAME) $(OBJ_FILES)
