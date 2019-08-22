# I *totally* didn't just copy this 10 line makefile from some random site because I was too lazy to learn makefile

CC=gcc
CFLAGS=
DEPS=cubestate.h algorithm.h solver.h scrambler.h
OBJ=main.o cubestate.o algorithm.o solver.o scrambler.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ivycube: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)