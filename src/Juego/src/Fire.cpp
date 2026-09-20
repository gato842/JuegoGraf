#include "../include/Fire.h"
#include <stdlib.h>
#include <math.h>

static bool IsTileOnFire(const Fire fires[], int maxFires, int gx, int gy) {
    for (int i = 0; i < maxFires; i++) {
        if (fires[i].active && fires[i].gridX == gx && fires[i].gridY == gy) {
            return true;
        }
    }
    return false;
}

void InitFires(Fire fires[], int maxFires) {
    for (int i = 0; i < maxFires; i++) {
        fires[i].active = false;
        fires[i].rec = { 0, 0, 0, 0 };
        fires[i].spreadTimer = 0.0f;
        fires[i].spreadInterval = 0.0f;
        fires[i].gridX = -1;
        fires[i].gridY = -1;
    }
}

bool SpawnFire(Fire fires[], int maxFires, int gridX, int gridY, const GridCell grid[GRID_COLS][GRID_ROWS]) {

    if (gridX < 0 || gridX >= GRID_COLS || gridY < 0 || gridY >= GRID_ROWS) return false;

    if (grid[gridX][gridY].permanentlyExtinguished) return false;

    if (IsTileOnFire(fires, maxFires, gridX, gridY)) return false;

    for (int i = 0; i < maxFires; i++) {
        if (!fires[i].active) {
            fires[i].active = true;
            fires[i].gridX = gridX;
            fires[i].gridY = gridY;
            fires[i].rec = {
                (float)gridX * TILE_SIZE,
                (float)gridY * TILE_SIZE,
                (float)TILE_SIZE,
                (float)TILE_SIZE
            };
            fires[i].spreadTimer = 0.0f;

            fires[i].spreadInterval = 4.0f + (float)(rand() % 4);
            return true;
        }
    }
    return false;
}

void UpdateFires(Fire fires[], int maxFires, float dt, bool windActive, const GridCell grid[GRID_COLS][GRID_ROWS]) {

    float intervalModifier = windActive ? (0.4f / 1.5f) : 1.0f;

    struct SpawnQueue {
        int x, y;
    } queue[50];
    int queueCount = 0;

    for (int i = 0; i < maxFires; i++) {
        if (!fires[i].active) continue;

        fires[i].spreadTimer += dt;

        float targetInterval = fires[i].spreadInterval * intervalModifier;
        if (fires[i].spreadTimer >= targetInterval) {
            fires[i].spreadTimer = 0.0f;

            int dirX = 0;
            int dirY = 0;

            if (windActive) {

                int roll = rand() % 100;
                if (roll < 65) {
                    dirX = 0;
                    dirY = 1;
                } else if (roll < 82) {
                    dirX = -1;
                    dirY = 0;
                } else if (roll < 99) {
                    dirX = 1;
                    dirY = 0;
                } else {
                    dirX = 0;
                    dirY = -1;
                }
            } else {

                int dir = rand() % 4;
                switch (dir) {
                    case 0: dirX = 0; dirY = -1; break;
                    case 1: dirX = 0; dirY = 1;  break;
                    case 2: dirX = -1; dirY = 0; break;
                    case 3: dirX = 1; dirY = 0;  break;
                }
            }

            int targetX = fires[i].gridX + dirX;
            int targetY = fires[i].gridY + dirY;

            if (targetX >= 0 && targetX < GRID_COLS && targetY >= 0 && targetY < GRID_ROWS) {
                if (!IsTileOnFire(fires, maxFires, targetX, targetY) && queueCount < 50) {
                    queue[queueCount++] = { targetX, targetY };
                }
            }
        }
    }

    for (int i = 0; i < queueCount; i++) {
        SpawnFire(fires, maxFires, queue[i].x, queue[i].y, grid);
    }
}

void DrawFires(const Fire fires[], int maxFires, Texture2D* tex) {
    for (int i = 0; i < maxFires; i++) {
        if (!fires[i].active) continue;

        if (tex != nullptr && tex->id > 0) {
            int frame = (int)(GetTime() * 10.0f + i) % 4;

            Rectangle sourceRec;
            if (tex->width == 2048) {

                int qRow = frame / 2;
                int qCol = frame % 2;
                int srcX = qCol * 1024 + 112;
                int srcY = qRow * 1024 + 37;
                sourceRec = { (float)srcX, (float)srcY, 800.0f, 950.0f };
            } else {
                int frameWidth = tex->width / 4;
                sourceRec = { (float)frame * frameWidth, 0.0f, (float)frameWidth, (float)tex->height };
            }

            DrawTexturePro(*tex,
                sourceRec,
                fires[i].rec,
                { 0, 0 },
                0.0f,
                WHITE);
        } else {

            float pulse = sinf(GetTime() * 10.0f + i) * 3.0f;

            Rectangle outerFlame = {
                fires[i].rec.x + 2 - pulse/2,
                fires[i].rec.y + 2 - pulse,
                fires[i].rec.width - 4 + pulse,
                fires[i].rec.height - 4 + pulse
            };
            DrawRectangleRec(outerFlame, ORANGE);

            Rectangle innerFlame = {
                fires[i].rec.x + 8,
                fires[i].rec.y + 10,
                fires[i].rec.width - 16,
                fires[i].rec.height - 12
            };
            DrawRectangleRec(innerFlame, RED);

            Rectangle coreFlame = {
                fires[i].rec.x + 14,
                fires[i].rec.y + 18,
                fires[i].rec.width - 28,
                fires[i].rec.height - 20
            };
            DrawRectangleRec(coreFlame, YELLOW);
        }
    }
}

int GetActiveFiresCount(const Fire fires[], int maxFires) {
    int count = 0;
    for (int i = 0; i < maxFires; i++) {
        if (fires[i].active) count++;
    }
    return count;
}
