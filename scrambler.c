#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "cubestate.h"
#include "algorithm.h"
#include "solver.h"
#include "scrambler.h"

void getRandomCubeState (struct CubeState *state) {
	srand(time(NULL));
	
	state->UFL.data.rotation = rand() % 3;
	state->UBR.data.rotation = rand() % 3;
	state->DFR.data.rotation = rand() % 3;
	state->DBL.data.rotation = rand() % 3;
	
	int centers[] = {0, 1, 2, 3, 4, 5};
	
	for (int i = 0; i < 5; i ++) {
		int j = i + (rand() % (6 - i));
		
		int tmp = centers[i];
		centers[i] = centers[j];
		centers[j] = tmp;
	}
	
	int cycleHead = 0;
	int curElement = 0;
	int cycleLength = 0;
	int evenCycles = 0;
	bool searched[] = {true, false, false, false, false, false};
	
	while (cycleHead < 6) {
		curElement = centers[curElement];
		cycleLength ++;
		
		searched[curElement] = true;
		
		if (curElement == cycleHead) {
			cycleHead = 6;
			
			for (int i = 0; i < 6; i ++) {
				if (!searched[i]) {
					cycleHead = i;
					break;
				}
			}
			
			curElement = cycleHead;
			
			if (cycleLength % 2 == 0) {
				evenCycles ++;
			}
			
			cycleLength = 0;
		}
	}
	
	if (evenCycles % 2) {
		int tmp = centers[0];
		centers[0] = centers[1];
		centers[1] = tmp;
	}
	
	state->U.data.color = centers[0];
	state->F.data.color = centers[1];
	state->R.data.color = centers[2];
	state->B.data.color = centers[3];
	state->L.data.color = centers[4];
	state->D.data.color = centers[5];
}

void getScramble (struct Algorithm *scramble) {
	struct CubeState state;
	
	initCubeState(&state);
	getRandomCubeState(&state);
	
	bruteForceSolve(state, scramble, false);
}
