#ifndef HELPER_NPC_H
#define HELPER_NPC_H

#include "Common.h"

struct Game;

struct NPC {
    Vector2 pos;
    float speed;
    bool active;
    Vector2 targetPos;
    bool hasTarget;
    float extinguishCooldown;

    int waterCount;
    int maxWater;
    bool goingToWell;
    int targetFireIdx;

    int direction;
    bool isMoving;
};

void InitHelperNPC(NPC& helper);
void UpdateHelperNPC(NPC& helper, Game& game, float dt);
void DrawHelperNPC(const NPC& helper, const Game& game);

#endif
