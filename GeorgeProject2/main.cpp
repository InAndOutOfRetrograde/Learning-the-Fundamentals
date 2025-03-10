
#include <raylib.h>
#include <iostream>
#include <utility>
#include <bitset>
#include <vector>
#include <string>

#include "InputBuffer.h"

InputBuffer buffer;
InputBuffer::DirectionMask checkedDirection = InputBuffer::DirectionMask::LEFT;

int main()
{
#pragma region display stuff
    int ballX = 400;
    int ballY = 400;
    Color green = { 20, 160, 133, 255 };

    InitWindow(800, 800, "My First raylib Game");
    SetTargetFPS(60);
#pragma endregion

    //Game Loop
    while (WindowShouldClose() == false)
    {
        int inputStorage = 0;

        // 1. Store Inputs.

        inputStorage |= buffer.RIGHT * IsKeyDown(KEY_RIGHT);
        inputStorage |= buffer.LEFT * IsKeyDown(KEY_LEFT);
        inputStorage |= buffer.UP * IsKeyDown(KEY_UP);
        inputStorage |= buffer.DOWN * IsKeyDown(KEY_DOWN);

        buffer.addToBuffer(inputStorage);   

        // 5. Drawing
        BeginDrawing();
        ClearBackground(green);
        DrawCircle(ballX, ballY, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}