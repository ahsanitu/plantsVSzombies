// Projectile.cpp
#include "Projectile.h"
#include "Zombie.h" // For interacting with zombies

void Projectile::Update(float deltaTime, std::vector<std::unique_ptr<Zombie>>& zombies) {
    if (!active) return;

    // Move the projectile
    rect.x += speed.x * deltaTime;
    rect.y += speed.y * deltaTime;

    // Check for collision with zombies
    for (auto& zombie : zombies) {
        if (zombie->active && CheckCollisionRecs(rect, zombie->rect)) {
            zombie->TakeDamage(damage); // Apply damage to the zombie
            if (type == ProjectileType::FROZEN) {
                zombie->ApplySlowEffect(); // Apply slow effect if frozen type
            }
            active = false; // Deactivate projectile after impact
            break; // Exit collision check
        }
    }

    // Deactivate if it goes off-screen
    if (rect.x > GetScreenWidth() || rect.y > GetScreenHeight() || rect.x < 0 || rect.y < 0) {
        active = false;
    }
}

void Projectile::Draw() const {
    if (!active) return;

    // Draw the projectile. If there is a texture, use it; otherwise, fall back to color
    if (texture.id > 0) { // Assuming a valid texture has id > 0
        DrawTexturePro(texture, sourceRect, rect, {0, 0}, 0.0f, WHITE);
    } else {
        DrawRectangleRec(rect, color);
    }
}