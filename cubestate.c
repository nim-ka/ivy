#include <stdbool.h>
#include <string.h>

#include "cubestate.h"

const struct CubeState solvedCubeState = {
	{PIECE_TYPE_CORNER, 0}, // UFL
	{PIECE_TYPE_CORNER, 0}, // UBR
	{PIECE_TYPE_CORNER, 0}, // DFR
	{PIECE_TYPE_CORNER, 0}, // DBL
	{PIECE_TYPE_CENTER, 0}, // U
	{PIECE_TYPE_CENTER, 1}, // F
	{PIECE_TYPE_CENTER, 2}, // R
	{PIECE_TYPE_CENTER, 3}, // B
	{PIECE_TYPE_CENTER, 4}, // L
	{PIECE_TYPE_CENTER, 5}  // D
};

const char stickersUFL[] = {0, 1, 4};
const char stickersUBR[] = {0, 3, 2};
const char stickersDFR[] = {5, 1, 2};
const char stickersDBL[] = {5, 3, 4};

void initCubeState (struct CubeState *stateptr) {
	memcpy(stateptr, &solvedCubeState, sizeof(struct CubeState));
}

void getCubeStateString (struct CubeState state, char *str) {
	str[0]  = '0' + stickersUFL[(3 - state.UFL.data.rotation) % 3];
	str[1]  = '0' + state.U.data.color;
	str[2]  = '0' + stickersUBR[(3 - state.UBR.data.rotation) % 3];
	
	str[3]  = ' ';
	
	str[4]  = '0' + stickersUFL[(3 - state.UFL.data.rotation + 1) % 3];
	str[5]  = '0' + state.F.data.color;
	str[6]  = '0' + stickersDFR[(3 - state.DFR.data.rotation + 1) % 3];
	
	str[7]  = ' ';
	
	str[8]  = '0' + stickersDFR[(3 - state.DFR.data.rotation + 2) % 3];
	str[9]  = '0' + state.R.data.color;
	str[10] = '0' + stickersUBR[(3 - state.UBR.data.rotation + 2) % 3];
	
	str[11] = ' ';
	
	str[12] = '0' + stickersUBR[(3 - state.UBR.data.rotation + 1) % 3];
	str[13] = '0' + state.B.data.color;
	str[14] = '0' + stickersDBL[(3 - state.DBL.data.rotation + 1) % 3];
	
	str[15] = ' ';
	
	str[16] = '0' + stickersDBL[(3 - state.DBL.data.rotation + 2) % 3];
	str[17] = '0' + state.L.data.color;
	str[18] = '0' + stickersUFL[(3 - state.UFL.data.rotation + 2) % 3];
	
	str[19] = ' ';
	
	str[20] = '0' + stickersDBL[(3 - state.DBL.data.rotation) % 3];
	str[21] = '0' + state.D.data.color;
	str[22] = '0' + stickersDFR[(3 - state.DFR.data.rotation) % 3];
	
	str[23] = '\0';
}

bool isCubeStateSolved (struct CubeState *state) {
	return memcmp(state, &solvedCubeState, sizeof(struct CubeState)) == 0;
}
