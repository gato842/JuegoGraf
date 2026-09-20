#ifndef INTRO_H
#define INTRO_H

#include "Common.h"

struct Game;

struct DialogueLine {
    const char* speaker;
    const char* text;
    int bgIndex;
    int spriteIndex;
};

void StartIntroLvl1(Game& game);
void StartIntroLvl2(Game& game);
void UpdateIntro(Game& game, float dt);
void DrawIntro(const Game& game);

#endif
