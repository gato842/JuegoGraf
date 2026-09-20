#include "../include/Intro.h"
#include "../include/Game.h"
#include "../include/Level1.h"
#include "../include/Level2.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

static const DialogueLine introLvl1Dialogue[] = {
    { "Padre", "Hijo, hoy limpiaremos esta maleza seca con una quema controlada. La sequia es peligrosa y esto evitara incendios mayores.", 0, 1 },
    { "Hijo", "¡Si, papa! Ya prepare el cortafuegos alrededor del campo y tengo los baldes de agua listos por si acaso.", 0, 2 },
    { "Narrador", "Comienzan a quemar la hierba seca de forma controlada dentro del perimetro establecido...", 1, 0 },
    { "Hijo", "¡Papa, mira! ¡El viento soplo una chispa hacia ese arbusto seco de afuera del perimetro!", 2, 2 },
    { "Padre", "¡No! ¡Esa zona no la previmos y el viento esta cambiando de direccion! ¡Rapido, usa los baldes de agua para controlarlo antes de que llegue a los vecinos!", 2, 4 },
    { "Narrador", "[ PRESIONA ESPACIO O ENTER PARA INICIAR LA DEFENSA DEL CAMPO ]", 2, 0 }
};
static const int introLvl1Count = sizeof(introLvl1Dialogue) / sizeof(introLvl1Dialogue[0]);

static const DialogueLine introLvl2Dialogue[] = {
    { "Narrador", "Aunque lograron contener las llamas principales del campo de cultivo, las cenizas seguian calientes...", 2, 0 },
    { "Narrador", "De repente, una fuerte rafaga de viento avivo las brasas y expandio chispas hacia las laderas altas vecinas...", 3, 0 },
    { "Hijo", "¡Papa! ¡El fuego corrio por la colina debido al viento y se dirige directo a las casas de los vecinos!", 3, 2 },
    { "Padre", "¡Esto es demasiado grande para nosotros! ¡Rapido, saca el telefono y llama a emergencias!", 3, 1 },
    { "Hijo", "¡Alo, Bomberos! ¡Se descontroló una quema en la Cordillera de Sama! ¡El fuego avanza hacia las viviendas!", 3, 2 },
    { "Narrador", "Unos minutos despues, el sonido fuerte de las sirenas anuncia la llegada de ayuda...", 4, 0 },
    { "Bombero", "¡Ya estamos aqui! La situacion es critica en la zona alta de las casas. Subanse al camion, los llevaremos y les prestaremos una manguera de alta presion.", 4, 3 },
    { "Padre", "¡Entendido! ¡Vamos rapido, salvemos las casas de la comunidad!", 4, 4 },
    { "Narrador", "[ PRESIONA ESPACIO O ENTER PARA COMENZAR A USAR LA MANGUERA DE ALTA PRESION ]", 4, 0 }
};
static const int introLvl2Count = sizeof(introLvl2Dialogue) / sizeof(introLvl2Dialogue[0]);

void StartIntroLvl1(Game& game) {
    game.currentScreen = SCREEN_INTRO_LVL1;
    game.currentDialogueIndex = 0;
    game.windAnimTimer = 0.0f;
    game.truckAnimTimer = 0.0f;
}

void StartIntroLvl2(Game& game) {
    game.currentScreen = SCREEN_INTRO_LVL2;
    game.currentDialogueIndex = 0;
    game.windAnimTimer = 0.0f;
    game.truckAnimTimer = 0.0f;
}

void UpdateIntro(Game& game, float dt) {

    game.windAnimTimer += dt;
    game.truckAnimTimer += dt;

    const DialogueLine* currentScript = (game.currentScreen == SCREEN_INTRO_LVL1) ? introLvl1Dialogue : introLvl2Dialogue;
    int maxLines = (game.currentScreen == SCREEN_INTRO_LVL1) ? introLvl1Count : introLvl2Count;

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game.currentDialogueIndex++;
        if (game.currentDialogueIndex >= maxLines) {
            if (game.currentScreen == SCREEN_INTRO_LVL1) {
                StartLevel1(game);
            } else {
                StartLevel2(game);
            }
        }
    }
}

static void DrawProceduralFather(float x, float y) {

    DrawRectangle(x - 20, y - 50, 40, 70, BLUE);
    DrawRectangle(x - 25, y - 50, 50, 25, RED);

    DrawCircle(x, y - 65, 18, { 235, 180, 140, 255 });

    DrawCircle(x - 10, y - 60, 6, GRAY);
    DrawCircle(x + 10, y - 60, 6, GRAY);
    DrawCircle(x, y - 56, 8, GRAY);
    DrawRectangle(x - 12, y - 62, 24, 8, GRAY);

    DrawCircle(x - 6, y - 68, 2.5f, BLACK);
    DrawCircle(x + 6, y - 68, 2.5f, BLACK);

    DrawEllipse(x, y - 76, 32, 10, BROWN);
    DrawRectangle(x - 16, y - 92, 32, 16, BROWN);
    DrawRectangle(x - 16, y - 82, 32, 5, GOLD);
}

