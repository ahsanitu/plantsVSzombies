#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


int main() {
    InitWindow(800, 450, "Raygui Test");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw a simple GUI button
        if (GuiButton((Rectangle){ 350, 200, 100, 40 }, "Click Me")) {
            // Optional: Do something when the button is clicked
            DrawText("Button Clicked!", 330, 260, 20, MAROON);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
