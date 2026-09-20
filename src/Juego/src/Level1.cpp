#include "../include/Level1.h"
#include "../include/Game.h"
#include "../include/Level2.h"
#include "../include/Intro.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void StartLevel1(Game& game) {
    game.currentScreen = SCREEN_LEVEL1;
    game.envDamage = 0.0f;
    game.levelTimer = 110.0f;
    game.firesExtinguished = 0;
    game.expandTimer = 0.0f;

    for (int x = 0; x < GRID_COLS; x++) {
        for (int y = 0; y < GRID_ROWS; y++) {
            game.grid[x][y].burnTimer = 0.0f;
            game.grid[x][y].permanentlyExtinguished = false;
        }
    }

    game.campoMinX = 5;
    game.campoMaxX = 6;

    InitPlayer(game.player);

    game.player.placedBucketsCount = 0;
    game.player.carryingBucket = false;
    game.player.carriedBucketWater = 0;
    game.player.carriedBucketHealth = 0;

    InitFires(game.fires, 150);
    InitPlacedBuckets(game.placedBuckets, 3);
    InitWaterBeams(game.waterBeams, 30);

    InitHelperNPC(game.helper);

    SpawnFire(game.fires, 150, 5, 5, game.grid);
    SpawnFire(game.fires, 150, 6, 5, game.grid);
    SpawnFire(game.fires, 150, 5, 6, game.grid);
    SpawnFire(game.fires, 150, 6, 6, game.grid);
    SpawnFire(game.fires, 150, 5, 7, game.grid);
    SpawnFire(game.fires, 150, 6, 7, game.grid);
    SpawnFire(game.fires, 150, 5, 8, game.grid);
    SpawnFire(game.fires, 150, 6, 8, game.grid);
}

