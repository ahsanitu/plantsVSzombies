# 🌻 Plants vs. Zombies (C++ with Raylib)

A simplified, custom-made remake of the classic *Plants vs. Zombies* game, implemented in C++ using the [Raylib](https://www.raylib.com/) library for GUI. This version features an endless mode with increasing difficulty, and core gameplay centered around grid-based defense strategy.

## 🎮 Game Objective

Defend your home from waves of invading zombies by strategically placing different types of plants on a 5x9 grid. Survive as long as you can and beat your high score!

## 🧠 Gameplay Mechanics

- **Endless Mode**: Fight waves of zombies with increasing difficulty.
- **Grid-Based Layout**: Place plants on a 5 (rows) × 9 (columns) grid.
- **Currency System**: Earn sunlight to purchase plants.
- **Win/Lose Conditions**: Lose when any zombie reaches the leftmost column. No win condition—aim for high scores!

## 🌿 Plant Types

### Offensive ☘️
| Plant       | Cost | Description                                        |
|-------------|------|----------------------------------------------------|
| Peashooter  | 100  | Shoots single peas (1 damage each).                |
| Repeater    | 200  | Shoots 2 peas at once.                             |
| Threepeater | 325  | Shoots in 3 adjacent rows.                         |
| Gatling Pea | 250  | Shoots 4 peas (requires Repeater).                |

### Resource ☀️
| Plant           | Cost | Description                        |
|------------------|------|------------------------------------|
| Sunflower        | 50   | Generates 25 sun periodically.     |
| Twin Sunflower   | 150  | Generates double the sunlight.     |

### Defensive 🛡️
| Plant     | Cost | Description                                           |
|-----------|------|-------------------------------------------------------|
| Wall-nut  | 50   | Basic barrier; slow to eat through.                   |
| Tall-nut  | 125  | Blocks jumping zombies; stronger than Wall-nut.       |
| Pumpkin   | 125  | Protective shell placed over other plants.            |
| Garlic    | 50   | Forces zombies to switch to an adjacent row.          |

## 🧟 Zombies

Zombies spawn from the right and randomly enter one of the five rows. They slowly progress toward the left. If any zombie reaches your house, the game ends.

## 🔁 Game Loop Overview

```cpp
while (!gameOver) {
    handleInput();      // Player places plants
    spawnSun();         // Auto-generate sunlight
    spawnZombies();     // Spawn zombies periodically
    moveZombies();      // Zombies move toward the house
    plantActions();     // Plants shoot or generate sun
    checkCollisions();  // Handle bullet/zombie and zombie/plant collisions
    updateGrid();       // Update health and remove dead units
    drawEverything();   // Render the game
    checkWinLose();     // Determine if the game is over
}
