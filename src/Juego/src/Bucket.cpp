#include "../include/Bucket.h"
#include <stdio.h>

void InitPlacedBuckets(PlacedBucket buckets[], int maxBuckets) {
    for (int i = 0; i < maxBuckets; i++) {
        buckets[i].active = false;
        buckets[i].rec = { 0, 0, 0, 0 };
        buckets[i].gridX = -1;
        buckets[i].gridY = -1;
        buckets[i].water = 0;
        buckets[i].health = 0;
    }
}

bool PlaceBucket(PlacedBucket buckets[], int maxBuckets, int gx, int gy, int water, int health) {

    for (int i = 0; i < maxBuckets; i++) {
        if (buckets[i].active && buckets[i].gridX == gx && buckets[i].gridY == gy) {
            return false;
        }
    }

    for (int i = 0; i < maxBuckets; i++) {
        if (!buckets[i].active) {
            buckets[i].active = true;
            buckets[i].gridX = gx;
            buckets[i].gridY = gy;
            buckets[i].water = water;
            buckets[i].health = health;
            buckets[i].rec = {
                (float)gx * TILE_SIZE + 4,
                (float)gy * TILE_SIZE + 4,
                (float)TILE_SIZE - 8,
                (float)TILE_SIZE - 8
            };
            return true;
        }
    }
    return false;
}

void UpdatePlacedBuckets(PlacedBucket buckets[], int maxBuckets, Fire fires[], int maxFires, int& placedCount) {
    for (int i = 0; i < maxBuckets; i++) {
        if (!buckets[i].active) continue;

        for (int j = 0; j < maxFires; j++) {
            if (!fires[j].active) continue;

            if (fires[j].gridX == buckets[i].gridX && fires[j].gridY == buckets[i].gridY) {

                fires[j].active = false;

                if (buckets[i].water > 0) {
                    buckets[i].water--;
                } else {
                    buckets[i].health--;

                    if (buckets[i].health <= 0) {
                        buckets[i].active = false;
                        placedCount--;
                    }
                }
                break;
            }
        }
    }
}

void DrawPlacedBuckets(const PlacedBucket buckets[], int maxBuckets, Texture2D* tex) {
    for (int i = 0; i < maxBuckets; i++) {
        if (!buckets[i].active) continue;

        if (tex != nullptr && tex->id > 0) {
            DrawTexturePro(*tex,
                { 0.0f, 0.0f, (float)tex->width, (float)tex->height },
                buckets[i].rec,
                { 0, 0 },
                0.0f,
                WHITE);
        } else {

            DrawEllipse(buckets[i].rec.x + buckets[i].rec.width/2, buckets[i].rec.y + 6, buckets[i].rec.width/2, 4.0f, SKYBLUE);

            DrawRectangle(buckets[i].rec.x + 4, buckets[i].rec.y + 6, buckets[i].rec.width - 8, buckets[i].rec.height - 10, BLUE);
            DrawRectangleLines(buckets[i].rec.x + 4, buckets[i].rec.y + 6, buckets[i].rec.width - 8, buckets[i].rec.height - 10, DARKBLUE);

            DrawCircleLines(buckets[i].rec.x + buckets[i].rec.width/2, buckets[i].rec.y + 6, buckets[i].rec.width/3, DARKBLUE);

            char statusText[20];
            sprintf(statusText, "A%d V%d", buckets[i].water, buckets[i].health);
            DrawText(statusText, buckets[i].rec.x + 4, buckets[i].rec.y + 14, 10, YELLOW);
        }
    }
}

void DrawWaterSource(Vector2 pos, Texture2D* tex, bool animate) {
    Rectangle dest = { pos.x * TILE_SIZE, pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

    if (tex != nullptr && tex->id > 0) {

        int frameWidth = tex->width / 4;
        int frame = 0;
        if (animate) {
            frame = (int)(GetTime() * 4.0f) % 4;
        }
        Rectangle sourceRec = { (float)frame * frameWidth, 0.0f, (float)frameWidth, (float)tex->height };

        DrawTexturePro(*tex,
            sourceRec,
            dest,
            { 0, 0 },
            0.0f,
            WHITE);
    } else {

        DrawRectangleRec(dest, GRAY);
        DrawRectangleLinesEx(dest, 3.0f, DARKGRAY);

        DrawCircle(dest.x + TILE_SIZE/2, dest.y + TILE_SIZE/2, TILE_SIZE/3, BLUE);
        DrawCircleLines(dest.x + TILE_SIZE/2, dest.y + TILE_SIZE/2, TILE_SIZE/3, SKYBLUE);

        DrawLine(dest.x, dest.y + 5, dest.x + TILE_SIZE/2, dest.y - 8, RED);
        DrawLine(dest.x + TILE_SIZE/2, dest.y - 8, dest.x + TILE_SIZE, dest.y + 5, RED);
    }
}
