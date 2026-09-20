#include "../include/Game.h"
#include "../include/Level1.h"
#include "../include/Level2.h"
#include "../include/Intro.h"
#include <stdio.h>

void InitGame(Game& game) {

    game.envDamage = 0.0f;
    game.score = 0;
    game.levelTimer = 35.0f;

    LoadHighScores(game);
    game.currentScreen = SCREEN_MENU;

    game.firesExtinguished = 0;
    game.targetFires = 5;
    game.hoseShootCooldown = 0.0f;
    game.waterSourcePos = { 2.0f, 3.0f };

    game.playerStaticTex = LoadCustomGameTexture("src/Juego/resources/estatico.png", 4128, 1024);
    game.playerMovAbaTex = LoadCustomGameTexture("src/Juego/resources/movAba.png", 4128, 1024);
    game.playerMovArrTex = LoadCustomGameTexture("src/Juego/resources/movArr.png", 4128, 1024);
    game.playerMovDerTex = LoadCustomGameTexture("src/Juego/resources/movDer.png", 1344, 768);
    game.playerMovIzqTex = LoadCustomGameTexture("src/Juego/resources/movIzq.png", 4128, 1024);
    game.playerTex = game.playerStaticTex;

    game.fireTex = LoadCustomGameTexture("src/Juego/resources/fire2.png", 2048, 2048);
    game.fireStage1Tex = LoadCustomGameTexture("src/Juego/resources/fire_stage1.png", 4128, 1024);
    game.fireStage2Tex = LoadCustomGameTexture("src/Juego/resources/fire_stage2.png", 4128, 1024);
    game.fireStage3Tex = LoadCustomGameTexture("src/Juego/resources/fire_stage3.png", 516, 128);
    game.ashTex = LoadCustomGameTexture("src/Juego/resources/ashes.png", 352, 192);
    game.bucketTex = LoadCustomGameTexture("src/Juego/resources/bucket.png", 40, 40);
    game.sourceTex = LoadCustomGameTexture("src/Juego/resources/well.png", 516, 128);
    game.houseTex = LoadCustomGameTexture("src/Juego/resources/house.png", 40, 40);
    game.npcMovTex = LoadCustomGameTexture("src/Juego/resources/movPadre.png", 2814, 1536);
    game.grassTex = LoadCustomGameTexture("src/Juego/resources/grass2.png", 1800, 600);

    game.wellSnd = LoadCustomGameSound("src/Juego/resources/Burbujas.mp3");
    game.placeBucketSnd = LoadCustomGameSound("src/Juego/resources/aguaPlop.mp3");
    game.extinguishSnd = LoadCustomGameSound("src/Juego/resources/extincion.mp3");
    game.fireLvl1Snd = LoadCustomGameSound("src/Juego/resources/fuego2.mp3");
    game.fireLvl2Snd = LoadCustomGameSound("src/Juego/resources/fuego1.mp3");
    game.bgLvl1Tex = LoadCustomGameTexture("src/Juego/resources/texturaLVL1.png", 800, 600);
    if (game.bgLvl1Tex.id == 0) {
        game.bgLvl1Tex = LoadCustomGameTexture("src/Juego/resources/background.png", 800, 600);
    }
    game.bgLvl2Tex = LoadCustomGameTexture("src/Juego/resources/texturaLVL2.png", 800, 600);
    game.bgTex = game.bgLvl1Tex;

    game.particleTex = LoadCustomGameTexture("src/Juego/resources/part1.png", 2398, 1792);

    game.grassTex = LoadCustomGameTexture("src/Juego/resources/grass2.png", 2400, 1790);

    for (int i = 0; i < 50; i++) {
        game.particles[i].active = false;
    }

    game.currentDialogueIndex = 0;
    game.windAnimTimer = 0.0f;
    game.truckAnimTimer = 0.0f;

    game.geminiTexs[0] = LoadCustomGameTexture("src/Juego/Gemini_Generated_Image_8mqr7z8mqr7z8mqr.png", 800, 600);
    game.geminiTexs[1] = LoadCustomGameTexture("src/Juego/Gemini_Generated_Image_rlbn0rrlbn0rrlbn.png", 800, 600);
    game.geminiTexs[2] = LoadCustomGameTexture("src/Juego/Gemini_Generated_Image_1r5v831r5v831r5v.png", 800, 600);
    game.geminiTexs[3] = LoadCustomGameTexture("src/Juego/Gemini_Generated_Image_ocsaobocsaobocsa.png", 800, 600);
    game.geminiTexs[4] = LoadCustomGameTexture("src/Juego/Gemini_Generated_Image_43sqf643sqf643sq.png", 800, 600);

    game.fatherSprite       = LoadCustomGameTexture("src/Juego/resources/padre.png", 1407, 768);
    game.sonSprite          = LoadCustomGameTexture("src/Juego/resources/hijo.png", 1407, 768);
    game.firefighterSprite  = LoadCustomGameTexture("src/Juego/resources/bombero.png", 1407, 768);
    game.truckSprite        = LoadCustomGameTexture("src/Juego/resources/camion.png", 1407, 768);

    InitPlayer(game.player);
    InitFires(game.fires, 150);
    InitPlacedBuckets(game.placedBuckets, 3);
    InitWaterBeams(game.waterBeams, 30);
}

