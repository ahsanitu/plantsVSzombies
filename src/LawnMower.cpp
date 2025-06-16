#include "LawnMower.h"

LawnMower::LawnMower(Rectangle rect, int row, Texture2D texture)
    : rect(rect), row(row), texture(texture), active(true), activated(false), speed(300.0f) // Adjusted speed
{

}

void LawnMower::Update(float deltaTime) {
    if (activated && active) {
        rect.x += speed * deltaTime;
        // The lawnmower will be deactivated in main.cpp once it goes off-screen
    }
}

void LawnMower::Draw() {
    if (active) {
        DrawTextureRec(texture, (Rectangle){0, 0, (float)texture.width, (float)texture.height}, {rect.x, rect.y}, WHITE);
    }
}