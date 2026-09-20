#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"

struct Player {
    Rectangle rec;
    float speed;
    int waterCount;
    int maxWater;
    int placedBucketsCount;
    int direction;
    Color color;
    float aimAngle;
    bool isMoving;

    bool carryingBucket;
    int carriedBucketWater;
    int carriedBucketHealth;

    int health;
    int maxHealth;
    float damageCooldown;
};

struct Game;

void InitPlayer(Player& player);
void UpdatePlayer(Player& player);
void DrawPlayer(const Player& player, const Game& game);

#endif
