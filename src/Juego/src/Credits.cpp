#include "../include/Credits.h"
#include "../include/Game.h"

void UpdateCredits(Game& game, float dt) {
    if (IsKeyPressed(KEY_ENTER)) {
        game.currentScreen = SCREEN_MENU;
    }
}

void DrawCredits(const Game& game) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 15, 15, 30, 240 });
    DrawText("CREDITOS", SCREEN_WIDTH/2 - MeasureText("CREDITOS", 32)/2, 100, 32, GOLD);

    DrawText("Desarrollado para la materia de Programacion Grafica", SCREEN_WIDTH/2 - MeasureText("Desarrollado para la materia de Videojuegos", 18)/2, 200, 18, WHITE);
    DrawText("Inspirado en la prevencion de incendios en Sama, Tarija", SCREEN_WIDTH/2 - MeasureText("Inspirado en la prevencion de incendios en Sama, Tarija", 18)/2, 240, 18, LIGHTGRAY);

    DrawText("Motor Grafico: Raylib (C++)", SCREEN_WIDTH/2 - MeasureText("Motor Grafico: Raylib (C++)", 16)/2, 320, 16, SKYBLUE);
    DrawText("Autor: Axel Elvis Irahola Gallardo y Adrian Samuel Arancibia Mendoza", SCREEN_WIDTH/2 - MeasureText("Autor: Axel Elvis Irahola Gallardo y Adrian Samuel Arancibia Mendoza", 16)/2, 360, 16, LIGHTGRAY);

    DrawText("[ PRESIONA ENTER PARA VOLVER AL MENU ]", SCREEN_WIDTH/2 - MeasureText("[ PRESIONA ENTER PARA VOLVER AL MENU ]", 16)/2, 480, 16, WHITE);
}
