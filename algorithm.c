#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cubestate.h"
#include "algorithm.h"

const struct Move allMoves[8] = {
	{CORNER_UFL, 1},
	{CORNER_UFL, 2},
	{CORNER_UBR, 1},
	{CORNER_UBR, 2},
	{CORNER_DFR, 1},
	{CORNER_DFR, 2},
	{CORNER_DBL, 1},
	{CORNER_DBL, 2}
};

void initAlgorithm (struct Algorithm *alg) {
	alg->numMoves = 0;
}

void addMoveToAlgorithm (struct Move move, struct Algorithm *alg) {
	alg->moves[alg->numMoves++] = move;
}

void getMoveString (struct Move move, char *str) {
	switch (move.corner) {
		case CORNER_UFL: memcpy(str, "UFL", 3); break;
		case CORNER_UBR: memcpy(str, "UBR", 3); break;
		case CORNER_DFR: memcpy(str, "DFR", 3); break;
		case CORNER_DBL: memcpy(str, "DBL", 3); break;
	}
	
	if (move.rotation == 2) {
		str[3] = '\'';
		str[4] = '\0';
	} else {
		str[3] = '\0';
	}
}

void getAlgorithmString (struct Algorithm alg, char *str) {
	int idx = 0;
	
	for (int i = 0; i < alg.numMoves; i ++) {
		getMoveString(alg.moves[i], &str[idx]);
		idx += alg.moves[i].rotation == 1 ? 3 : 4;
		
		str[idx++] = ' ';
	}
	
	str[idx] = '\0';
}

void parseMoveString (char *movestr, struct Move *dest) {
	if (movestr == NULL) {
		fprintf(stderr, "Could not process null move string\n");
		exit(1);
	}
	
	int corner = 0;
	
	for (int i = 0; i < 3; i ++) {
		if (!movestr[i] || strchr("UFRBLD", movestr[i]) == NULL) {
			fprintf(stderr, "Could not process invalid move string %s\n", movestr);
			exit(1);
		}
		
		corner += movestr[i];
	}
	
	short rotation = 1;
	
	if (movestr[3] == '\'') {
		rotation = 2;
	}
	
	dest->corner = corner;
	dest->rotation = rotation;
}

void parseAlgorithmString (char *algstr, struct Algorithm *dest) {
	if (algstr == NULL) {
		fprintf(stderr, "Could not process null alg string\n");
		exit(1);
	}
	
	initAlgorithm(dest);
	
	if (!algstr[0]) {
		dest->numMoves = 0;
		return;
	}
	
	int curMove = 0;
	char *token = strtok(algstr, " ");
	
	while (token != NULL) {
		parseMoveString(token, &dest->moves[curMove++]);
		token = strtok(NULL, " ");
	}
	
	dest->numMoves = curMove;
}

void performMoveUFL (struct CubeState *state) {
	state->UFL.data.rotation ++;
	state->UFL.data.rotation %= 3;
	
	short temp = state->L.data.color;
	state->L.data.color = state->F.data.color;
	state->F.data.color = state->U.data.color;
	state->U.data.color = temp;
}

void performMoveUBR (struct CubeState *state) {
	state->UBR.data.rotation ++;
	state->UBR.data.rotation %= 3;
	
	short temp = state->R.data.color;
	state->R.data.color = state->B.data.color;
	state->B.data.color = state->U.data.color;
	state->U.data.color = temp;
}

void performMoveDFR (struct CubeState *state) {
	state->DFR.data.rotation ++;
	state->DFR.data.rotation %= 3;
	
	short temp = state->R.data.color;
	state->R.data.color = state->F.data.color;
	state->F.data.color = state->D.data.color;
	state->D.data.color = temp;
}

void performMoveDBL (struct CubeState *state) {
	state->DBL.data.rotation ++;
	state->DBL.data.rotation %= 3;
	
	short temp = state->L.data.color;
	state->L.data.color = state->B.data.color;
	state->B.data.color = state->D.data.color;
	state->D.data.color = temp;
}

void performMove (struct Move move, struct CubeState *state) {
	void (*moveFunc)(struct CubeState*) = NULL;
	
	switch (move.corner) {
		case CORNER_UFL: moveFunc = performMoveUFL; break;
		case CORNER_UBR: moveFunc = performMoveUBR; break;
		case CORNER_DFR: moveFunc = performMoveDFR; break;
		case CORNER_DBL: moveFunc = performMoveDBL; break;
		default:
			fprintf(stderr, "Could not run invalid move: corner was %d\n", move.corner);
			exit(1);
	}
	
	for (int i = 0; i < move.rotation; i ++) {
		moveFunc(state);
	}
}

void performAlgorithm (struct Algorithm alg, struct CubeState *state) {
	for (int i = 0; i < alg.numMoves; i ++) {
		performMove(alg.moves[i], state);
	}
}
