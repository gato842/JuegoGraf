#ifndef FIRE_H
#define FIRE_H

#include "Common.h"

struct Fire {
    Rectangle rec;
    bool active;
    float spreadTimer;
    float spreadInterval;
    int gridX;
    int gridY;
};

void InitFires(Fire fires[], int maxFires);
bool SpawnFire(Fire fires[], int maxFires, int gridX, int gridY, const GridCell grid[GRID_COLS][GRID_ROWS]);
void UpdateFires(Fire fires[], int maxFires, float dt, bool windActive, const GridCell grid[GRID_COLS][GRID_ROWS]);
void DrawFires(const Fire fires[], int maxFires, Texture2D* tex);
int GetActiveFiresCount(const Fire fires[], int maxFires);

#endif
