#ifndef BUCKET_H
#define BUCKET_H

#include "Common.h"
#include "Fire.h"

struct PlacedBucket {
    Rectangle rec;
    bool active;
    int gridX;
    int gridY;
    int water;
    int health;
};

void InitPlacedBuckets(PlacedBucket buckets[], int maxBuckets);
bool PlaceBucket(PlacedBucket buckets[], int maxBuckets, int gx, int gy, int water, int health);

void UpdatePlacedBuckets(PlacedBucket buckets[], int maxBuckets, Fire fires[], int maxFires, int& placedCount);
void DrawPlacedBuckets(const PlacedBucket buckets[], int maxBuckets, Texture2D* tex);
void DrawWaterSource(Vector2 pos, Texture2D* tex, bool animate);

#endif
