CC = gcc
LD = gcc

CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS= -lcriterion

all: brainfuck test_brainfuck_helper

test_brainfuck_helper: brainfuck_helper.o test_brainfuck_helper.o
	$(CC) $^ -o $@ $(LDFLAGS)

brainfuck: brainfuck_helper.o brainfuck_main.o
	$(CC) $(CFLAGS) $^ -o $@

brainfuck_helper.o : brainfuck_helper.c brainfuck_helper.h
	$(CC) $(CFLAGS) -c $< -o $@

test_brainfuck_helper.o : test_brainfuck_helper.c
	$(CC) $(CFLAGS) -c $< -o $@

brainfuck_main.o : brainfuck_main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f brainfuck_helper.o brainfuck_main.o test_brainfuck_helper.o brainfuck test_brainfuck_helper


.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
