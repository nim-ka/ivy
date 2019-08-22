# I *totally* didn't just copy this 10 line makefile from some random site because I was too lazy to learn makefile

CC = gcc

CFLAGS ?=
BUILD_DIR ?= build
EXEC_NAME ?= ivycube

OBJS = main.o cubestate.o algorithm.o solver.o scrambler.o

$(BUILD_DIR)/%.o: %.c
	$(CC) -I. -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/$(EXEC_NAME): $(foreach file,$(OBJS),$(BUILD_DIR)/$(file))
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -r build