static void DrawProceduralSon(float x, float y) {

    DrawRectangle(x - 15, y - 40, 30, 55, BLUE);
    DrawRectangle(x - 20, y - 40, 40, 20, ORANGE);

    DrawCircle(x, y - 52, 15, { 235, 180, 140, 255 });

    DrawCircle(x - 5, y - 54, 2.0f, BLACK);
    DrawCircle(x + 5, y - 54, 2.0f, BLACK);
    DrawLine(x - 4, y - 48, x + 4, y - 48, RED);

    DrawEllipse(x, y - 60, 26, 8, BROWN);
    DrawRectangle(x - 12, y - 73, 24, 13, BROWN);
    DrawRectangle(x - 12, y - 65, 24, 4, YELLOW);
}

static void DrawProceduralFirefighter(float x, float y) {

    DrawRectangle(x - 22, y - 50, 44, 70, { 30, 30, 30, 255 });
    DrawRectangle(x - 22, y - 40, 44, 6, YELLOW);
    DrawRectangle(x - 22, y - 20, 44, 6, YELLOW);

    DrawCircle(x, y - 65, 18, { 235, 180, 140, 255 });

    DrawCircle(x - 6, y - 68, 2.5f, BLACK);
    DrawCircle(x + 6, y - 68, 2.5f, BLACK);

    DrawEllipse(x, y - 76, 28, 7, RED);
    DrawRectangle(x - 14, y - 90, 28, 14, RED);
    DrawTriangle({ x - 8, y - 88 }, { x + 8, y - 88 }, { x, y - 98 }, YELLOW);
    DrawRectangle(x - 18, y - 76, 36, 4, { 50, 50, 50, 255 });
}

