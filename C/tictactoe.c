#include <stdio.h>
#include "tictactoe.h"

void printBoard(State* state){
    char board[9];
    for(int i = 0; i < 9; i++){
        if(state->playerX & (1<<i)){
            board[i] = 'X';
        }
        else{
            if(state->playerO & (1<<i)){
                board[i] = 'O';
            }
            else{
                board[i] = ' ';
            }
        }
    }
    printf("0|1|2\n3|4|5\n6|7|8\n\n");
    printf("%c|%c|%c\n%c|%c|%c\n%c|%c|%c\n",
        board[0], board[1], board[2],
        board[3], board[4], board[5],
        board[6], board[7], board[8]
    );
}

int makeMove(State *state, int player, int move) {
    if (move < 0 || move > 8) return 0;
    int bit = 1 << move;
    if ((state->playerX | state->playerO) & bit) return 0;  // already occupied
    if (player == 1)
        state->playerX |= bit;
    else
        state->playerO |= bit;
    return 1;
}

int available_moves(State* state){
    return (~(state->playerX | state->playerO)) & 0b111111111;
}

Status check(State* state){
    static const int horizontal = 0b111000000;
    static const int vertical   = 0b100100100;
    static const int diag1      = 0b100010001;
    static const int diag2      = 0b001010100;
    static const int full       = 0b111111111;

    /* Horizontal rows */
    for (int i = 0; i <= 6; i += 3) {
        int mask = horizontal >> i;
        if ((state->playerX & mask) == mask){ 
            return STATUS_X; 
        }
        if ((state->playerO & mask) == mask){ 
            return STATUS_O;
        }
    }
 
    /* Vertical columns */
    for (int i = 0; i <= 2; i++) {
        int mask = vertical >> i;
        if((state->playerX & mask) == mask){ 
            return STATUS_X;
        }
        if((state->playerO & mask) == mask){ 
            return STATUS_O;
        }
    }
 
    /* Diagonals */
    if ((state->playerX & diag1) == diag1 || (state->playerX & diag2) == diag2) {
        return STATUS_X;
    }
    if ((state->playerO & diag1) == diag1 || (state->playerO & diag2) == diag2) {
        return STATUS_O;
    }
 
    /* Draw */
    if (full == (state->playerX | state->playerO)){ 
        return STATUS_DRAW;
    }
 
    return STATUS_IN_PROGRESS;
}


void clearScreen(){
    printf("\033[2J\033[1;1H");
}