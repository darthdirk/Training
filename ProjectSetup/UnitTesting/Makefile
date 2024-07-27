

CC=-gcc
CFLAGS=-g -Wall -I/usr/include/criterion -I./src
LDFLAGS=-pthread -lcriterion
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TEST=tests
TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

LIBDIR=lib
LIB=$(LIBDIR)/myqueue.a

all:$(LIB)

release: CFLAGS=-Wall -02 -DNDEBUG
release: clean
release: $(LIB)

$(LIB): $(LIBDIR) $(OBJ) $(OBJS)
	$(RM) $(LIB)
	ar -cvrs $(LIB) $(OBJS)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST)/bin/%: $(TEST)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ $(LDFLAGS)

$(TEST)/bin:
	mkdir $@

$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@

test: $(LIB) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

 
clean:
	$(RM) -r $(LIBDIR) $(OBJ)
	$(RM) $(TEST)/bin/*

