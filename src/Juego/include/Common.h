#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int TILE_SIZE = 40;
const int GRID_COLS = 20;
const int GRID_ROWS = 15;

enum GameScreen {
    SCREEN_MENU,
    SCREEN_INTRO_LVL1,
    SCREEN_LEVEL1,
    SCREEN_INTRO_LVL2,
    SCREEN_LEVEL2,
    SCREEN_WIN,
    SCREEN_LOSE,
    SCREEN_CREDITS,
    SCREEN_HIGHSCORES
};

enum Direction {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

struct GridCell {
    float burnTimer;
    bool permanentlyExtinguished;
};

inline bool IsInsideCampo(int gx, int gy, int minX, int maxX) {
    return (gx >= minX && gx <= maxX && gy >= 4 && gy <= 10);
}

#endif
