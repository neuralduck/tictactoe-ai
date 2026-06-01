#ifndef MINIMAX_H
#define MINIMAX_H

#include "tictactoe.h"

#define INF 2

typedef struct {
    int choice;
    int score;
} MinimaxResult;

MinimaxResult minimax(const State *state, int player, int alpha, int beta);

#endif