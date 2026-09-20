#include "raylib.h"
#include <cmath>
#include <iostream>


void DrawPixelPoint(int x, int y, Color color) {
    DrawPixel(x, 500 - y, color);
}

void LineDDA(int x0, int y0, int x1, int y1, Color color) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = std::max(std::abs(dx), std::abs(dy));
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++) {
        DrawPixelPoint(round(x), round(y), color);
        x += xInc;
        y += yInc;
    }
}

void LineBresenham(int x0, int y0, int x1, int y1, Color color) {
    int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        DrawPixelPoint(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

int main() {
    InitWindow(500, 500, "Control Primitivas-Triangulo de Penrose");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        LineBresenham(100, 100, 400, 100, BLACK); // B ext
        LineBresenham(400, 100, 250, 400, BLACK); // L derecho ext
        LineBresenham(250, 400, 100, 100, BLACK); // L izquierdo ext
        
        LineDDA(150, 130, 350, 130, DARKGRAY); 
        DrawText("RHSR", 20, 460, 20, BLACK); 

        EndDrawing();
    }

    CloseWindow();
    return 0;
}