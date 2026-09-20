#ifndef MENU_H
#define MENU_H

#include "Common.h"

struct Game;

void UpdateMenu(Game& game, float dt);
void DrawMenu(const Game& game);

#endif
