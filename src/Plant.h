#ifndef PLANT_H
#define PLANT_H

#include "raylib.h"
#include <vector>
#include <memory>

// Forward declarations to avoid circular dependencies
class Zombie;
class Projectile;

// Enum to identify different plant types
enum class PlantType {
    PEASHOOTER,
    SUNFLOWER,
    CHERRY_BOMB,
    WALNUT,
    SHOVEL,
    REPEATER,
    ICE_PEA,
    NONE // Default or unselected type
};

//----------------------------------------------------------------------------------
// Base Plant Class
//----------------------------------------------------------------------------------
class Plant {
public:
    Rectangle rect;
    int health;
    bool active;
    Color color; // For debugging colors
    Texture2D texture; // The sprite/texture for the plant
    Rectangle sourceRect; // Current frame in the sprite sheet

    int row;
    int col;

    int currentFrame;
    float frameTimer;
    float frameSpeed;
    int numFrames;

    Plant(Rectangle rect, int health, Color color, Texture2D tex, int row, int col, int numFrames, float frameSpeed);

    virtual ~Plant() = default; // Virtual destructor for proper cleanup of derived objects

    virtual void Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                        std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                        Texture2D peaTex) = 0;

    virtual void Draw() const;

    virtual int GetCost() const = 0;

    virtual PlantType GetType() const = 0;

    void TakeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            active = false;
        }
    }
};

//----------------------------------------------------------------------------------
// Derived Plant Classes
//----------------------------------------------------------------------------------

// Peashooter
class Peashooter : public Plant {
protected:
    float fireRate;
    float fireTimer;

public:
    Peashooter(Rectangle rect, int row, int col, Texture2D tex);

    void Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                Texture2D peaTex) override;

    void Draw() const override;

    int GetCost() const override { return 50; }
    PlantType GetType() const override { return PlantType::PEASHOOTER; }
};

// Sunflower
class Sunflower : public Plant {
private:
    float sunProductionInterval; // Time between sun production
    float sunProductionTimer; // Timer to track sun production

public:
    Sunflower(Rectangle rect, int row, int col, Texture2D tex);

    void Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                Texture2D peaTex) override;

    void Draw() const override;

    int GetCost() const override { return 25; }
    PlantType GetType() const override { return PlantType::SUNFLOWER; }
};

// CherryBomb
class CherryBomb : public Plant {
private:
    float fuseTimer; // Time until explosion
    bool exploded;
    Sound explosionSound;

public:
    CherryBomb(Rectangle rect, int row, int col, Texture2D tex, Sound expSound);

    void Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                Texture2D peaTex) override;

    void Draw() const override;

    int GetCost() const override { return 50; }
    PlantType GetType() const override { return PlantType::CHERRY_BOMB; }
};

// WallNut
class WallNut : public Plant {
public:
    WallNut(Rectangle rect, int row, int col, Texture2D tex);

    void Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                Texture2D peaTex) override;

    void Draw() const override;

    int GetCost() const override { return 75; }
    PlantType GetType() const override { return PlantType::WALNUT; }
};

// Repeater
class Repeater : public Peashooter {
public:
    Repeater(Rectangle rect, int row, int col, Texture2D tex);

    void Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                Texture2D peaTex) override;

    void Draw() const override;

    int GetCost() const override { return 200; }
    PlantType GetType() const override { return PlantType::REPEATER; }
};

// IcePea
class IcePea : public Peashooter {
private:
    Texture2D icePeaProjectileTex;

public:
    IcePea(Rectangle rect, int row, int col, Texture2D tex, Texture2D icePeaProjTex);

    void Update(float deltaTime, std::vector<std::unique_ptr<Zombie> > &zombies,
                std::vector<std::unique_ptr<Projectile> > &projectiles, int &sunCurrency, Sound shootSound,
                Texture2D peaTex) override;

    void Draw() const override;

    int GetCost() const override { return 150; }
    PlantType GetType() const override { return PlantType::ICE_PEA; }
};

#endif // PLANT_H
