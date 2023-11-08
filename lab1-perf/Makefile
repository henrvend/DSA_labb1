.PHONY: clean tidy

CC = gcc
CFLAGS = -Wall -Werror -std=gnu99 -lm
HDR = $(wildcard *.h)
SRC = $(filter-out $(wildcard *_test.c), $(wildcard *.c))
OBJ = $(SRC:.c=.o)

CFLAGS_TEST = $(CFLAGS)
SRC_TEST = $(filter-out main.c, $(wildcard *.c))
OBJ_TEST = $(SRC_TEST:.c=.o)

main: $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS)

test: $(OBJ_TEST)
	$(CC) -o test $(OBJ_TEST) 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf *.o main test

tidy:
	rm -rf *.o
