#include "raylib.h"

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Mostrar texturas con teclas 1 y 2");
    Texture2D textureLogo = LoadTexture("resources/raylib_logo.png");
    Texture2D textureBunny = LoadTexture("resources/raybunny.png");
    bool showLogo = true;
    Rectangle source = { 0.0f, 0.0f, (float)textureLogo.width, (float)textureLogo.height };
    Rectangle dest = { 0.0f, 0.0f, (float)textureLogo.width, (float)textureLogo.height };
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ONE)) showLogo = true;
        if (IsKeyPressed(KEY_TWO)) showLogo = false;
        Texture2D currentTexture = showLogo ? textureLogo : textureBunny;
        source.width = (float)currentTexture.width;
        source.height = (float)currentTexture.height;
        dest.width = (float)currentTexture.width;
        dest.height = (float)currentTexture.height;
        dest.x = (screenWidth - dest.width) / 2.0f;
        dest.y = (screenHeight - dest.height) / 2.0f;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Iniciales: AEIG",20,0,20,BLACK);
        DrawText("Presiona 1 para raylib_logo.png", 20, 20, 20, DARKGRAY);
        DrawText("Presiona 2 para raybunny.png", 20, 50, 20, DARKGRAY);
        DrawText(showLogo ? "Mostrando: raylib_logo.png" : "Mostrando: raybunny.png", 20, 80, 20, BLACK);
        DrawTexturePro(currentTexture, source, dest, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadTexture(textureLogo);
    UnloadTexture(textureBunny);

    CloseWindow();

    return 0;
}
