#ifndef SCRAMBLER_H
#define SCRAMBLER_H

#include "cubestate.h"
#include "algorithm.h"

void getRandomCubeState (struct CubeState *state);
void getScramble (struct Algorithm *scramble);

#endif