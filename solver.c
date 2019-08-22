#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cubestate.h"
#include "algorithm.h"
#include "solver.h"

// iterative deepening
void bruteForceSolve (struct CubeState state, struct Algorithm *alg, bool print) {
	if (alg == NULL) {
		fprintf(stderr, "bruteForceSolve got null alg pointer\n");
		exit(1);
	}
	
	initAlgorithm(alg);
	
	if (isCubeStateSolved(&state)) {
		if (print) {
			printf("Cube already solved.\n");
		}
		
		return;
	}
	
	struct Node head;
	
	initAlgorithm(&head.alg);
	head.state = state;
	
	bool complete = false;
	int depth = 1;
	
	while (!complete) {
		traverse(head, alg, &complete, 0, depth);
		
		if (print && !complete) {
			printf("Found no %d move solutions.\n", depth);
		}
		
		depth ++;
	}
}

void traverse (struct Node node, struct Algorithm *alg, bool *solvedOnce, int depth, int maxDepth) {
	if (depth > maxDepth) {
		return;
	}
	
	if (isCubeStateSolved(&node.state) && (!*solvedOnce || node.alg.numMoves < alg->numMoves)) {
		*alg = node.alg;
		*solvedOnce = true;
		return;
	}
	
	for (int i = 0; i < 8; i ++) {
		struct Node child;
		
		memcpy(&child, &node, sizeof(struct Node));
		
		addMoveToAlgorithm(allMoves[i], &child.alg);
		performMove(allMoves[i], &child.state);
		
		traverse(child, alg, solvedOnce, depth + 1, maxDepth);
	}
	
	return;
}
