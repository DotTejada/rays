#include "raylib.h"
#include "stdio.h"

const int scale = 50;
const int screenWidth = 800;
const int screenHeight = 600;
const int cWidth = screenWidth / scale; //16
const int cHeight = screenHeight / scale; //12


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
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
