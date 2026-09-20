#include "raylib.h"
#include "rlgl.h"


int main() {
    InitWindow(800, 600, "Translación Rotación Escalamiento");
    SetTargetFPS(60);
    Vector2 posicion={400,300};
    float rotacion=0.0f;
    float escala=1.0f;

    while (!WindowShouldClose()) {

        if(IsKeyDown(KEY_RIGHT))posicion.x+=2;
        if(IsKeyDown(KEY_LEFT))posicion.x-=2;
        if(IsKeyDown(KEY_DOWN)) posicion.y+=2;
        if(IsKeyDown(KEY_UP)) posicion.y-=2;

        if(IsKeyDown(KEY_R))rotacion+=2.0f;
        if(IsKeyDown(KEY_T))rotacion-=2.0f;

        if(IsKeyDown(KEY_KP_ADD)|| IsKeyDown(KEY_EQUAL)) escala+=0.1f;
        if(IsKeyDown(KEY_KP_SUBTRACT)|| IsKeyDown(KEY_MINUS)) escala-=0.1f;

        if(escala< 0.2f) escala=0.2f;
        if(escala>3.0f) escala=3.0f;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Flechas=mover, R/T=rotar, +/-=escalar", 10, 10, 20, DARKGRAY);
        DrawRectanglePro((Rectangle){posicion.x,posicion.y,100*escala,50*escala}, (Vector2){50*escala,50*escala}, rotacion, BLUE);

     EndDrawing();   
    }
    
    CloseWindow();
    return 0;
}
