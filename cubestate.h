#ifndef CUBESTATE_H
#define CUBESTATE_H

#include <stdbool.h>

enum PieceType {
	PIECE_TYPE_CORNER,
	PIECE_TYPE_CENTER
};

struct Piece {
	enum PieceType type;
	union {
		short rotation; // Corner rotation
		short color; // Center color (UFRBLD)
	} data;
};

struct CubeState {
	struct Piece UFL;
	struct Piece UBR;
	struct Piece DFR;
	struct Piece DBL;
	struct Piece U;
	struct Piece F;
	struct Piece R;
	struct Piece B;
	struct Piece L;
	struct Piece D;
};

const struct CubeState solvedCubeState;

void initCubeState (struct CubeState *stateptr);

void getCubeStateString (struct CubeState state, char *str);

bool isCubeStateSolved (struct CubeState *state);

#endif
