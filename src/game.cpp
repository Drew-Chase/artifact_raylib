#include "game.h"

#include <raylib.h>

namespace artifact
{
    void Game::run()
    {
        InitWindow(800, 450, "raylib [core] example - basic window");

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            EndDrawing();
        }

        CloseWindow();
    }
} // namespace artifact
