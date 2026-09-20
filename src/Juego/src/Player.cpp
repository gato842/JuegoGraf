#include "../include/Player.h"
#include "../include/Game.h"
#include <math.h>

void InitPlayer(Player& player) {

    player.rec = { (float)SCREEN_WIDTH / 2 - 16, (float)SCREEN_HEIGHT - 100, 32.0f, 32.0f };
    player.speed = 220.0f;
    player.waterCount = 0;
    player.maxWater = 8;
    player.placedBucketsCount = 0;
    player.direction = DIR_UP;
    player.color = BLUE;
    player.aimAngle = 90.0f;
    player.isMoving = false;
    player.carryingBucket = false;
    player.carriedBucketWater = 0;
    player.carriedBucketHealth = 0;
    player.health = 5;
    player.maxHealth = 5;
    player.damageCooldown = 0.0f;
}

void UpdatePlayer(Player& player) {
    float dt = GetFrameTime();

    if (player.damageCooldown > 0.0f) {
        player.damageCooldown -= dt;
    }

    bool moving = false;
    float dx = 0.0f;
    float dy = 0.0f;

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        dy = -1.0f;
        player.direction = DIR_UP;
        moving = true;
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        dy = 1.0f;
        player.direction = DIR_DOWN;
        moving = true;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        dx = -1.0f;
        player.direction = DIR_LEFT;
        moving = true;
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        dx = 1.0f;
        player.direction = DIR_RIGHT;
        moving = true;
    }

    if (moving) {

        float length = sqrtf(dx * dx + dy * dy);
        if (length > 0) {
            dx /= length;
            dy /= length;
        }
        player.rec.x += dx * player.speed * dt;
        player.rec.y += dy * player.speed * dt;
    }
    player.isMoving = moving;

    if (player.rec.x < 0) player.rec.x = 0;
    if (player.rec.y < 0) player.rec.y = 0;
    if (player.rec.x > SCREEN_WIDTH - player.rec.width) player.rec.x = SCREEN_WIDTH - player.rec.width;
    if (player.rec.y > SCREEN_HEIGHT - player.rec.height) player.rec.y = SCREEN_HEIGHT - player.rec.height;
}

void DrawPlayer(const Player& player, const Game& game) {
    if (game.currentScreen == SCREEN_LEVEL2) {

        if (game.truckSprite.id > 0) {

            Rectangle destRec = { player.rec.x + player.rec.width/2 - 60.0f, player.rec.y + player.rec.height/2 - 25.0f, 120.0f, 60.0f };
            DrawTexturePro(game.truckSprite,
                { 0.0f, 0.0f, (float)game.truckSprite.width, (float)game.truckSprite.height },
                destRec, { 0.0f, 0.0f }, 0.0f, WHITE);

            Color sirenColor = (((int)(GetTime() * 8.0f) % 2) == 0)
                ? (Color){ 0, 100, 255, 140 }
                : (Color){ 255, 30, 30, 140 };
            DrawCircle(player.rec.x + player.rec.width/2 - 20.0f, player.rec.y + player.rec.height/2 - 22.0f, 8.0f, sirenColor);
        } else {

            Rectangle destRec = { player.rec.x - 16, player.rec.y - 8, 64.0f, 32.0f };
            DrawRectangleRec(destRec, RED);
            DrawCircle(destRec.x + 16, destRec.y + 32, 6, BLACK);
            DrawCircle(destRec.x + 48, destRec.y + 32, 6, BLACK);
        }
        return;
    }

    Texture2D tex = game.playerStaticTex;
    Rectangle sourceRec;

    if (player.isMoving) {
        if (player.direction == DIR_UP) tex = game.playerMovArrTex;
        else if (player.direction == DIR_DOWN) tex = game.playerMovAbaTex;
        else if (player.direction == DIR_LEFT) tex = game.playerMovIzqTex;
        else if (player.direction == DIR_RIGHT) tex = game.playerMovDerTex;
    } else {

        if (player.direction == DIR_LEFT) {
            tex = game.playerMovIzqTex;
        } else {
            tex = game.playerStaticTex;
        }
    }

    if (tex.id > 0) {
        if (tex.width == 1344) {

            int col = 0;
            if (player.isMoving) {
                col = (int)(GetTime() * 8.0f) % 3;
            }
            int srcX = col * 448 + 59;
            sourceRec = { (float)srcX, 0.0f, 330.0f, 410.0f };
        }
        else {

            int col = 0;
            if (player.isMoving) {
                int animStep = (int)(GetTime() * 8.0f) % 3;
                col = (animStep == 0) ? 0 : (animStep == 1) ? 2 : 3;
            } else {

                if (player.direction == DIR_LEFT) {
                    col = 0;
                } else {
                    if (player.direction == DIR_DOWN) col = 0;
                    else if (player.direction == DIR_RIGHT) col = 2;
                    else if (player.direction == DIR_UP) col = 3;
                }
            }
            int srcX = col * 1032 + 136;
            int srcY = 37;
            sourceRec = { (float)srcX, (float)srcY, 760.0f, 950.0f };
        }

        DrawTexturePro(tex, sourceRec, player.rec, { 0.0f, 0.0f }, 0.0f, WHITE);

        if (player.carryingBucket) {
            DrawCircle(player.rec.x + player.rec.width - 4, player.rec.y + 4, 5.0f, SKYBLUE);
            DrawCircleLines(player.rec.x + player.rec.width - 4, player.rec.y + 4, 5.0f, DARKBLUE);

            char durText[15];
            sprintf(durText, "A%dV%d", player.carriedBucketWater, player.carriedBucketHealth);
            DrawText(durText, player.rec.x + player.rec.width + 2, player.rec.y - 2, 9, SKYBLUE);
        }
    } else {

        DrawRectangleRec(player.rec, player.color);
        DrawRectangleLinesEx(player.rec, 2.0f, DARKBLUE);

        DrawCircle(player.rec.x + player.rec.width/2, player.rec.y + player.rec.height/2, 10.0f, BROWN);
        DrawCircle(player.rec.x + player.rec.width/2, player.rec.y + player.rec.height/2, 6.0f, GOLD);

        Vector2 dirDot = { player.rec.x + player.rec.width/2, player.rec.y + player.rec.height/2 };
        if (player.direction == DIR_UP) dirDot.y -= 12;
        else if (player.direction == DIR_DOWN) dirDot.y += 12;
        else if (player.direction == DIR_LEFT) dirDot.x -= 12;
        else if (player.direction == DIR_RIGHT) dirDot.x += 12;
        DrawCircle(dirDot.x, dirDot.y, 4.0f, YELLOW);

        if (player.carryingBucket) {
            DrawCircle(player.rec.x + player.rec.width - 4, player.rec.y + 4, 5.0f, SKYBLUE);
            DrawCircleLines(player.rec.x + player.rec.width - 4, player.rec.y + 4, 5.0f, DARKBLUE);

            char durText[15];
            sprintf(durText, "A%dV%d", player.carriedBucketWater, player.carriedBucketHealth);
            DrawText(durText, player.rec.x + player.rec.width + 2, player.rec.y - 2, 9, SKYBLUE);
        }
    }
}
