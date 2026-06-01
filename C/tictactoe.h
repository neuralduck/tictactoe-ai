#ifndef TICTACTOE_H
#define TICTACTOE_H

typedef enum {
    STATUS_X           = 1,
    STATUS_O           = 0,
    STATUS_DRAW        = 2,
    STATUS_IN_PROGRESS = 3,
} Status;

typedef struct {
    int playerX;
    int playerO;
    //Status status;
} State;

void printBoard(const State *state);
int makeMove(State *state, int player, int move);
Status check(const State *state);
int available_moves(const State *state);
void clearScreen();

#endif