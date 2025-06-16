// projectile.h
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h" // Needed for Rectangle, Vector2, Color, Texture2D
#include <vector>   // Needed for Projectile::Update interaction with zombies
#include <memory>   // Needed for std::unique_ptr

// Forward declaration for Zombie, as Projectile might interact with it
class Zombie;

// Projectile types
enum class ProjectileType {
    NORMAL,
    FROZEN // For IcePea projectiles
};

//----------------------------------------------------------------------------------
// Projectile Class
//----------------------------------------------------------------------------------

class Projectile {
public:
    Rectangle rect;
    Vector2 speed;
    bool active;
    Color color;
    Texture2D texture;
    Rectangle sourceRect;
    int currentFrame;
    float frameTimer;
    float frameSpeed;
    int numFrames;
    int damage;
    ProjectileType type;

    // Constructor to initialize projectile properties
    Projectile(Rectangle pRect, Vector2 pSpeed, int pDamage, Texture2D pTex,
               ProjectileType pType = ProjectileType::NORMAL)
        : rect(pRect), speed(pSpeed), active(true), damage(pDamage), texture(pTex), type(pType),
          currentFrame(0), frameTimer(0.0f), frameSpeed(0.1f), numFrames(1) {
        sourceRect = {0, 0, (float) texture.width / numFrames, (float) texture.height};
        if (type == ProjectileType::FROZEN) {
            color = BLUE;
        } else {
            color = LIME;
        }
    }

    void Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies);

    void Draw() const;
};

#endif // PROJECTILE_H
