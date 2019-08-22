#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "cubestate.h"

enum Corner {
	CORNER_UFL = 'U' + 'F' + 'L',
	CORNER_UBR = 'U' + 'B' + 'R',
	CORNER_DFR = 'D' + 'F' + 'R',
	CORNER_DBL = 'D' + 'B' + 'L'
};

struct Move {
	enum Corner corner;
	short rotation;
};

struct Algorithm {
	int numMoves;
	struct Move moves[100];
};

const struct Move allMoves[8];

void initAlgorithm (struct Algorithm *alg);
void addMoveToAlgorithm (struct Move move, struct Algorithm *alg);

void getMoveString (struct Move move, char *str);
void getAlgorithmString (struct Algorithm alg, char *str);

void parseMoveString (char *movestr, struct Move *dest);
void parseAlgorithmString (char *algstr, struct Algorithm *dest);

void performMove (struct Move move, struct CubeState *state);
void performAlgorithm (struct Algorithm alg, struct CubeState *state);

#endif