void UnloadGameAssets(Game& game) {
    if (game.playerStaticTex.id > 0) UnloadTexture(game.playerStaticTex);
    if (game.playerMovAbaTex.id > 0) UnloadTexture(game.playerMovAbaTex);
    if (game.playerMovArrTex.id > 0) UnloadTexture(game.playerMovArrTex);
    if (game.playerMovDerTex.id > 0) UnloadTexture(game.playerMovDerTex);
    if (game.playerMovIzqTex.id > 0) UnloadTexture(game.playerMovIzqTex);
    if (game.fireTex.id > 0) UnloadTexture(game.fireTex);
    if (game.fireStage1Tex.id > 0) UnloadTexture(game.fireStage1Tex);
    if (game.fireStage2Tex.id > 0) UnloadTexture(game.fireStage2Tex);
    if (game.fireStage3Tex.id > 0) UnloadTexture(game.fireStage3Tex);
    if (game.ashTex.id > 0) UnloadTexture(game.ashTex);
    if (game.bucketTex.id > 0) UnloadTexture(game.bucketTex);
    if (game.sourceTex.id > 0) UnloadTexture(game.sourceTex);
    if (game.houseTex.id > 0) UnloadTexture(game.houseTex);
    if (game.bgLvl1Tex.id > 0) UnloadTexture(game.bgLvl1Tex);
    if (game.bgLvl2Tex.id > 0) UnloadTexture(game.bgLvl2Tex);
    if (game.particleTex.id > 0) UnloadTexture(game.particleTex);
    if (game.npcMovTex.id > 0) UnloadTexture(game.npcMovTex);
    if (game.grassTex.id > 0) UnloadTexture(game.grassTex);

    if (game.wellSnd.frameCount > 0) UnloadSound(game.wellSnd);
    if (game.placeBucketSnd.frameCount > 0) UnloadSound(game.placeBucketSnd);
    if (game.extinguishSnd.frameCount > 0) UnloadSound(game.extinguishSnd);
    if (game.fireLvl1Snd.frameCount > 0) UnloadSound(game.fireLvl1Snd);
    if (game.fireLvl2Snd.frameCount > 0) UnloadSound(game.fireLvl2Snd);

    for (int i = 0; i < 5; i++) {
        if (game.geminiTexs[i].id > 0) UnloadTexture(game.geminiTexs[i]);
    }
    if (game.fatherSprite.id > 0)      UnloadTexture(game.fatherSprite);
    if (game.sonSprite.id > 0)         UnloadTexture(game.sonSprite);
    if (game.firefighterSprite.id > 0) UnloadTexture(game.firefighterSprite);
    if (game.truckSprite.id > 0)       UnloadTexture(game.truckSprite);
}

void UpdateGame(Game& game) {
    float dt = GetFrameTime();

    switch (game.currentScreen) {
        case SCREEN_MENU: {
            UpdateMenu(game, dt);
            break;
        }
        case SCREEN_INTRO_LVL1:
        case SCREEN_INTRO_LVL2: {
            UpdateIntro(game, dt);
            break;
        }
        case SCREEN_LEVEL1: {
            UpdateLevel1(game, dt);
            break;
        }
        case SCREEN_LEVEL2: {
            UpdateLevel2(game, dt);
            break;
        }
        case SCREEN_WIN:
        case SCREEN_LOSE: {
            if (IsKeyPressed(KEY_ENTER)) {
                if (game.currentScreen == SCREEN_WIN) {
                    game.currentScreen = SCREEN_CREDITS;
                } else {
                    game.currentScreen = SCREEN_MENU;
                }
            }
            break;
        }
        case SCREEN_CREDITS: {
            UpdateCredits(game, dt);
            break;
        }
        case SCREEN_HIGHSCORES: {
            UpdateHighScores(game);
            break;
        }
    }

    for (int i = 0; i < 50; i++) {
        if (game.particles[i].active) {
            game.particles[i].timer += dt;
            if (game.particles[i].timer >= 1.0f) {
                game.particles[i].active = false;
            }
        }
    }
}