void DrawIntro(const Game& game) {
    const DialogueLine* currentScript = (game.currentScreen == SCREEN_INTRO_LVL1) ? introLvl1Dialogue : introLvl2Dialogue;
    const DialogueLine& line = currentScript[game.currentDialogueIndex];

    bool drawFallbackBg = true;
    if (line.bgIndex >= 0 && line.bgIndex < 5) {
        if (game.geminiTexs[line.bgIndex].id > 0) {
            DrawTexturePro(game.geminiTexs[line.bgIndex],
                { 0.0f, 0.0f, (float)game.geminiTexs[line.bgIndex].width, (float)game.geminiTexs[line.bgIndex].height },
                { 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT },
                { 0.0f, 0.0f }, 0.0f, WHITE);
            drawFallbackBg = false;
        }
    }

    if (drawFallbackBg) {

        if (game.currentScreen == SCREEN_INTRO_LVL1) {
            if (line.bgIndex == 0) {

                DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 30, 80, 40, 255 }, { 10, 40, 20, 255 });
                DrawCircle(100, 100, 40, YELLOW);
            } else if (line.bgIndex == 1) {

                DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 50, 80, 50, 255 }, { 30, 50, 30, 255 });

                for (int i = 0; i < 6; i++) {
                    DrawCircle(200 + i * 80, 350 - (i % 2) * 30, 40 + i * 5, { 100, 100, 100, 100 });
                }
            } else {

                DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 120, 40, 20, 255 }, { 40, 10, 5, 255 });

                for (int x = 0; x < SCREEN_WIDTH; x += 40) {
                    DrawTriangle({ (float)x, (float)SCREEN_HEIGHT - 100 }, { (float)x + 40, (float)SCREEN_HEIGHT - 100 }, { (float)x + 20, (float)SCREEN_HEIGHT - 180 + (x % 3) * 20 }, ORANGE);
                }
            }
        } else {

            if (line.bgIndex == 2 || line.bgIndex == 3) {

                DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 140, 30, 10, 255 }, { 50, 10, 5, 255 });

                DrawRectangle(450, SCREEN_HEIGHT - 220, 80, 80, DARKGRAY);
                DrawTriangle({ 440, SCREEN_HEIGHT - 220 }, { 540, SCREEN_HEIGHT - 220 }, { 490, SCREEN_HEIGHT - 270 }, RED);
                DrawRectangle(580, SCREEN_HEIGHT - 200, 70, 70, DARKGRAY);
                DrawTriangle({ 570, SCREEN_HEIGHT - 200 }, { 660, SCREEN_HEIGHT - 200 }, { 615, SCREEN_HEIGHT - 245 }, RED);

                for (int x = 400; x < SCREEN_WIDTH; x += 50) {
                    DrawTriangle({ (float)x, (float)SCREEN_HEIGHT - 120 }, { (float)x + 50, (float)SCREEN_HEIGHT - 120 }, { (float)x + 25, (float)SCREEN_HEIGHT - 240 + (x % 4) * 30 }, ORANGE);
                }
            } else {

                DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 80, 30, 10, 255 }, { 20, 5, 5, 255 });
            }
        }
    }

    if (game.currentScreen == SCREEN_INTRO_LVL2) {

        if (game.currentDialogueIndex == 1 || game.currentDialogueIndex == 2) {
            float windOffset = fmodf(game.windAnimTimer * 500.0f, SCREEN_WIDTH + 300.0f) - 200.0f;
            for (int i = 0; i < 5; i++) {
                float y = 100.0f + i * 90.0f + sinf(game.windAnimTimer * 3.0f + i) * 20.0f;
                DrawLineEx({ windOffset - 100.0f, y }, { windOffset + 150.0f, y }, 4.0f, { 255, 255, 255, 120 });

                DrawCircle(windOffset + 80.0f, y - 10.0f, 3.0f, ORANGE);
                DrawCircle(windOffset - 30.0f, y + 15.0f, 4.0f, RED);
            }
        }

        if (game.currentDialogueIndex >= 5 && game.currentDialogueIndex <= 7) {

            float truckX = -300.0f + (game.truckAnimTimer * 400.0f);
            if (truckX > 80.0f) truckX = 80.0f;

            float truckY = SCREEN_HEIGHT - 300.0f;

            if (game.truckSprite.id > 0) {

                DrawTexturePro(game.truckSprite,
                    { 0.0f, 0.0f, (float)game.truckSprite.width, (float)game.truckSprite.height },
                    { truckX, truckY - 20.0f, 320.0f, 160.0f },
                    { 0.0f, 0.0f }, 0.0f, WHITE);

                Color sirenColor = (((int)(game.truckAnimTimer * 8.0f) % 2) == 0)
                    ? (Color){ 0, 100, 255, 140 }
                    : (Color){ 255, 30, 30, 140 };
                DrawCircle(truckX + 90, truckY - 28, 14, sirenColor);
            } else {

                DrawRectangle(truckX, truckY, 200, 70, RED);
                DrawRectangle(truckX + 140, truckY + 20, 60, 50, RED);
                DrawRectangle(truckX + 160, truckY + 25, 30, 20, SKYBLUE);
                DrawCircle(truckX + 40, truckY + 70, 16, BLACK);
                DrawCircle(truckX + 150, truckY + 70, 16, BLACK);
                DrawRectangle(truckX + 20, truckY + 15, 100, 15, GRAY);
                DrawRectangle(truckX + 10, truckY - 5, 20, 10, { 200, 200, 200, 255 });
                DrawRectangle(truckX + 40, truckY - 5, 20, 10, { 200, 200, 200, 255 });

                if (((int)(game.truckAnimTimer * 8.0f) % 2) == 0) {
                    DrawCircle(truckX + 175, truckY + 15, 10, BLUE);
                    DrawCircle(truckX + 175, truckY + 15, 6, LIGHTGRAY);
                } else {
                    DrawCircle(truckX + 175, truckY + 15, 10, RED);
                    DrawCircle(truckX + 175, truckY + 15, 6, LIGHTGRAY);
                }
            }
        }
    }

    float spriteY = SCREEN_HEIGHT - 190.0f;
    if (line.spriteIndex == 1) {
        if (game.fatherSprite.id > 0) {
            DrawTexturePro(game.fatherSprite,
                { 0.0f, 0.0f, (float)game.fatherSprite.width, (float)game.fatherSprite.height },
                { SCREEN_WIDTH / 2.0f - 100.0f, spriteY - 80.0f, 200.0f, 200.0f },
                { 0.0f, 0.0f }, 0.0f, WHITE);
        } else {
            DrawProceduralFather(SCREEN_WIDTH / 2.0f, spriteY + 40.0f);
        }
    } else if (line.spriteIndex == 2) {
        if (game.sonSprite.id > 0) {
            DrawTexturePro(game.sonSprite,
                { 0.0f, 0.0f, (float)game.sonSprite.width, (float)game.sonSprite.height },
                { SCREEN_WIDTH / 2.0f - 100.0f, spriteY - 80.0f, 200.0f, 200.0f },
                { 0.0f, 0.0f }, 0.0f, WHITE);
        } else {
            DrawProceduralSon(SCREEN_WIDTH / 2.0f, spriteY + 45.0f);
        }
    } else if (line.spriteIndex == 3) {
        if (game.firefighterSprite.id > 0) {
            DrawTexturePro(game.firefighterSprite,
                { 0.0f, 0.0f, (float)game.firefighterSprite.width, (float)game.firefighterSprite.height },
                { SCREEN_WIDTH / 2.0f + 20.0f, spriteY - 80.0f, 200.0f, 200.0f },
                { 0.0f, 0.0f }, 0.0f, WHITE);
        } else {
            DrawProceduralFirefighter(SCREEN_WIDTH / 2.0f + 120.0f, spriteY + 40.0f);
        }
    } else if (line.spriteIndex == 4) {
        if (game.fatherSprite.id > 0) {
            DrawTexturePro(game.fatherSprite,
                { 0.0f, 0.0f, (float)game.fatherSprite.width, (float)game.fatherSprite.height },
                { SCREEN_WIDTH / 2.0f - 120.0f, spriteY - 80.0f, 200.0f, 200.0f },
                { 0.0f, 0.0f }, 0.0f, WHITE);
        } else {
            DrawProceduralFather(SCREEN_WIDTH / 2.0f - 60.0f, spriteY + 40.0f);
        }

        if (game.sonSprite.id > 0) {
            DrawTexturePro(game.sonSprite,
                { 0.0f, 0.0f, (float)game.sonSprite.width, (float)game.sonSprite.height },
                { SCREEN_WIDTH / 2.0f + 20.0f, spriteY - 80.0f, 200.0f, 200.0f },
                { 0.0f, 0.0f }, 0.0f, WHITE);
        } else {
            DrawProceduralSon(SCREEN_WIDTH / 2.0f + 60.0f, spriteY + 45.0f);
        }
    }

    float boxWidth = SCREEN_WIDTH - 60.0f;
    float boxHeight = 135.0f;
    float boxX = 30.0f;
    float boxY = SCREEN_HEIGHT - boxHeight - 20.0f;

    DrawRectangle(boxX - 2, boxY - 2, boxWidth + 4, boxHeight + 4, ORANGE);
    DrawRectangle(boxX, boxY, boxWidth, boxHeight, { 15, 20, 30, 240 });

    if (line.speaker && strcmp(line.speaker, "Narrador") != 0) {
        float labelWidth = MeasureText(line.speaker, 16) + 30.0f;
        float labelHeight = 30.0f;
        float labelX = boxX + 15.0f;
        float labelY = boxY - 20.0f;

        DrawRectangle(labelX - 1, labelY - 1, labelWidth + 2, labelHeight + 2, GOLD);
        DrawRectangle(labelX, labelY, labelWidth, labelHeight, { 35, 45, 65, 255 });
        DrawText(line.speaker, labelX + 15, labelY + 6, 16, YELLOW);
    }

    int textFontSize = 15;
    Color textColor = (strcmp(line.speaker, "Narrador") == 0) ? GOLD : WHITE;

    char wrapBuffer[512];
    snprintf(wrapBuffer, sizeof(wrapBuffer), "%s", line.text);

    float startTextX = boxX + 25.0f;
    float startTextY = boxY + 25.0f;
    if (line.speaker && strcmp(line.speaker, "Narrador") != 0) {
        startTextY += 10.0f;
    }

    int charIdx = 0;
    int lineOffset = 0;
    char lineBuffer[128] = "";
    int lineCharCount = 0;

    for (int i = 0; wrapBuffer[i] != '\0'; i++) {
        lineBuffer[lineCharCount++] = wrapBuffer[i];
        lineBuffer[lineCharCount] = '\0';

        if (MeasureText(lineBuffer, textFontSize) > boxWidth - 50.0f || wrapBuffer[i] == '\n') {

            int lastSpace = -1;
            for (int j = lineCharCount - 1; j >= 0; j--) {
                if (lineBuffer[j] == ' ') {
                    lastSpace = j;
                    break;
                }
            }

            if (lastSpace != -1 && wrapBuffer[i] != '\n') {

                lineBuffer[lastSpace] = '\0';
                DrawText(lineBuffer, startTextX, startTextY + lineOffset * 22, textFontSize, textColor);

                i -= (lineCharCount - 1 - lastSpace);
            } else {
                DrawText(lineBuffer, startTextX, startTextY + lineOffset * 22, textFontSize, textColor);
            }

            lineCharCount = 0;
            lineBuffer[0] = '\0';
            lineOffset++;
        }
    }

    if (lineCharCount > 0) {
        DrawText(lineBuffer, startTextX, startTextY + lineOffset * 22, textFontSize, textColor);
    }

    if (((int)(game.windAnimTimer * 2.0f) % 2) == 0) {
        DrawText("[ Haz clic o ESPACIO para avanzar ]", boxX + boxWidth - 235, boxY + boxHeight - 20, 11, SKYBLUE);
    }
}
