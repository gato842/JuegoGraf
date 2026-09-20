#include "raylib.h"
#include <string.h>
int main(void)
{
const int screenWidth = 800;
const int screenHeight = 450; 
InitWindow(screenWidth, screenHeight, "Ejercicio 2 - Mover textura RHSR");
Texture2D bunny = LoadTexture("resources/raybunny.png");
Vector2 posicion = { 350.0f, 200.0f };
float velocidad = 4.0f;
SetTargetFPS(60);
while (!WindowShouldClose())
{
if (IsKeyDown(KEY_RIGHT)) posicion.x += velocidad;
if (IsKeyDown(KEY_LEFT)) posicion.x -= velocidad;
if (IsKeyDown(KEY_UP)) posicion.y -= velocidad;
if (IsKeyDown(KEY_DOWN)) posicion.y += velocidad;
if(posicion.x < 0) posicion.x = 0;
if(posicion.y < 0) posicion.y = 0;
if(posicion.x > screenWidth - bunny.width) posicion.x = screenWidth - bunny.width;
if(posicion.y > screenHeight - bunny.height) posicion.y = screenHeight - bunny.height;

BeginDrawing();
ClearBackground(RAYWHITE);
DrawText("Iniciales: AEIG",20,0,20,BLACK);
DrawText("Ejercicio 2: Mover textura con teclado RHSR", 40, 40, 24,
BLACK);
DrawText("Usa las flechas del teclado", 40, 80, 18, DARKGRAY);
DrawTextureV(bunny, posicion, WHITE);
DrawText(TextFormat("X: %.0f", posicion.x), 40, 130, 18, BLACK);
DrawText(TextFormat("Y: %.0f", posicion.y), 40, 160, 18, BLACK);
EndDrawing();
}
UnloadTexture(bunny);
CloseWindow();
return 0;
}
