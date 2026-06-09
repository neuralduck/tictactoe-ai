#include <stdio.h>
#include "raylib.h"
#include "tictactoe.h"
#include "minimax.h"

#define SCREEN_SIZE 600
#define CELL_SIZE   (SCREEN_SIZE / 3)

static int human_player = 1;

static unsigned int board2index(Vector2 pos){
    if(pos.x < 0 || pos.x >= SCREEN_SIZE ||
       pos.y < 0 || pos.y >= SCREEN_SIZE){
        return 9; /* invalid */
    }
    int col = (int)pos.x / CELL_SIZE;
    int row = (int)pos.y / CELL_SIZE;
    return (unsigned int)(row * 3 + col);
}

static void drawMarks(const State *state){
    int padding = 20;
    for(int i = 0; i < 9; i++){
        int col = i % 3;
        int row = i / 3;
        int px  = col * CELL_SIZE;
        int py  = row * CELL_SIZE;
        if(state->playerX & (1 << i)){
            DrawLineEx(
                (Vector2){px + padding, py + padding},
                (Vector2){px + CELL_SIZE - padding, py + CELL_SIZE - padding},
                6, BLUE
            );
            DrawLineEx(
                (Vector2){px + CELL_SIZE - padding, py + padding},
                (Vector2){px + padding, py + CELL_SIZE - padding},
                6, BLUE
            );
        }
        else if(state->playerO & (1 << i)){
            int cx = px + CELL_SIZE / 2;
            int cy = py + CELL_SIZE / 2;
            int r  = CELL_SIZE / 2 - padding;
            DrawCircleLinesV((Vector2){cx, cy}, (float)r, RED);
            DrawCircleLinesV((Vector2){cx, cy}, (float)(r - 1), RED);
            DrawCircleLinesV((Vector2){cx, cy}, (float)(r - 2), RED);
        }
    }
}

static void drawGrid(void){
    DrawLine(0, CELL_SIZE, SCREEN_SIZE, CELL_SIZE, BLACK);
    DrawLine(0, CELL_SIZE * 2, SCREEN_SIZE, CELL_SIZE * 2, BLACK);
    DrawLine(CELL_SIZE, 0, CELL_SIZE, SCREEN_SIZE, BLACK);
    DrawLine(CELL_SIZE*2, 0, CELL_SIZE * 2, SCREEN_SIZE, BLACK);
}

static void drawBanner(Status status){
    const char *msg = NULL;
    Color col = BLACK;
    if(status == STATUS_X){
        msg = (human_player == 1) ? "You win!" : "X wins!";
        col = BLUE;
    }
    else if(status == STATUS_O){
        msg = (human_player == 0) ? "You win!" : "O wins!";
        col = RED;
    }
    else if(status == STATUS_DRAW){
        msg = "Draw!";
        col = DARKGRAY;
    }
    if(msg){
        DrawRectangle(100, 230, 400, 60, Fade(RAYWHITE, 0.85f));
        DrawText(msg, 200, 248, 36, col);
    }
}

int main(void){
    State state  = {0, 0};
    int turn   = 1;
    Status status = STATUS_IN_PROGRESS;

    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Tic Tac Toe");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        if(status == STATUS_IN_PROGRESS){
            if(turn == human_player){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    unsigned int move = board2index(GetMousePosition());
                    if(move < 9 && makeMove(&state, human_player, (int)move)){
                        status = check(&state);
                        turn = !turn;
                    }
                }
            }
            else{
                status = check(&state);
                if(status == STATUS_IN_PROGRESS){
                    int ai = (human_player == 1) ? 0 : 1;
                    MinimaxResult r = minimax(&state, ai, -INF, INF);
                    if(r.choice >= 0){
                        makeMove(&state, ai, r.choice);
                        status = check(&state);
                        turn   = !turn;
                    }
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawGrid();
            drawMarks(&state);
            drawBanner(status);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}