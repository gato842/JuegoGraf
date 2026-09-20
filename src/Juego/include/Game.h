#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "Player.h"
#include "Fire.h"
#include "Bucket.h"
#include "WaterBeam.h"
#include "HelperNPC.h"
#include "HighScore.h"
#include "Menu.h"
#include "Credits.h"
#include "TextureUtils.h"

struct GameParticle {
    Vector2 pos;
    bool active;
    float timer;
};

struct Game {
    GameScreen currentScreen;
    Player player;
    NPC helper;
    Fire fires[150];
    PlacedBucket placedBuckets[3];
    WaterBeam waterBeams[30];
    Vector2 waterSourcePos;

    GameParticle particles[50];
    Texture2D particleTex;

    GridCell grid[GRID_COLS][GRID_ROWS];

    int campoMinX;
    int campoMaxX;
    float expandTimer;

    float envDamage;
    float levelTimer;
    int score;
    int firesExtinguished;
    int targetFires;
    float hoseShootCooldown;

    int currentDialogueIndex;
    float windAnimTimer;
    float truckAnimTimer;

    Texture2D playerTex;
    Texture2D playerStaticTex;
    Texture2D playerMovAbaTex;
    Texture2D playerMovArrTex;
    Texture2D playerMovDerTex;
    Texture2D playerMovIzqTex;
    Texture2D fireTex;
    Texture2D fireStage1Tex;
    Texture2D fireStage2Tex;
    Texture2D fireStage3Tex;
    Texture2D ashTex;
    Texture2D bucketTex;
    Texture2D sourceTex;
    Texture2D houseTex;
    Texture2D bgTex;
    Texture2D bgLvl1Tex;
    Texture2D bgLvl2Tex;
    Texture2D geminiTexs[5];
    Texture2D fatherSprite;
    Texture2D sonSprite;
    Texture2D firefighterSprite;
    Texture2D truckSprite;
    Texture2D npcMovTex;
    Texture2D grassTex;

    Sound wellSnd;
    Sound placeBucketSnd;
    Sound extinguishSnd;
    Sound fireLvl1Snd;
    Sound fireLvl2Snd;

    HighScoreRecord highScores[10];
    int highScoreCount;
};

void InitGame(Game& game);
void UpdateGame(Game& game);
void DrawGame(const Game& game);
void UnloadGameAssets(Game& game);
void SpawnGameParticle(Game& game, Vector2 pos);

#endif
