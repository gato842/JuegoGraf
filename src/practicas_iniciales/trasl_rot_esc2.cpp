#include "raylib.h"
#include "rlgl.h"

using namespace std;

    const int ANCHO=800;
    const int ALTO=600;
    const int Xmin =-200;
    const int Xmax = 200;
    const int Ymin =-150;
    const int Ymax = 150;


Vector2 ToScreen(Vector2 p){
    float x = (p.x - Xmin)* ANCHO/(Xmax - Xmin);
    float y = ALTO - (p.y - Ymin)* ALTO/(Ymax - Ymin);
    return {x, y};
}

void DibujarLinea(Vector2 a,Vector2 b,Color color){
    Vector2 pa = ToScreen(a);
    Vector2 pb = ToScreen(b);
    DrawLineV(pa, pb, color);
}

void DibujarEjes(){
    DibujarLinea({-200,0}, {200,0},BLACK);
    DibujarLinea({0,-150}, {0,150},BLACK);
}

int main(){

    InitWindow(800, 600, "Translación Rotación Escalamiento");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DibujarEjes();
        DrawText("GL_LINES Axel Irahola", 10, 10, 20, BLUE);
        EndDrawing();   
    }


    return 0;
}