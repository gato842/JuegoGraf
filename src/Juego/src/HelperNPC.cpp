#include "../include/HelperNPC.h"
#include "../include/Game.h"
#include <math.h>

void InitHelperNPC(NPC& helper) {
    helper.pos = { 2.0f * TILE_SIZE, 11.0f * TILE_SIZE };
    helper.speed = 110.0f;
    helper.active = true;
    helper.hasTarget = false;
    helper.targetPos = helper.pos;
    helper.extinguishCooldown = 0.0f;
    helper.waterCount = 0;
    helper.maxWater = 5;
    helper.goingToWell = false;
    helper.targetFireIdx = -1;
    helper.direction = DIR_DOWN;
    helper.isMoving = false;
}

void UpdateHelperNPC(NPC& helper, Game& game, float dt) {
    if (!helper.active) return;

    Rectangle npcRec = { helper.pos.x, helper.pos.y, 32.0f, 32.0f };

    if (helper.waterCount > 0) {
        for (int i = 0; i < 150; i++) {
            if (game.fires[i].active && game.fires[i].gridY >= 8 && game.fires[i].gridY <= 13) {
                if (!IsInsideCampo(game.fires[i].gridX, game.fires[i].gridY, game.campoMinX, game.campoMaxX)) {
                    if (CheckCollisionRecs(npcRec, game.fires[i].rec)) {
                        game.fires[i].active = false;
                        helper.waterCount--;
                        game.score += 50;
                        if (i == helper.targetFireIdx) {
                            helper.hasTarget = false;
                            helper.targetFireIdx = -1;
                        }
                        break;
                    }
                }
            }
        }
    }

    npcRec = { helper.pos.x, helper.pos.y, 32.0f, 32.0f };

    if (helper.waterCount > 0) {

        float minDistance = 999999.0f;
        int targetFireIdx = -1;

        for (int i = 0; i < 150; i++) {
            if (game.fires[i].active && game.fires[i].gridY >= 8 && game.fires[i].gridY <= 13) {
                if (!IsInsideCampo(game.fires[i].gridX, game.fires[i].gridY, game.campoMinX, game.campoMaxX)) {
                    Vector2 fCenter = { game.fires[i].rec.x + 20, game.fires[i].rec.y + 20 };
                    float dx = fCenter.x - helper.pos.x;
                    float dy = fCenter.y - helper.pos.y;
                    float dist = sqrtf(dx*dx + dy*dy);
                    if (dist < minDistance) {
                        minDistance = dist;
                        targetFireIdx = i;
                    }
                }
            }
        }

        if (targetFireIdx != -1) {
            helper.targetFireIdx = targetFireIdx;
            helper.targetPos = { game.fires[targetFireIdx].rec.x + 4, game.fires[targetFireIdx].rec.y + 4 };
            helper.hasTarget = true;
            helper.goingToWell = false;
        } else {

            helper.targetFireIdx = -1;
            helper.targetPos = { 10.0f * TILE_SIZE, 12.0f * TILE_SIZE };
            helper.hasTarget = false;
            helper.goingToWell = false;
        }
    } else {

        helper.targetFireIdx = -1;
        helper.targetPos = { 2.0f * TILE_SIZE, 11.0f * TILE_SIZE };
        helper.hasTarget = false;
        helper.goingToWell = true;
    }

    bool reachedTarget = false;
    if (helper.goingToWell) {
        float dx = helper.targetPos.x - helper.pos.x;
        float dy = helper.targetPos.y - helper.pos.y;
        float dist = sqrtf(dx*dx + dy*dy);
        if (dist <= 8.0f) {
            reachedTarget = true;
            helper.waterCount = helper.maxWater;
            helper.goingToWell = false;

            SpawnGameParticle(game, { 2.0f * TILE_SIZE, 11.0f * TILE_SIZE });
            PlaySound(game.wellSnd);
        }
    } else if (helper.hasTarget && helper.targetFireIdx != -1) {

        if (!game.fires[helper.targetFireIdx].active) {
            helper.hasTarget = false;
            helper.targetFireIdx = -1;
        } else if (CheckCollisionRecs(npcRec, game.fires[helper.targetFireIdx].rec)) {

            reachedTarget = true;
            game.fires[helper.targetFireIdx].active = false;
            helper.waterCount--;
            helper.hasTarget = false;
            helper.targetFireIdx = -1;
            game.score += 50;
            PlaySound(game.extinguishSnd);
        }
    }

    if (!reachedTarget) {
        float dx = helper.targetPos.x - helper.pos.x;
        float dy = helper.targetPos.y - helper.pos.y;
        float dist = sqrtf(dx*dx + dy*dy);

        if (dist > 5.0f) {
            float vx = dx / dist;
            float vy = dy / dist;

            bool pathBlocked = false;
            Vector2 futurePos = { helper.pos.x + vx * 25.0f, helper.pos.y + vy * 25.0f };
            Rectangle futureRec = { futurePos.x, futurePos.y, 32.0f, 32.0f };

            for (int i = 0; i < 150; i++) {
                if (i == helper.targetFireIdx) continue;
                if (game.fires[i].active && CheckCollisionRecs(futureRec, game.fires[i].rec)) {
                    pathBlocked = true;
                    break;
                }
            }

            if (pathBlocked) {
                bool evadedDown = false;

                Vector2 downPos = { helper.pos.x, helper.pos.y + 25.0f };
                Rectangle downRec = { downPos.x, downPos.y, 32.0f, 32.0f };
                bool downBlocked = false;

                for (int i = 0; i < 150; i++) {
                    if (game.fires[i].active && CheckCollisionRecs(downRec, game.fires[i].rec)) {
                        downBlocked = true;
                        break;
                    }
                }

                if (!downBlocked && helper.pos.y < (GRID_ROWS - 2) * TILE_SIZE) {
                    vx = 0.0f;
                    vy = 1.0f;
                    evadedDown = true;
                }

                if (!evadedDown) {

                    float rx = -vy;
                    float ry = vx;
                    Vector2 tryPos1 = { helper.pos.x + rx * 25.0f, helper.pos.y + ry * 25.0f };
                    Rectangle tryRec1 = { tryPos1.x, tryPos1.y, 32.0f, 32.0f };
                    bool blocked1 = false;
                    for (int i = 0; i < 150; i++) {
                        if (i == helper.targetFireIdx) continue;
                        if (game.fires[i].active && CheckCollisionRecs(tryRec1, game.fires[i].rec)) {
                            blocked1 = true;
                            break;
                        }
                    }

                    float lx = vy;
                    float ly = -vx;
                    Vector2 tryPos2 = { helper.pos.x + lx * 25.0f, helper.pos.y + ly * 25.0f };
                    Rectangle tryRec2 = { tryPos2.x, tryPos2.y, 32.0f, 32.0f };
                    bool blocked2 = false;
                    for (int i = 0; i < 150; i++) {
                        if (i == helper.targetFireIdx) continue;
                        if (game.fires[i].active && CheckCollisionRecs(tryRec2, game.fires[i].rec)) {
                            blocked2 = true;
                            break;
                        }
                    }

                    if (!blocked1) {
                        vx = rx;
                        vy = ry;
                    } else if (!blocked2) {
                        vx = lx;
                        vy = ly;
                    } else {

                        vx = -vx * 0.5f;
                        vy = -vy * 0.5f;
                    }
                }
            }

            helper.isMoving = (vx != 0.0f || vy != 0.0f);
            if (helper.isMoving) {
                if (fabsf(vx) > fabsf(vy)) {
                    helper.direction = (vx > 0.0f) ? DIR_RIGHT : DIR_LEFT;
                } else {
                    helper.direction = (vy > 0.0f) ? DIR_DOWN : DIR_UP;
                }
            }

            helper.pos.x += vx * helper.speed * dt;
            helper.pos.y += vy * helper.speed * dt;
        } else {
            helper.isMoving = false;
        }
    } else {
        helper.isMoving = false;
    }
}

