#include <stdio.h>
#include "tictactoe.h"

int main(void) {
    State s = {0, 0};
    int choice;
    int player = 1;
    clearScreen();
    printBoard(&s);
    printf("%d\n", check(&s));
    while(1){
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
        for (int i = 0; i < 9; i++) {
            if (moves & (1 << i))
                printf("%d ", i);
        }
        printf("\n");
        do {
            if (player == 1){
                printf("X choice: ");
            }
            else{
                printf("O choice: ");
            }
            scanf("%d", &choice);
        } while (!makeMove(&s, player, choice));

        player = !player;
    }
    return 0;
}