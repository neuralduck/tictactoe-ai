#include "minimax.h"
#include "tictactoe.h"

MinimaxResult minimax(const State *state, int player, int alpha, int beta){
    Status status = check(state);
    if(status == STATUS_X){
        return (MinimaxResult){-1, 1};
    }
    if(status == STATUS_O){
        return (MinimaxResult){-1, -1};
    }
    if(status == STATUS_DRAW){
        return (MinimaxResult){-1, 0};
    }

    MinimaxResult best = {-1, player == 1 ? -INF : INF};
    int preferred[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

    for(int i = 0; i < 9; i++){
        int choice = preferred[i];
        if(!(available_moves(state)&(1<<choice))){
            continue;
        }
        State next = *state;
        makeMove(&next, player, choice);
        MinimaxResult r = minimax(&next, !player, alpha, beta);
        if(player == 1 && r.score > best.score){
            best = (MinimaxResult){choice, r.score};
            alpha = alpha > best.score ? alpha : best.score;
            if(alpha >= beta){
                break;
            }

        }
        if(player == 0 && r.score < best.score){
            best = (MinimaxResult){choice, r.score};
            beta = beta < best.score ? beta : best.score;
            if(beta <= alpha){
                break;
            }
        }
    }
    return best;
}