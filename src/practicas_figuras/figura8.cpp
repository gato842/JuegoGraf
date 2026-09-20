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
void DibujarFiguras(Vector2 c,Vector2 r){
    Vector2 punto1=ToScreen(c);
    Vector2 punto2={r.x,r.y+5};
    Vector2 punto3={r.x,r.y-5};
    Vector2 p2 = ToScreen(punto2);
    Vector2 p3 = ToScreen(punto3);

    DrawPoly(punto1,5, 150.0f,55.0f, BLUE);
    DrawPoly(p3,3, 150.0f,90.0f, GREEN);
    DrawPoly(p2,3, 150.0f,270.0f, GREEN);
}

int main(){

    InitWindow(800, 600, "Translación Rotación Escalamiento");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DibujarEjes();
        DibujarFiguras({-100,0},{100,0});
        DrawText("GL_POLY Axel Irahola", 10, 10, 20, BLUE);
        EndDrawing();   
    }


    return 0;
}