void UpdateLevel1(Game& game, float dt) {
    if (!IsSoundPlaying(game.fireLvl1Snd)) {
        PlaySound(game.fireLvl1Snd);
    }

    Vector2 prevPos = { game.player.rec.x, game.player.rec.y };

    UpdatePlayer(game.player);

    bool wasTouchingFire = false;
    for (int i = 0; i < 150; i++) {
        if (game.fires[i].active) {
            Rectangle prevRec = { prevPos.x, prevPos.y, game.player.rec.width, game.player.rec.height };
            if (CheckCollisionRecs(prevRec, game.fires[i].rec)) {
                wasTouchingFire = true;
                break;
            }
        }
    }

    bool isTouchingFireNow = false;
    for (int i = 0; i < 150; i++) {
        if (game.fires[i].active && CheckCollisionRecs(game.player.rec, game.fires[i].rec)) {
            isTouchingFireNow = true;
            break;
        }
    }

    if (isTouchingFireNow) {
        if (!wasTouchingFire) {

            game.player.rec.x = prevPos.x;
            game.player.rec.y = prevPos.y;
        }

        if (game.player.damageCooldown <= 0.0f) {
            game.player.health--;
            game.player.damageCooldown = 1.0f;
        }
    }

    Rectangle well1Rec = { 2.0f * TILE_SIZE, 3.0f * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };
    Rectangle well2Rec = { 2.0f * TILE_SIZE, 11.0f * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };
    if (CheckCollisionRecs(game.player.rec, well1Rec) || CheckCollisionRecs(game.player.rec, well2Rec)) {
        game.player.rec.x = prevPos.x;
        game.player.rec.y = prevPos.y;
    }

    int pgx = (int)(game.player.rec.x + game.player.rec.width / 2) / TILE_SIZE;
    int pgy = (int)(game.player.rec.y + game.player.rec.height / 2) / TILE_SIZE;

    UpdateHelperNPC(game.helper, game, dt);

    bool nearTopWell = (abs(pgx - (int)game.waterSourcePos.x) <= 1 && abs(pgy - (int)game.waterSourcePos.y) <= 1);
    bool nearBottomWell = (abs(pgx - 2) <= 1 && abs(pgy - 11) <= 1);
    bool nearWell = nearTopWell || nearBottomWell;

    if (nearWell && game.player.carryingBucket) {
        if (game.player.carriedBucketWater < 5 || game.player.carriedBucketHealth < 3) {
            game.player.carriedBucketWater = 5;
            game.player.carriedBucketHealth = 3;

            Vector2 wellPos = nearTopWell ? game.waterSourcePos : Vector2{ 2.0f, 11.0f };
            SpawnGameParticle(game, { wellPos.x * TILE_SIZE, wellPos.y * TILE_SIZE });
            PlaySound(game.wellSnd);
        }
    }

    int nearBucketIdx = -1;
    for (int i = 0; i < 3; i++) {
        if (game.placedBuckets[i].active) {
            if (abs(pgx - game.placedBuckets[i].gridX) <= 1 && abs(pgy - game.placedBuckets[i].gridY) <= 1) {
                nearBucketIdx = i;
                break;
            }
        }
    }

    if (IsKeyPressed(KEY_B)) {
        if (nearWell && !game.player.carryingBucket) {

            if (game.player.placedBucketsCount + 1 <= 3) {
                game.player.carryingBucket = true;
                game.player.carriedBucketWater = 5;
                game.player.carriedBucketHealth = 3;

                Vector2 wellPos = nearTopWell ? game.waterSourcePos : Vector2{ 2.0f, 11.0f };
                SpawnGameParticle(game, { wellPos.x * TILE_SIZE, wellPos.y * TILE_SIZE });
                PlaySound(game.wellSnd);
            }
        } else if (!nearWell && game.player.carryingBucket) {

            {

                bool tileOccupied = false;
                for (int i = 0; i < 3; i++) {
                    if (game.placedBuckets[i].active && game.placedBuckets[i].gridX == pgx && game.placedBuckets[i].gridY == pgy) {
                        tileOccupied = true;
                        break;
                    }
                }
                if (!tileOccupied) {
                    if (PlaceBucket(game.placedBuckets, 3, pgx, pgy, game.player.carriedBucketWater, game.player.carriedBucketHealth)) {
                        game.player.carryingBucket = false;
                        game.player.carriedBucketWater = 0;
                        game.player.carriedBucketHealth = 0;
                        game.player.placedBucketsCount++;
                        PlaySound(game.placeBucketSnd);
                    }
                }
            }
        } else if (!nearWell && !game.player.carryingBucket && nearBucketIdx != -1) {

            game.player.carryingBucket = true;
            game.player.carriedBucketWater = game.placedBuckets[nearBucketIdx].water;
            game.player.carriedBucketHealth = game.placedBuckets[nearBucketIdx].health;
            game.placedBuckets[nearBucketIdx].active = false;
            game.player.placedBucketsCount--;
        }
    }

    if (IsKeyPressed(KEY_C)) {
        if (game.player.carryingBucket && nearBucketIdx != -1) {
            int tempWater = game.player.carriedBucketWater;
            int tempHealth = game.player.carriedBucketHealth;
            game.player.carriedBucketWater = game.placedBuckets[nearBucketIdx].water;
            game.player.carriedBucketHealth = game.placedBuckets[nearBucketIdx].health;
            game.placedBuckets[nearBucketIdx].water = tempWater;
            game.placedBuckets[nearBucketIdx].health = tempHealth;
        }
    }

    int frontX = pgx;
    int frontY = pgy;
    if (game.player.direction == DIR_UP) frontY--;
    else if (game.player.direction == DIR_DOWN) frontY++;
    else if (game.player.direction == DIR_LEFT) frontX--;
    else if (game.player.direction == DIR_RIGHT) frontX++;

    if (game.player.carryingBucket && game.player.carriedBucketWater > 0 && IsKeyPressed(KEY_SPACE)) {
        int targetFireIdx = -1;
        for (int i = 0; i < 150; i++) {
            if (game.fires[i].active && game.fires[i].gridX == frontX && game.fires[i].gridY == frontY) {

                if (!IsInsideCampo(frontX, frontY, game.campoMinX, game.campoMaxX)) {
                    targetFireIdx = i;
                    break;
                }
            }
        }

        if (targetFireIdx != -1) {
            game.fires[targetFireIdx].active = false;
            game.player.carriedBucketWater--;
            game.firesExtinguished++;
            game.score += 150;
            PlaySound(game.extinguishSnd);
        }
    }

    UpdateFires(game.fires, 150, dt, false, game.grid);

    if (game.levelTimer > 90.0f) {

        game.campoMaxX = 7;
        for (int i = 0; i < 150; i++) {
            if (game.fires[i].active) {
                if (game.fires[i].gridX < 5 || game.fires[i].gridX > 7 || game.fires[i].gridY < 4 || game.fires[i].gridY > 10) {
                    game.fires[i].active = false;
                }
            }
        }
    } else {

        game.expandTimer += dt;
        if (game.expandTimer >= 4.0f) {
            game.expandTimer = 0.0f;
            if (game.campoMaxX < 19) {
                game.campoMaxX++;
                SpawnFire(game.fires, 150, game.campoMaxX, 4 + (rand() % 6), game.grid);
            }
        }

        for (int i = 0; i < 150; i++) {
            if (game.fires[i].active) {
                if (game.fires[i].gridX < 5 || game.fires[i].gridX > game.campoMaxX) {
                    game.fires[i].active = false;
                }
            }
        }
    }

    UpdatePlacedBuckets(game.placedBuckets, 3, game.fires, 150, game.player.placedBucketsCount);

    bool burningMap[GRID_COLS][GRID_ROWS] = { false };
    for (int i = 0; i < 150; i++) {
        if (game.fires[i].active) {
            int gx = game.fires[i].gridX;
            int gy = game.fires[i].gridY;
            if (gx >= 0 && gx < GRID_COLS && gy >= 0 && gy < GRID_ROWS) {
                burningMap[gx][gy] = true;
            }
        }
    }

    for (int x = 0; x < GRID_COLS; x++) {
        for (int y = 0; y < GRID_ROWS; y++) {
            if (burningMap[x][y]) {
                game.grid[x][y].burnTimer += dt;
                if (game.grid[x][y].burnTimer >= 30.0f) {

                    game.grid[x][y].permanentlyExtinguished = true;

                    for (int i = 0; i < 150; i++) {
                        if (game.fires[i].active && game.fires[i].gridX == x && game.fires[i].gridY == y) {
                            game.fires[i].active = false;
                        }
                    }
                }
            } else {
                if (!game.grid[x][y].permanentlyExtinguished) {
                    game.grid[x][y].burnTimer = 0.0f;
                }
            }
        }
    }

    if (game.player.health <= 0) {
        game.currentScreen = SCREEN_LOSE;
    }

    int activeFiresOutside = 0;
    for (int i = 0; i < 150; i++) {
        if (game.fires[i].active && !IsInsideCampo(game.fires[i].gridX, game.fires[i].gridY, game.campoMinX, game.campoMaxX)) {
            activeFiresOutside++;
        }
    }

    if (activeFiresOutside > 0) {
        game.envDamage += 1.9f * activeFiresOutside * dt;
    } else {
        game.envDamage -= 1.575f * dt;
        if (game.envDamage < 0.0f) game.envDamage = 0.0f;
    }

    if (game.envDamage >= 100.0f) {
        StopSound(game.fireLvl1Snd);
        AddHighScore(game, game.score);
        game.currentScreen = SCREEN_LOSE;
    }

    game.levelTimer -= dt;
    if (game.levelTimer <= 0.0f) {
        StopSound(game.fireLvl1Snd);

        StartIntroLvl2(game);
    }
}