void DrawGame(const Game& game) {
    BeginDrawing();
    ClearBackground(DARKGREEN);

    if (game.currentScreen != SCREEN_INTRO_LVL1 && game.currentScreen != SCREEN_INTRO_LVL2) {
        Texture2D activeBg = { 0 };
        if (game.currentScreen == SCREEN_LEVEL1) activeBg = game.bgLvl1Tex;
        else if (game.currentScreen == SCREEN_LEVEL2) activeBg = game.bgLvl2Tex;
        else activeBg = game.bgLvl1Tex;

        if (activeBg.id > 0) {
            DrawTexturePro(activeBg,
                { 0, 0, (float)activeBg.width, (float)activeBg.height },
                { 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT },
                { 0, 0 }, 0.0f, WHITE);
        }
    } else {

        for (int x = 0; x < SCREEN_WIDTH; x += TILE_SIZE) {
            DrawLine(x, 0, x, SCREEN_HEIGHT, { 0, 80, 0, 50 });
        }
        for (int y = 0; y < SCREEN_HEIGHT; y += TILE_SIZE) {
            DrawLine(0, y, SCREEN_WIDTH, y, { 0, 80, 0, 50 });
        }
    }

    switch (game.currentScreen) {
        case SCREEN_MENU: {
            DrawMenu(game);
            break;
        }
        case SCREEN_INTRO_LVL1:
        case SCREEN_INTRO_LVL2: {
            DrawIntro(game);
            break;
        }
        case SCREEN_LEVEL1: {
            DrawLevel1(game);
            break;
        }
        case SCREEN_LEVEL2: {
            DrawLevel2(game);
            break;
        }
        case SCREEN_WIN: {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 10, 45, 10, 240 });
            DrawText("VICTORIA", SCREEN_WIDTH/2 - MeasureText("VICTORIA", 45)/2, SCREEN_HEIGHT/2 - 100, 45, GREEN);

            DrawText("¡Has controlado la quema y salvado las casas de la Cordillera!", SCREEN_WIDTH/2 - MeasureText("¡Has controlado la quema y salvado las casas de la Cordillera!", 18)/2, SCREEN_HEIGHT/2 - 20, 18, LIGHTGRAY);

            char finalScore[50];
            sprintf(finalScore, "PUNTUACION FINAL: %d", game.score);
            DrawText(finalScore, SCREEN_WIDTH/2 - MeasureText(finalScore, 20)/2, SCREEN_HEIGHT/2 + 30, 20, YELLOW);

            DrawText("[ PRESIONA ENTER PARA VER LOS CREDITOS ]", SCREEN_WIDTH/2 - MeasureText("[ PRESIONA ENTER PARA VER LOS CREDITOS ]", 16)/2, SCREEN_HEIGHT/2 + 100, 16, WHITE);
            break;
        }
        case SCREEN_LOSE: {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 45, 10, 10, 240 });
            DrawText("INCENDIO DESCONTROLADO", SCREEN_WIDTH/2 - MeasureText("INCENDIO DESCONTROLADO", 36)/2, SCREEN_HEIGHT/2 - 100, 36, RED);

            DrawText("¡El daño ambiental supero el limite o alcanzo las casas vecinas!", SCREEN_WIDTH/2 - MeasureText("¡El daño ambiental supero el limite o alcanzo las casas vecinas!", 18)/2, SCREEN_HEIGHT/2 - 20, 18, LIGHTGRAY);

            char finalScore[50];
            sprintf(finalScore, "SCORE CONSEGUIDO: %d", game.score);
            DrawText(finalScore, SCREEN_WIDTH/2 - MeasureText(finalScore, 20)/2, SCREEN_HEIGHT/2 + 30, 20, YELLOW);

            DrawText("[ PRESIONA ENTER PARA VOLVER AL MENU ]", SCREEN_WIDTH/2 - MeasureText("[ PRESIONA ENTER PARA VOLVER AL MENU ]", 16)/2, SCREEN_HEIGHT/2 + 100, 16, WHITE);
            break;
        }
        case SCREEN_CREDITS: {
            DrawCredits(game);
            break;
        }
        case SCREEN_HIGHSCORES: {
            DrawHighScores(game);
            break;
        }
    }

    EndDrawing();
}

void SpawnGameParticle(Game& game, Vector2 pos) {
    for (int i = 0; i < 50; i++) {
        if (!game.particles[i].active) {
            game.particles[i].active = true;
            game.particles[i].pos = pos;
            game.particles[i].timer = 0.0f;
            break;
        }
    }
}