void DrawHelperNPC(const NPC& helper, const Game& game) {
    if (!helper.active) return;

    Rectangle destRec = { helper.pos.x - 4, helper.pos.y - 12, 40.0f, 40.0f };

    if (game.npcMovTex.id > 0) {

        int row = (helper.direction == DIR_UP) ? 0 :
                  (helper.direction == DIR_DOWN) ? 1 :
                  (helper.direction == DIR_RIGHT) ? 2 : 3;

        int col = 0;
        if (helper.isMoving) {
            if (row == 3) {

                int animStep = (int)(GetTime() * 8.0f) % 3;
                col = (animStep == 0) ? 0 : (animStep == 1) ? 2 : 3;
            } else {

                col = (int)(GetTime() * 8.0f) % 4;
            }
        }

        float srcX = (float)col * 703.5f + 231.75f;
        float srcY = (float)row * 384.0f + 32.0f;
        Rectangle sourceRec = { srcX, srcY, 240.0f, 320.0f };

        DrawTexturePro(game.npcMovTex, sourceRec, destRec, { 0.0f, 0.0f }, 0.0f, WHITE);
    }
    else {

        Rectangle npcRec = { helper.pos.x, helper.pos.y, 32.0f, 32.0f };
        DrawRectangleRec(npcRec, LIME);
        DrawRectangleLinesEx(npcRec, 2.0f, GREEN);

        DrawCircle(helper.pos.x + 16, helper.pos.y + 16, 9.0f, DARKGRAY);
        DrawCircle(helper.pos.x + 16, helper.pos.y + 16, 5.0f, LIME);
    }

    DrawText("NPC", helper.pos.x - 15, helper.pos.y - 12, 10, GREEN);

    if (helper.waterCount > 0) {
        for (int w = 0; w < helper.waterCount; w++) {
            DrawCircle(helper.pos.x + 2 + w * 4, helper.pos.y + 36, 2.5f, SKYBLUE);
        }
    } else {
        DrawText("SIN AGUA!", helper.pos.x - 10, helper.pos.y + 34, 9, RED);
    }
}
