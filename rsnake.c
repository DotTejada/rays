#include "raylib.h"
#include "stdio.h"
#include "stdbool.h"

const int scale = 50;
const int screenWidth = 800;
const int screenHeight = 600;
const int cWidth = screenWidth / scale; //16
const int cHeight = screenHeight / scale; //12

bool board[16][12] = {false};

int main() {
    InitWindow(screenWidth, screenHeight, "RSnake");
    Image ball = LoadImage("ballp.png");
    SetWindowIcon(ball);

    if (!IsWindowReady()) {
        fprintf(stderr, "The window could not be initialized.");
        return 1;
    }

    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < cWidth; i++) {
            DrawLine(i * (screenWidth / cWidth), 0, i * (screenWidth / cWidth), screenHeight, GRAY);
        }
        for (int i = 0; i < cHeight; i++) {
            DrawLine(0, i * (screenHeight / cHeight), screenWidth, i * (screenHeight / cHeight), GRAY);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int xpos = GetMouseX() / scale;
            int ypos = GetMouseY() / scale;
            board[xpos][ypos] = !board[xpos][ypos];
        }

        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 16; j++) {
                if (board[j][i]) {
                    DrawRectangle(j * scale, i * scale, scale, scale, WHITE);
                }
            }
        }
        
        EndDrawing();
    }
    CloseWindow();
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 16; j++) {
            printf("%d", board[j][i]);
        }
        printf("\n");
    }
    return 0;
}
