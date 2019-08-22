#ifndef SOLVER_H
#define SOLVER_H

#include <stdbool.h>

#include "cubestate.h"
#include "algorithm.h"

struct Node {
	struct Algorithm alg;
	struct CubeState state;
};

void bruteForceSolve (struct CubeState state, struct Algorithm *alg, bool print);
void traverse (struct Node node, struct Algorithm *alg, bool *solvedOnce, int depth, int maxDepth);

#endif
