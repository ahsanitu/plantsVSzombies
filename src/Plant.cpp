// plant.cpp
#include "Plant.h"
#include "Projectile.h" // Needed to create Projectile objects
#include "Zombie.h"     // Needed to interact with Zombie objects
#include <iostream>     // For debug prints (optional)
#include <algorithm>    // For std::max (CherryBomb)

// Defined global grid constants from main.cpp
// These need to be extern if they are defined in main.cpp and used here.
extern const int GRID_START_X;
extern const int GRID_START_Y;
extern const int TILE_SIZE;
extern const int GRID_ROWS;
extern const int GRID_COLS;

//----------------------------------------------------------------------------------
// Base Plant Implementation
//----------------------------------------------------------------------------------
Plant::Plant(Rectangle rect, int health, Color color, Texture2D tex, int row, int col, int numFrames, float frameSpeed)
    : rect(rect), health(health), active(true), color(color), texture(tex),
      row(row), col(col),
      currentFrame(0), frameTimer(0.0f), frameSpeed(frameSpeed), numFrames(numFrames) {
    sourceRect = {0, 0, (float) texture.width / numFrames, (float) texture.height};
}

void Plant::Draw() const {
    if (active) {
        DrawTexturePro(texture, sourceRect, rect, {0, 0}, 0, WHITE);
    }
}

//----------------------------------------------------------------------------------
// Peashooter Implementations
//----------------------------------------------------------------------------------
Peashooter::Peashooter(Rectangle rect, int row, int col, Texture2D tex)
    : Plant(rect, 100, GREEN, tex, row, col, 1, 0.0f),
      fireRate(1.5f), fireTimer(1.5f) {
}

void Peashooter::Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                        std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                        Texture2D peaTex) {
    if (!active) return;

    frameTimer += deltaTime;
    if (frameTimer >= frameSpeed) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % numFrames;
        sourceRect.x = currentFrame * sourceRect.width;
    }

    fireTimer += deltaTime;
    if (fireTimer >= fireRate) {
        bool zombieInLane = false;
        for (const auto &zombie: zombies) {
            if (zombie->active && zombie->row == this->row && zombie->rect.x > this->rect.x) {
                zombieInLane = true;
                break;
            }
        }

        if (zombieInLane) {
            fireTimer = 0.0f;
            std::unique_ptr<Projectile> newProjectile = std::make_unique<Projectile>(
                (Rectangle){this->rect.x + this->rect.width, this->rect.y + this->rect.height / 4, 20, 10},
                (Vector2){300.0f, 0.0f},
                50,
                peaTex,
                ProjectileType::NORMAL
            );
            projectiles.push_back(std::move(newProjectile));
            PlaySound(shootSound);
        }
    }
}

void Peashooter::Draw() const {
    Plant::Draw();
}

//----------------------------------------------------------------------------------
// Sunflower Implementations
//----------------------------------------------------------------------------------
Sunflower::Sunflower(Rectangle rect, int row, int col, Texture2D tex)
    : Plant(rect, 80, YELLOW, tex, row, col, 1, 0.0f),
      sunProductionInterval(10.0f), sunProductionTimer(0.0f) {
}

void Sunflower::Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                       std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                       Texture2D peaTex) {
    if (!active) return;

    frameTimer += deltaTime;
    if (frameTimer >= frameSpeed) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % numFrames;
        sourceRect.x = currentFrame * sourceRect.width;
    }

    sunProductionTimer += deltaTime;
    if (sunProductionTimer >= sunProductionInterval) {
        sunProductionTimer = 0.0f;
        sunCurrency += 25;
        std::cout << "Sunflower produced sun! Current sun: " << sunCurrency << std::endl;
    }
}

void Sunflower::Draw() const {
    Plant::Draw();
}

//----------------------------------------------------------------------------------
// CherryBomb Implementations
//----------------------------------------------------------------------------------
CherryBomb::CherryBomb(Rectangle rect, int row, int col, Texture2D tex, Sound expSound)
    : Plant(rect, 1, RED, tex, row, col, 1, 0.0f),
      fuseTimer(0.0f), exploded(false), explosionSound(expSound) {
}

