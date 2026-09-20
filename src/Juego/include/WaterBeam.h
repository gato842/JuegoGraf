#ifndef WATERBEAM_H
#define WATERBEAM_H

#include "Common.h"

struct WaterBeam {
    Rectangle rec;
    Vector2 velocity;
    bool active;
};

void InitWaterBeams(WaterBeam beams[], int maxBeams);
bool ShootWaterBeam(WaterBeam beams[], int maxBeams, Vector2 startPos, float angle);
void UpdateWaterBeams(WaterBeam beams[], int maxBeams, float dt);
void DrawWaterBeams(const WaterBeam beams[], int maxBeams);

#endif
