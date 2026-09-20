#include "../include/HighScore.h"
#include "../include/Game.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void LoadHighScores(Game& game) {

    game.highScoreCount = 0;
    for (int i = 0; i < 10; i++) {
        game.highScores[i].score = 0;
        strcpy(game.highScores[i].date, "-");
    }

    FILE* file = fopen("src/Juego/resources/highscores.txt", "r");
    if (!file) {
        file = fopen("../src/Juego/resources/highscores.txt", "r");
    }
    if (!file) {
        file = fopen("../../src/Juego/resources/highscores.txt", "r");
    }

    if (file) {
        int idx = 0;
        while (idx < 10 && fscanf(file, "%d;%[^\n]\n", &game.highScores[idx].score, game.highScores[idx].date) == 2) {
            idx++;
        }
        game.highScoreCount = idx;
        fclose(file);
    }
}

void SaveHighScores(const Game& game) {
    FILE* file = fopen("src/Juego/resources/highscores.txt", "w");
    if (!file) {
        file = fopen("../src/Juego/resources/highscores.txt", "w");
    }
    if (!file) {
        file = fopen("../../src/Juego/resources/highscores.txt", "w");
    }

    if (file) {
        for (int i = 0; i < game.highScoreCount; i++) {
            fprintf(file, "%d;%s\n", game.highScores[i].score, game.highScores[i].date);
        }
        fclose(file);
    }
}

void AddHighScore(Game& game, int newScore) {

    time_t rawtime;
    struct tm * timeinfo;
    char dateStr[30];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (timeinfo) {
        strftime(dateStr, sizeof(dateStr), "%d/%m/%Y %H:%M", timeinfo);
    } else {
        strcpy(dateStr, "Fecha Desconocida");
    }

    HighScoreRecord newRecord;
    newRecord.score = newScore;
    strcpy(newRecord.date, dateStr);

    HighScoreRecord tempScores[11];
    int count = game.highScoreCount;
    for (int i = 0; i < count; i++) {
        tempScores[i] = game.highScores[i];
    }
    tempScores[count] = newRecord;
    count++;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (tempScores[j].score < tempScores[j + 1].score) {
                HighScoreRecord t = tempScores[j];
                tempScores[j] = tempScores[j + 1];
                tempScores[j + 1] = t;
            }
        }
    }

    game.highScoreCount = (count > 10) ? 10 : count;
    for (int i = 0; i < game.highScoreCount; i++) {
        game.highScores[i] = tempScores[i];
    }

    SaveHighScores(game);
}

void UpdateHighScores(Game& game) {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) {
        game.currentScreen = SCREEN_MENU;
    }
}

void DrawHighScores(const Game& game) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 10, 20, 30, 245 });

    DrawText("TABLA DE PUNTAJES (TOP 10)", SCREEN_WIDTH/2 - MeasureText("TABLA DE PUNTAJES (TOP 10)", 28)/2, 40, 28, ORANGE);
    DrawText("Cordillera de Sama - Rescates Destacados", SCREEN_WIDTH/2 - MeasureText("Cordillera de Sama - Rescates Destacados", 16)/2, 85, 16, YELLOW);

    DrawText("PUESTO", 120, 140, 14, SKYBLUE);
    DrawText("PUNTAJE", 280, 140, 14, SKYBLUE);
    DrawText("FECHA Y HORA", 480, 140, 14, SKYBLUE);
    DrawLine(100, 160, 700, 160, GRAY);

    int yStart = 180;
    for (int i = 0; i < 10; i++) {
        char numStr[10];
        sprintf(numStr, "#%02d", i + 1);

        char scoreStr[20];
        sprintf(scoreStr, "%d PTS", game.highScores[i].score);

        Color rowColor = WHITE;
        if (i == 0) rowColor = GOLD;
        else if (i == 1) rowColor = LIGHTGRAY;
        else if (i == 2) rowColor = ORANGE;

        DrawText(numStr, 120, yStart + i * 32, 14, rowColor);

        if (i < game.highScoreCount) {
            DrawText(scoreStr, 280, yStart + i * 32, 14, rowColor);
            DrawText(game.highScores[i].date, 480, yStart + i * 32, 14, rowColor);
        } else {
            DrawText("---", 280, yStart + i * 32, 14, DARKGRAY);
            DrawText("---", 480, yStart + i * 32, 14, DARKGRAY);
        }
    }

    DrawText("[ PRESIONA ENTER PARA VOLVER AL MENU ]", SCREEN_WIDTH/2 - MeasureText("[ PRESIONA ENTER PARA VOLVER AL MENU ]", 16)/2, 530, 16, GREEN);
}
