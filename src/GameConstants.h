// game_constants.h
#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

// Global Screen and Grid Constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int GRID_ROWS;
extern const int GRID_COLS;
extern const int TILE_SIZE;
extern const int GRID_START_X;
extern const int GRID_START_Y;

// Cherry Bomb specific
const float FUSE_DURATION = 1.5f;

// Zombie Animation and Behavior Constants
const int ZOMBIE_HEALTH = 100;
const float ZOMBIE_SPEED = 20.0f;
const float ZOMBIE_DAMAGE_PER_SECOND = 10.0f;

// Zombie Attack/Bite System constants
const int ZOMBIE_DAMAGE_PER_BITE = 20;
const float ZOMBIE_BITE_RATE = 0.8f;

// Regular Zombie Stats and Animation properties
const int REGULAR_ZOMBIE_HEALTH = 100;
const float REGULAR_ZOMBIE_SPEED = 20.0f;
const int REGULAR_ZOMBIE_TOTAL_SPRITE_ROWS = 2;
const int REGULAR_ZOMBIE_WALKING_NUM_FRAMES = 10;
const float REGULAR_ZOMBIE_WALKING_FRAME_SPEED = 0.25f;
const int REGULAR_ZOMBIE_EATING_NUM_FRAMES = 10;
const float REGULAR_ZOMBIE_EATING_FRAME_SPEED = 0.15f;

// Jumping Zombie Stats and Animation properties
const int JUMPING_ZOMBIE_HEALTH = 150;
const float JUMPING_ZOMBIE_SPEED = 25.0f;
const int JUMPING_ZOMBIE_NUM_FRAMES = 6;
const float JUMPING_ZOMBIE_FRAME_SPEED = 0.15f;
const int JUMPING_ZOMBIE_TOTAL_SPRITE_ROWS = 1;

// Zombie Score Values
const int REGULAR_ZOMBIE_SCORE_VALUE = 100;
const int JUMPING_ZOMBIE_SCORE_VALUE = 200;

// Plant Constants
const int PEASHOOTER_HEALTH = 100;
const int PEASHOOTER_DAMAGE = 20;

const int SUNFLOWER_HEALTH = 80;
const float SUNFLOWER_SUN_GENERATION_INTERVAL = 0.1f;

#endif // GAME_CONSTANTS_H