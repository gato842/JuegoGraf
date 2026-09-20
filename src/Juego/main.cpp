#include "include/Game.h"
#include <time.h>
#include <stdlib.h>

int main() {

    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sama Fire Rescue - Control de Incendios");
    InitAudioDevice();

    SetTargetFPS(60);

    Game game;
    InitGame(game);

    while (!WindowShouldClose()) {
        UpdateGame(game);
        DrawGame(game);
    }

    UnloadGameAssets(game);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
