#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "cubestate.h"
#include "algorithm.h"
#include "solver.h"
#include "scrambler.h"

struct CubeState state;
struct Algorithm alg;

// Superflip
//char algstr[] = "UFL UBR UFL UBR' UFL' UBR' UFL' UBR' UFL UBR DFR' DBL' DFR' DBL DFR DBL DFR DBL DFR' DBL'";
char algstr[] = "UFL UBR DFR DBL";

int main (int argc, char **argv) {
	char buf[1024];
	
	if (argc > 1 && memcmp(argv[1], "--test", 6) == 0) {
		printf("Initializing cube...\n");
	
		initCubeState(&state);
	
		printf("Done.\n\n");
	
		printf("Performing algorithm %s...\n", algstr);
	
		parseAlgorithmString(algstr, &alg);
		performAlgorithm(alg, &state);
	
		printf("Done. Cube state:\n");
	
		getCubeStateString(state, buf);
		printf("\t%s\n\n", buf);
	
		printf("Solving cube...\n");
	
		bruteForceSolve(state, &alg, true);
	
		getAlgorithmString(alg, buf);
		printf("%s\n", buf);
	
		printf("Done.\n\n");
	}
	
	printf("Getting scramble...\n");
	
	getScramble(&alg);
	
	printf("Done. Scramble:\n");
	
	getAlgorithmString(alg, buf);
	printf("\t%s\n\n", buf);
	
	return 0;
}