void CherryBomb::Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                        std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                        Texture2D peaTex) {
    if (!active || exploded) return;

    frameTimer += deltaTime;
    if (frameTimer >= frameSpeed) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % numFrames;
        sourceRect.x = currentFrame * sourceRect.width;
    }

    fuseTimer += deltaTime;
    if (fuseTimer >= FUSE_DURATION) {
        exploded = true;
        this->active = false;
        PlaySound(explosionSound);

        int explosionDamage = 9999;
        Rectangle explosionArea = {
            (float) (GRID_START_X + (this->col - 1) * TILE_SIZE),
            (float) (GRID_START_Y + (this->row - 1) * TILE_SIZE),
            (float) (TILE_SIZE * 3),
            (float) (TILE_SIZE * 3)
        };

        explosionArea.x = std::max((float) GRID_START_X, explosionArea.x);
        explosionArea.y = std::max((float) GRID_START_Y, explosionArea.y);
        explosionArea.width = std::min((float) GRID_COLS * TILE_SIZE - (explosionArea.x - GRID_START_X),
                                       explosionArea.width);
        explosionArea.height = std::min((float) GRID_ROWS * TILE_SIZE - (explosionArea.y - GRID_START_Y),
                                        explosionArea.height);

        for (auto &zombie: zombies) {
            if (zombie->active && CheckCollisionRecs(explosionArea, zombie->rect)) {
                zombie->health -= explosionDamage;
            }
        }
        std::cout << "CherryBomb exploded! Damaged zombies in area." << std::endl;
    }
}

void CherryBomb::Draw() const {
    Plant::Draw();
}

//----------------------------------------------------------------------------------
// WallNut Implementations
//----------------------------------------------------------------------------------
WallNut::WallNut(Rectangle rect, int row, int col, Texture2D tex)
    : Plant(rect, 400, BROWN, tex, row, col, 1, 0.0f) {
}

void WallNut::Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                     std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                     Texture2D peaTex) {
    if (!active) return;

    frameTimer += deltaTime;
    if (frameTimer >= frameSpeed) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % numFrames;
        sourceRect.x = currentFrame * sourceRect.width;
    }
}

void WallNut::Draw() const {
    Plant::Draw();
}

//----------------------------------------------------------------------------------
// Repeater Implementations (NEW!)
//----------------------------------------------------------------------------------
Repeater::Repeater(Rectangle rect, int row, int col, Texture2D tex)
    : Peashooter(rect, row, col, tex) {
    this->fireRate = 1.0f;
    this->fireTimer = this->fireRate;
    this->health = 100;
}

void Repeater::Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                      std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                      Texture2D peaTex) {
    if (!active) return;

    frameTimer += deltaTime;
    if (frameTimer >= frameSpeed) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % numFrames;
        sourceRect.x = currentFrame * sourceRect.width;
    }

    fireTimer += deltaTime;
    if (fireTimer >= fireRate) {
        bool zombieInLane = false;
        for (const auto &zombie: zombies) {
            if (zombie->active && zombie->row == this->row && zombie->rect.x > this->rect.x) {
                zombieInLane = true;
                break;
            }
        }

        if (zombieInLane) {
            fireTimer = 0.0f;

            std::unique_ptr<Projectile> newProjectile1 = std::make_unique<Projectile>(
                (Rectangle){this->rect.x + this->rect.width, this->rect.y + this->rect.height / 4, 20, 10},
                (Vector2){300.0f, 0.0f},
                50,
                peaTex,
                ProjectileType::NORMAL
            );
            projectiles.push_back(std::move(newProjectile1));
            PlaySound(shootSound);

            std::unique_ptr<Projectile> newProjectile2 = std::make_unique<Projectile>(
                (Rectangle){this->rect.x + this->rect.width, this->rect.y + this->rect.height / 4, 20, 10},
                (Vector2){300.0f, 0.0f},
                50,
                peaTex,
                ProjectileType::NORMAL
            );
            projectiles.push_back(std::move(newProjectile2));
        }
    }
}

void Repeater::Draw() const {
    Plant::Draw();
}

//----------------------------------------------------------------------------------
// IcePea Implementations (NEW!)
//----------------------------------------------------------------------------------
IcePea::IcePea(Rectangle rect, int row, int col, Texture2D tex, Texture2D icePeaProjTex)
    : Peashooter(rect, row, col, tex), icePeaProjectileTex(icePeaProjTex) {
    this->fireRate = 1.8f;
    this->fireTimer = this->fireRate;
    this->health = 200;
}

void IcePea::Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                    std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                    Texture2D peaTex) {
    if (!active) return;

    frameTimer += deltaTime;
    if (frameTimer >= frameSpeed) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % numFrames;
        sourceRect.x = currentFrame * sourceRect.width;
    }

    fireTimer += deltaTime;
    if (fireTimer >= fireRate) {
        bool zombieInLane = false;
        for (const auto &zombie: zombies) {
            if (zombie->active && zombie->row == this->row && zombie->rect.x > this->rect.x) {
                zombieInLane = true;
                break;
            }
        }

        if (zombieInLane) {
            fireTimer = 0.0f;

            std::unique_ptr<Projectile> newProjectile = std::make_unique<Projectile>(
                (Rectangle){this->rect.x + this->rect.width, this->rect.y + this->rect.height / 4, 20, 10},
                (Vector2){300.0f, 0.0f},
                50,
                icePeaProjectileTex,
                ProjectileType::FROZEN
            );
            projectiles.push_back(std::move(newProjectile));
            PlaySound(shootSound);
        }
    }
}

void IcePea::Draw() const {
    Plant::Draw();
}
