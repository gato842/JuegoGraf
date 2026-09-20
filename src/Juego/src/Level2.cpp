#include "../include/Level2.h"
#include "../include/Game.h"
#include <stdio.h>
#include <math.h>

void StartLevel2(Game& game) {
    game.currentScreen = SCREEN_LEVEL2;
    game.envDamage = 0.0f;
    game.levelTimer = 70.0f;
    game.hoseShootCooldown = 0.0f;

    InitPlayer(game.player);

    game.player.rec.x = (float)SCREEN_WIDTH / 2 - 16;
    game.player.rec.y = 12.0f * TILE_SIZE;
    game.player.aimAngle = 90.0f;

    InitFires(game.fires, 150);
    InitPlacedBuckets(game.placedBuckets, 3);
    InitWaterBeams(game.waterBeams, 30);

    SpawnFire(game.fires, 150, 3, 0, game.grid);
    SpawnFire(game.fires, 150, 6, 0, game.grid);
    SpawnFire(game.fires, 150, 9, 0, game.grid);
    SpawnFire(game.fires, 150, 12, 0, game.grid);
    SpawnFire(game.fires, 150, 15, 0, game.grid);
    SpawnFire(game.fires, 150, 18, 0, game.grid);
}

void UpdateLevel2(Game& game, float dt) {
    if (!IsSoundPlaying(game.fireLvl2Snd)) {
        PlaySound(game.fireLvl2Snd);
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        game.player.aimAngle += 130.0f * dt;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        game.player.aimAngle -= 130.0f * dt;
    }

    if (game.player.aimAngle < 15.0f) game.player.aimAngle = 15.0f;
    if (game.player.aimAngle > 165.0f) game.player.aimAngle = 165.0f;

    if (game.hoseShootCooldown > 0.0f) {
        game.hoseShootCooldown -= dt;
    }

    if (IsKeyDown(KEY_SPACE) && game.hoseShootCooldown <= 0.0f) {
        float px = game.player.rec.x + game.player.rec.width / 2;
        float py = game.player.rec.y + game.player.rec.height / 2;

        float rad = game.player.aimAngle * DEG2RAD;
        Vector2 nozzleEnd = { px + 30.0f * cosf(rad), py - 30.0f * sinf(rad) };

        if (ShootWaterBeam(game.waterBeams, 30, nozzleEnd, game.player.aimAngle)) {
            game.hoseShootCooldown = 0.08f;
        }
    }

    UpdateWaterBeams(game.waterBeams, 30, dt);

    UpdateFires(game.fires, 150, dt, true, game.grid);

    if (GetActiveFiresCount(game.fires, 150) == 0) {
        for (int col = 1; col < GRID_COLS - 1; col += 2) {
            SpawnFire(game.fires, 150, col, 0, game.grid);
        }
    }

    for (int b = 0; b < 30; b++) {
        if (!game.waterBeams[b].active) continue;

        for (int f = 0; f < 150; f++) {
            if (!game.fires[f].active) continue;

            if (CheckCollisionRecs(game.waterBeams[b].rec, game.fires[f].rec)) {
                game.fires[f].active = false;
                game.waterBeams[b].active = false;
                game.score += 25;
                PlaySound(game.extinguishSnd);
                break;
            }
        }
    }

    for (int f = 0; f < 150; f++) {
        if (game.fires[f].active && game.fires[f].gridY == 13) {
            StopSound(game.fireLvl2Snd);
            AddHighScore(game, game.score);
            game.currentScreen = SCREEN_LOSE;
            break;
        }
    }

    game.levelTimer -= dt;
    if (game.levelTimer <= 0.0f) {
        StopSound(game.fireLvl2Snd);
        AddHighScore(game, game.score);
        game.currentScreen = SCREEN_WIN;
    }
}

void DrawLevel2(const Game& game) {

    DrawFires(game.fires, 150, (Texture2D*)&game.fireTex);

    DrawWaterBeams(game.waterBeams, 30);

    float px = game.player.rec.x + game.player.rec.width / 2;
    float py = game.player.rec.y + game.player.rec.height / 2;
    float rad = game.player.aimAngle * DEG2RAD;

    for (int d = 1; d <= 8; d++) {
        float dist = d * 60.0f;
        DrawCircle(px + dist * cosf(rad), py - dist * sinf(rad), 2.0f, { 0, 160, 255, 120 });
    }

    Vector2 nozzleEnd = { px + 32.0f * cosf(rad), py - 32.0f * sinf(rad) };
    DrawLineEx({ px, py }, nozzleEnd, 6.0f, SKYBLUE);
    DrawCircle(nozzleEnd.x, nozzleEnd.y, 4.0f, BLUE);

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

    DrawRectangle(0, 0, SCREEN_WIDTH, 45, { 0, 0, 0, 180 });
    DrawText("NIVEL 2: DEFENSA DE LA COMUNIDAD", 15, 13, 16, RED);

    char timeText[30];
    sprintf(timeText, "RESISTIR TORMENTA: %d s", (int)game.levelTimer);
    DrawText(timeText, 350, 13, 16, WHITE);

    char scoreText[30];
    sprintf(scoreText, "SCORE: %d", game.score);
    DrawText(scoreText, SCREEN_WIDTH - 150, 13, 16, YELLOW);

    DrawRectangle(0, SCREEN_HEIGHT - 35, SCREEN_WIDTH, 35, { 0, 0, 0, 200 });
    DrawText("APUNTAR: Teclas [A/D] o [Flechas]. DISPARAR: Mantener [ESPACIO]", 15, SCREEN_HEIGHT - 25, 14, SKYBLUE);
    DrawText("¡No dejes que el viento empuje el fuego hasta las casas de los vecinos!", 480, SCREEN_HEIGHT - 25, 12, ORANGE);
}
