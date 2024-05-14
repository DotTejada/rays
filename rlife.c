#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#define unimplemented DrawText("Not yet implemented", 200, 150, 40, GREEN);

#define scale 40
#define screenWidth 800
#define screenHeight 600
#define cWidth (screenWidth / scale) // 16
#define cHeight (screenHeight / scale) // 12

bool board[cWidth][cHeight] = {false};
bool copy[cWidth][cHeight] = {false};
bool run = false;

bool cellnext(int col, int row) {
    int count = 0;
    //first row
    if (row == 0) {
        //top left cell
        if (col == 0) {
            if (board[col + 1][row]) {count += 1;}
            if (board[col][row + 1]) {count += 1;}
            if (board[col + 1][row + 1]) {count += 1;}
        //middle cells
        } else if (0 < col && col < cWidth - 1) {
            if (board[col - 1][row]) {count += 1;}
            if (board[col + 1][row]) {count += 1;}
            for (int ix = -1; ix < 2; ix++) {
                if (board[col + ix][row + 1]) {count += 1;}
            }
        //top right cell
        } else {
            if (board[col - 1][row]) {count += 1;}
            if (board[col][row + 1]) {count += 1;}
            if (board[col - 1][row + 1]) {count += 1;}
        }
    //middle rows
    } else if (0 < row && row < cHeight - 1) {
        //left edge cell
        if (col == 0) {
            if (board[col][row - 1]) {count += 1;}
            if (board[col][row + 1]) {count += 1;}
            for (int iy = -1; iy < 2; iy++) {
                if (board[col + 1][row + iy]) {count += 1;}
            }
        //middle cells
        } else if (0 < col && col < cWidth - 1) {
            if (board[col - 1][row]) {count += 1;}
            if (board[col + 1][row]) {count += 1;}
            for (int a = -1; a < 2; a++) {
                if (board[col + a][row + 1]) {count += 1;}
            }
            for (int b = -1; b < 2; b++) {
                if (board[col + b][row - 1]) {count += 1;}
            }
        //right edge cell
        } else {
            if (board[col][row - 1]) {count += 1;}
            if (board[col][row + 1]) {count += 1;}
            for (int iz = -1; iz < 2; iz++) {
                if (board[col - 1][row + iz]) {count += 1;}
            }
        }
    //last row
    } else {
        //bottom left cell
        if (col == 0) {
            if (board[col + 1][row]) {count += 1;}
            if (board[col][row - 1]) {count += 1;}
            if (board[col + 1][row - 1]) {count += 1;}
        //middle cells
        } else if (0 < col && col < cWidth - 1) {
            if (board[col - 1][row]) {count += 1;}
            if (board[col + 1][row]) {count += 1;}
            for (int ix = -1; ix < 2; ix++) {
                if (board[col + ix][row - 1]) {count += 1;}
            }
        //bottom right cell
        } else {
            if (board[col - 1][row]) {count += 1;}
            if (board[col][row - 1]) {count += 1;}
            if (board[col - 1][row - 1]) {count += 1;}
        }
    }

    //if alive already
    if (board[col][row]) {
        if (count < 2) {
            return false;
        } else if (count == 2 || count == 3) {
            return true;
        } else {
            return false;
        }
    //if dead already
    } else { 
        if (count == 3) {
            return true;
        } else {
            return false;
        }
    }
}

int main() {
    InitWindow(screenWidth, screenHeight, "Game of Life");
    Image ball = LoadImage("glider.png");
    SetWindowIcon(ball);

    if (!IsWindowReady()) {
        fprintf(stderr, "The window could not be initialized.");
        return 1;
    }

    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        //Draws grid
        for (int i = 0; i < cWidth; i++) {
            DrawLine(i * scale, 0, i * scale, screenHeight, GRAY);
        }
        for (int i = 0; i < cHeight; i++) {
            DrawLine(0, i * scale, screenWidth, i * scale, GRAY);
        }

        //User input
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int xpos = GetMouseX() / scale;
            int ypos = GetMouseY() / scale;
            board[xpos][ypos] = !board[xpos][ypos];
        }

        if (IsKeyPressed(KEY_SPACE)) { run = !run; }
        if (IsKeyPressed(KEY_S)) {
            FILE *f = fopen("save.gol", "w");
            for (int row = 0; row < cHeight; row++) {
                for (int col = 0; col < cWidth; col++) {
                    fprintf(f, "%d", board[col][row]);
                }
                fprintf(f, "\n");
            }
            fclose(f);
            DrawText("Saved!", 0, 0, 20, GREEN);
        }

        if (!run) {
            //Draws the board statically if not running
            for (int row = 0; row < cHeight; row++) {
                for (int col = 0; col < cWidth; col++) {
                    if (board[col][row]) {
                        DrawRectangle(col * scale + 1, row * scale + 1, scale - 2, scale - 2, WHITE);
                    }
                }
            }
        } else {
            //Updates board each frame
            for (int row = 0; row < cHeight; row++) {
                for (int col = 0; col < cWidth; col++) {
                    copy[col][row] = cellnext(col, row);
                }
            }
            memcpy(board, copy, sizeof(bool) * cWidth * cHeight);
            //Then draws it
            for (int row = 0; row < cHeight; row++) {
                for (int col = 0; col < cWidth; col++) {
                    if (board[col][row]) {
                        DrawRectangle(col * scale + 1, row * scale + 1, scale - 2, scale - 2, WHITE);
                    }
                }
            }
        }
        
        EndDrawing();
    }
    CloseWindow();

    for (int row = 0; row < cHeight; row++) {
        for (int col = 0; col < cWidth; col++) {
            printf("%d", board[col][row]);
        }
        printf("\n");
    }

    return 0;
}
