#include <stdio.h>
#include "tictactoe.h"
#include "minimax.h"

void pvp() {
    State s = {0, 0};
    int choice;
    int player = 1;
    while (1) {
        clearScreen();
        printBoard(&s);
        Status status = check(&s);
        if (status == STATUS_X){ 
            printf("X wins\n"); 
            break; 
        }
        if (status == STATUS_O){ 
            printf("O wins\n"); 
            break; 
        }
        if (status == STATUS_DRAW){ 
            printf("Draw\n");   
            break; 
        }

        int moves = available_moves(&s);
        printf("available moves: ");
        for(int i = 0; i < 9; i++)
            if(moves & (1 << i)){
                printf("%d ", i);
            }
        printf("\n");

        do {
            printf(player == 1 ? "X choice: " : "O choice: ");
            scanf("%d", &choice);
        } while (!makeMove(&s, player, choice));

        player = !player;
    }
}

void vsMinimax() {
    int option;
    printf("Play as: 1. X  2. O\n> ");
    scanf("%d", &option);
    int human = (option == 1) ? 1 : 0;

    State s = {0, 0};
    int choice;
    int player = 1;
    
    while (1) {
        clearScreen();
        printBoard(&s);
        Status status = check(&s);
        if (status == STATUS_X) {
            printf("X wins\n");
            break;
        }
        if (status == STATUS_O) {
            printf("O wins\n");
            break;
        }
        if (status == STATUS_DRAW) {
            printf("Draw\n");
            break;
        }

        int moves = available_moves(&s);
        printf("available moves: ");
        for (int i = 0; i < 9; i++) {
            if (moves & (1 << i)) {
                printf("%d ", i);
            }
        }
        printf("\n");

        if (player == human) {
            do {
                printf("You: ");
                scanf("%d", &choice);
            } while (!makeMove(&s, player, choice));
        } else {
            choice = minimax(&s, player, -INF, INF).choice;
            printf("Bot plays: %d\n", choice);
            makeMove(&s, player, choice);
        }

        player = !player;
    }
}
int main(void) {
    int option;
    printf("1. PvP  2. vs Minimax\n> ");
    scanf("%d", &option);
    switch (option) {
        case 1:  pvp();        break;
        case 2:  vsMinimax();  break;
        default: printf("invalid option\n"); break;
    }
    return 0;
}