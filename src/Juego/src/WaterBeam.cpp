#include "../include/WaterBeam.h"
#include <math.h>

void InitWaterBeams(WaterBeam beams[], int maxBeams) {
    for (int i = 0; i < maxBeams; i++) {
        beams[i].active = false;
        beams[i].rec = { 0, 0, 0, 0 };
        beams[i].velocity = { 0, 0 };
    }
}

bool ShootWaterBeam(WaterBeam beams[], int maxBeams, Vector2 startPos, float angle) {
    for (int i = 0; i < maxBeams; i++) {
        if (!beams[i].active) {
            beams[i].active = true;
            beams[i].rec = { startPos.x - 6, startPos.y - 6, 12, 12 };

            float speed = 600.0f;
            float rad = angle * DEG2RAD;
            beams[i].velocity.x = speed * cosf(rad);
            beams[i].velocity.y = -speed * sinf(rad);
            return true;
        }
    }
    return false;
}

void UpdateWaterBeams(WaterBeam beams[], int maxBeams, float dt) {
    for (int i = 0; i < maxBeams; i++) {
        if (!beams[i].active) continue;

        beams[i].rec.x += beams[i].velocity.x * dt;
        beams[i].rec.y += beams[i].velocity.y * dt;

        if (beams[i].rec.x < 0 || beams[i].rec.x > SCREEN_WIDTH ||
            beams[i].rec.y < 0 || beams[i].rec.y > SCREEN_HEIGHT) {
            beams[i].active = false;
        }
    }
}

void DrawWaterBeams(const WaterBeam beams[], int maxBeams) {
    for (int i = 0; i < maxBeams; i++) {
        if (!beams[i].active) continue;

        DrawCircle(beams[i].rec.x + beams[i].rec.width/2, beams[i].rec.y + beams[i].rec.height/2, 6.0f, SKYBLUE);
        DrawCircleLines(beams[i].rec.x + beams[i].rec.width/2, beams[i].rec.y + beams[i].rec.height/2, 6.0f, BLUE);
        DrawCircle(beams[i].rec.x + beams[i].rec.width/2 - 2, beams[i].rec.y + beams[i].rec.height/2 - 2, 2.0f, WHITE);
    }
}
