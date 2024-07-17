CC=gcc
CFLAGS=-g
OBJ=debug.o survey.o
PROGNAME=survey

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(PROGNAME) $(OBJS)
	