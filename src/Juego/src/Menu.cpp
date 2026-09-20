#include "../include/Menu.h"
#include "../include/Game.h"
#include "../include/Level1.h"
#include "../include/Intro.h"

void UpdateMenu(Game& game, float dt) {
    if (IsKeyPressed(KEY_ENTER)) {
        game.score = 0;
        StartIntroLvl1(game);
    }
    if (IsKeyPressed(KEY_C)) {
        game.currentScreen = SCREEN_CREDITS;
    }
    if (IsKeyPressed(KEY_H)) {
        game.currentScreen = SCREEN_HIGHSCORES;
    }
}

void DrawMenu(const Game& game) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 10, 25, 10, 230 });

    DrawText("SAMA FIRE RESCUE", SCREEN_WIDTH/2 - MeasureText("SAMA FIRE RESCUE", 40)/2, 120, 40, ORANGE);
    DrawText("Combate el incendio de la Cordillera de Sama", SCREEN_WIDTH/2 - MeasureText("Combate el incendio de la Cordillera de Sama", 20)/2, 180, 20, YELLOW);

    DrawRectangleLines(SCREEN_WIDTH/2 - 180, 250, 360, 180, ORANGE);
    DrawText("INSTRUCCIONES:", SCREEN_WIDTH/2 - 160, 270, 16, WHITE);
    DrawText("- Moverse: WASD / Flechas de Direccion", SCREEN_WIDTH/2 - 160, 300, 14, LIGHTGRAY);
    DrawText("- Nivel 1: Recarga agua en pozo. Coloca baldes [B]", SCREEN_WIDTH/2 - 160, 325, 14, LIGHTGRAY);
    DrawText("  para bloquear fuego o apaga frente [SPACE].", SCREEN_WIDTH/2 - 160, 345, 14, LIGHTGRAY);
    DrawText("- Nivel 2: Usa la manguera de alta presion [SPACE]", SCREEN_WIDTH/2 - 160, 370, 14, LIGHTGRAY);
    DrawText("  para salvar las casas de los vecinos abajo.", SCREEN_WIDTH/2 - 160, 390, 14, LIGHTGRAY);

    DrawText("[ PRESIONA ENTER PARA INICIAR ]", SCREEN_WIDTH/2 - MeasureText("[ PRESIONA ENTER PARA INICIAR ]", 20)/2, 465, 20, GREEN);
    DrawText("[ PRESIONA C PARA VER LOS CREDITOS ]", SCREEN_WIDTH/2 - MeasureText("[ PRESIONA C PARA VER LOS CREDITOS ]", 16)/2, 505, 16, SKYBLUE);
    DrawText("[ PRESIONA H PARA VER LOS MEJORES PUNTAJES ]", SCREEN_WIDTH/2 - MeasureText("[ PRESIONA H PARA VER LOS MEJORES PUNTAJES ]", 16)/2, 538, 16, GOLD);
}
