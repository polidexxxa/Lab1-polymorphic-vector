CC = gcc
CFLAGS = -I.

PROG = vector_program
TEST = vector_test

SRCS = types.c errors.c vector.c
OBJS = $(SRCS:.c=.o)

ALL_OBJS = $(OBJS) main.o
TEST_OBJS = $(OBJS) test_vector.o

all: $(PROG) $(TEST)

$(PROG): main.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ main.o $(OBJS)

$(TEST): test_vector.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ test_vector.o $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(PROG)
	./$(PROG)

test: $(TEST)
	./$(TEST)

clean:
	rm -f *.o $(PROG) $(TEST)

main.o: main.c vector.h errors.h
test_vector.o: test_vector.c vector.h errors.h
types.o: types.c types.h
errors.o: errors.c errors.h
vector.o: vector.c vector.h types.h errors.h

.PHONY: all run test clean