void DrawLevel1(const Game& game) {

    for (int x = 0; x < GRID_COLS; x++) {
        for (int y = 0; y < GRID_ROWS; y++) {
            if (game.grid[x][y].permanentlyExtinguished) {

                Rectangle ashDest = { (float)x * TILE_SIZE - 6, (float)y * TILE_SIZE - 6, (float)TILE_SIZE + 12, (float)TILE_SIZE + 12 };
                if (game.ashTex.id > 0) {
                    DrawTexturePro(game.ashTex, { 0.0f, 0.0f, (float)game.ashTex.width, (float)game.ashTex.height }, ashDest, { 0, 0 }, 0.0f, WHITE);
                } else {
                    DrawRectangle(x * TILE_SIZE + 2, y * TILE_SIZE + 2, TILE_SIZE - 4, TILE_SIZE - 4, { 55, 55, 55, 200 });
                    DrawRectangleLines(x * TILE_SIZE + 2, y * TILE_SIZE + 2, TILE_SIZE - 4, TILE_SIZE - 4, { 80, 80, 80, 200 });
                    DrawText("CENIZAS", x * TILE_SIZE + 4, y * TILE_SIZE + 16, 7, LIGHTGRAY);
                }
            }
        }
    }

    Rectangle campoRect = {
        (float)game.campoMinX * TILE_SIZE,
        4.0f * TILE_SIZE,
        (float)(game.campoMaxX - game.campoMinX + 1) * TILE_SIZE,
        7.0f * TILE_SIZE
    };

    DrawRectangleRec(campoRect, { 80, 45, 10, 75 });
    DrawRectangleLinesEx(campoRect, 2.0f, { 255, 120, 0, 180 });

    DrawText("CAMPO DE QUEMA CONTROLADA", campoRect.x + 15, campoRect.y + 15, 14, { 255, 120, 0, 100 });
    DrawText("FUEGO INAPAGABLE", campoRect.x + 15, campoRect.y + 35, 12, { 255, 60, 0, 100 });

    if (game.grassTex.id > 0) {
        for (int x = 5; x <= 19; x++) {
            for (int y = 4; y <= 10; y++) {

                bool hasFire = false;
                for (int i = 0; i < 150; i++) {
                    if (game.fires[i].active && game.fires[i].gridX == x && game.fires[i].gridY == y) {
                        hasFire = true;
                        break;
                    }
                }

                if (!hasFire && !game.grid[x][y].permanentlyExtinguished) {

                    int frame = (int)(GetTime() * 2.0f + x + y) % 3;

                    int srcX = frame * 600 + 50;
                    int srcY = 280;
                    Rectangle sourceRec = { (float)srcX, (float)srcY, 500.0f, 300.0f };
                    Rectangle destRec = { (float)x * TILE_SIZE, (float)y * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };

                    DrawTexturePro(game.grassTex, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
                }
            }
        }
    }

    int pgx = (int)(game.player.rec.x + game.player.rec.width / 2) / TILE_SIZE;
    int pgy = (int)(game.player.rec.y + game.player.rec.height / 2) / TILE_SIZE;

    bool nearTop = (abs(pgx - (int)game.waterSourcePos.x) <= 1 && abs(pgy - (int)game.waterSourcePos.y) <= 1);
    bool playerRefillingTop = nearTop && game.player.carryingBucket && (game.player.carriedBucketWater < 5 || game.player.carriedBucketHealth < 3);

    bool nearBottom = (abs(pgx - 2) <= 1 && abs(pgy - 11) <= 1);
    bool playerRefillingBottom = nearBottom && game.player.carryingBucket && (game.player.carriedBucketWater < 5 || game.player.carriedBucketHealth < 3);

    int npx = (int)(game.helper.pos.x + 16) / TILE_SIZE;
    int npy = (int)(game.helper.pos.y + 16) / TILE_SIZE;
    bool npcRefillingBottom = game.helper.goingToWell && (abs(npx - 2) <= 1 && abs(npy - 11) <= 1);
    bool bottomWellActive = playerRefillingBottom || npcRefillingBottom;

    if (game.bgTex.id == 0) {
        DrawWaterSource(game.waterSourcePos, (Texture2D*)&game.sourceTex, playerRefillingTop);
        DrawWaterSource({ 2.0f, 11.0f }, (Texture2D*)&game.sourceTex, bottomWellActive);
    }

    DrawPlacedBuckets(game.placedBuckets, 3, (Texture2D*)&game.bucketTex);

    for (int i = 0; i < 150; i++) {
        if (!game.fires[i].active) continue;

        int gx = game.fires[i].gridX;
        int gy = game.fires[i].gridY;
        float bTime = game.grid[gx][gy].burnTimer;

        bool inside = IsInsideCampo(gx, gy, game.campoMinX, game.campoMaxX);

        Texture2D activeTex = game.fireTex;
        if (inside) {

            if (bTime < 10.0f) {
                if (game.fireStage1Tex.id > 0) activeTex = game.fireStage1Tex;
            } else if (bTime < 20.0f) {
                if (game.fireStage2Tex.id > 0) activeTex = game.fireStage2Tex;
            } else {
                if (game.fireStage3Tex.id > 0) activeTex = game.fireStage3Tex;
            }
        } else {

            if (game.fireTex.id > 0) {
                activeTex = game.fireTex;
            }
        }

        if (activeTex.id > 0) {
            int frame = (int)(GetTime() * 6.0f + i) % 4;

            Rectangle sourceRec;
            if (activeTex.id == game.fireStage1Tex.id) {

                int srcX = (frame == 0) ? 170 : (frame == 1) ? 1032 : (frame == 2) ? 2253 : 3272;
                int srcY = 150;
                sourceRec = { (float)srcX, (float)srcY, 700.0f, 700.0f };
            } else if (activeTex.id == game.fireStage2Tex.id) {

                int srcX = (frame == 0) ? 106 : (frame == 1) ? 948 : (frame == 2) ? 2075 : 3168;
                int srcY = 110;
                sourceRec = { (float)srcX, (float)srcY, 900.0f, 900.0f };
            } else if (activeTex.id == game.fireTex.id) {

                int qRow = frame / 2;
                int qCol = frame % 2;
                int srcX = qCol * 1024 + 112;
                int srcY = qRow * 1024 + 37;
                sourceRec = { (float)srcX, (float)srcY, 800.0f, 950.0f };
            } else {
                int frameWidth = activeTex.width / 4;
                sourceRec = { (float)frame * frameWidth, 0.0f, (float)frameWidth, (float)activeTex.height };
            }

            Rectangle destRec = game.fires[i].rec;

            DrawTexturePro(activeTex, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
        } else {

            float pulse = sinf(GetTime() * 10.0f + i) * 3.0f;
            Color outerColor = ORANGE;
            Color innerColor = RED;
            if (bTime < 10.0f) {
                outerColor = { 255, 170, 0, 255 };
                innerColor = YELLOW;
            } else if (bTime < 20.0f) {
                outerColor = RED;
                innerColor = YELLOW;
            } else {
                outerColor = DARKGRAY;
                innerColor = ORANGE;
            }

            Rectangle outerFlame = {
                game.fires[i].rec.x + 2 - pulse/2,
                game.fires[i].rec.y + 2 - pulse,
                game.fires[i].rec.width - 4 + pulse,
                game.fires[i].rec.height - 4 + pulse
            };
            DrawRectangleRec(outerFlame, outerColor);

            Rectangle innerFlame = {
                game.fires[i].rec.x + 8,
                game.fires[i].rec.y + 10,
                game.fires[i].rec.width - 16,
                game.fires[i].rec.height - 12
            };
            DrawRectangleRec(innerFlame, innerColor);
        }
    }

    DrawHelperNPC(game.helper, game);

    DrawPlayer(game.player, game);

    for (int i = 0; i < 50; i++) {
        if (game.particles[i].active) {
            int frame = (int)(game.particles[i].timer * 15.0f);
            if (frame < 0) frame = 0;
            if (frame > 15) frame = 15;

            if (game.particleTex.id > 0) {

                int col = frame % 4;
                int row = frame / 4;
                int srcX = 67 + col * 101 + 2;
                int srcY = 693 + row * 101 + 2;
                Rectangle sourceRec = { (float)srcX, (float)srcY, 97.0f, 97.0f };

                Rectangle destRec = { game.particles[i].pos.x, game.particles[i].pos.y, 40.0f, 40.0f };
                DrawTexturePro(game.particleTex, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
            } else {

                float radius = game.particles[i].timer * 20.0f;
                DrawCircleLines(game.particles[i].pos.x + 20, game.particles[i].pos.y + 20, radius, SKYBLUE);
            }
        }
    }

    if (game.player.carryingBucket) {
        int pgx = (int)(game.player.rec.x + game.player.rec.width / 2) / TILE_SIZE;
        int pgy = (int)(game.player.rec.y + game.player.rec.height / 2) / TILE_SIZE;
        int frontX = pgx;
        int frontY = pgy;
        if (game.player.direction == DIR_UP) frontY--;
        else if (game.player.direction == DIR_DOWN) frontY++;
        else if (game.player.direction == DIR_LEFT) frontX--;
        else if (game.player.direction == DIR_RIGHT) frontX++;

        if (frontX >= 0 && frontX < GRID_COLS && frontY >= 0 && frontY < GRID_ROWS) {
            DrawRectangleLinesEx({ (float)frontX * TILE_SIZE, (float)frontY * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE }, 2.0f, SKYBLUE);
        }
    }

    DrawRectangle(0, 0, SCREEN_WIDTH, 45, { 0, 0, 0, 180 });

    if (game.levelTimer > 90.0f) {
        DrawText("NIVEL 1: FASE PREPARACION (20s)", 15, 13, 16, ORANGE);
        DrawText("¡Recoge y coloca baldes estratégicamente!", 15, 50, 12, LIGHTGRAY);
    } else {
        DrawText("NIVEL 1: FASE DEFENSIVA (90s)", 15, 13, 16, RED);
    }

    char timeText[30];
    sprintf(timeText, "TIEMPO: %d s", (int)game.levelTimer);
    DrawText(timeText, 320, 13, 16, WHITE);

    if (game.player.carryingBucket) {
        char bucketLifeText[50];
        sprintf(bucketLifeText, "BALDE - AGUA: %d/5 | VIDA: %d/3", game.player.carriedBucketWater, game.player.carriedBucketHealth);
        DrawText(bucketLifeText, 410, 13, 16, SKYBLUE);
    } else {
        DrawText("SIN BALDE! (Recoge en Pozo [B])", 450, 13, 16, RED);
    }

    DrawRectangle(0, SCREEN_HEIGHT - 35, SCREEN_WIDTH, 35, { 0, 0, 0, 200 });
    DrawText("Llevar/Dejar Balde: [B] | Cambiar Balde: [C] | Apagar Frente: [ESPACIO]", 15, SCREEN_HEIGHT - 25, 13, GOLD);
    DrawText("¡No toques el fuego!", SCREEN_WIDTH - 160, SCREEN_HEIGHT - 25, 13, RED);

    DrawText("DAÑO AMBIENTAL:", 15, 65, 12, RED);
    DrawRectangle(15, 80, 200, 15, DARKGRAY);
    float damageWidth = (game.envDamage / 100.0f) * 200.0f;
    if (damageWidth > 200.0f) damageWidth = 200.0f;
    DrawRectangle(15, 80, (int)damageWidth, 15, RED);
    DrawRectangleLines(15, 80, 200, 15, WHITE);

    char damagePct[10];
    sprintf(damagePct, "%d%%", (int)game.envDamage);
    DrawText(damagePct, 225, 80, 14, RED);

    DrawText("VIDA:", 300, 65, 12, GREEN);
    DrawRectangle(300, 80, 200, 15, DARKGRAY);
    float healthWidth = ((float)game.player.health / (float)game.player.maxHealth) * 200.0f;
    if (healthWidth < 0.0f) healthWidth = 0.0f;
    DrawRectangle(300, 80, (int)healthWidth, 15, GREEN);
    DrawRectangleLines(300, 80, 200, 15, WHITE);

    char healthPct[10];
    sprintf(healthPct, "%d/%d", game.player.health, game.player.maxHealth);
    DrawText(healthPct, 510, 80, 14, GREEN);

    char scoreText[30];
    sprintf(scoreText, "SCORE: %d", game.score);
    DrawText(scoreText, SCREEN_WIDTH - 150, 13, 16, YELLOW);
}
