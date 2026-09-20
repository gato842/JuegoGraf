#include "raylib.h"
#include <cmath>
#include <string>

const int CELL_SIZE = 40;
const int COLS = 15;
const int ROWS = 10;
const int OFFSET_X = 80;
const int OFFSET_Y = 80;

void DrawGridEx() {
    for (int i = 0; i <= COLS; i++) {
        DrawLine(OFFSET_X + i * CELL_SIZE, OFFSET_Y, OFFSET_X + i * CELL_SIZE, OFFSET_Y + ROWS * CELL_SIZE, LIGHTGRAY);
    }
    for (int j = 0; j <= ROWS; j++) {
        DrawLine(OFFSET_X, OFFSET_Y + j * CELL_SIZE, OFFSET_X + COLS * CELL_SIZE, OFFSET_Y + j * CELL_SIZE, LIGHTGRAY);
    }
}

void FillCell(int x, int y, Color color) {
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) {
        // Se añade +1 y -2 para dejar un pequeño margen y que no tape las líneas de la cuadrícula
        DrawRectangle(OFFSET_X + x * CELL_SIZE + 1, OFFSET_Y + y * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2, color);
    }
}

void DrawLineBresenham_Grid(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        FillCell(x1, y1, RED);

        if (x1 == x2 && y1 == y2) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

int main() {
    InitWindow(800, 600, "Ejercicio Bresenham");
    SetTargetFPS(60);

    int p1_x = 2, p1_y = 2;
    int p2_x = 10, p2_y = 6;

    while (!WindowShouldClose()) {
    
        if (IsKeyPressed(KEY_W) && p1_y > 0) p1_y--;
        if (IsKeyPressed(KEY_S) && p1_y < ROWS - 1) p1_y++;
        if (IsKeyPressed(KEY_A) && p1_x > 0) p1_x--;
        if (IsKeyPressed(KEY_D) && p1_x < COLS - 1) p1_x++;

        if (IsKeyPressed(KEY_UP) && p2_y > 0) p2_y--;
        if (IsKeyPressed(KEY_DOWN) && p2_y < ROWS - 1) p2_y++;
        if (IsKeyPressed(KEY_LEFT) && p2_x > 0) p2_x--;
        if (IsKeyPressed(KEY_RIGHT) && p2_x < COLS - 1) p2_x++;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawGridEx();
        DrawLineBresenham_Grid(p1_x, p1_y, p2_x, p2_y);

        // Línea guía verde entre centros
        int screen_x1 = OFFSET_X + p1_x * CELL_SIZE + CELL_SIZE / 2;
        int screen_y1 = OFFSET_Y + p1_y * CELL_SIZE + CELL_SIZE / 2;
        int screen_x2 = OFFSET_X + p2_x * CELL_SIZE + CELL_SIZE / 2;
        int screen_y2 = OFFSET_Y + p2_y * CELL_SIZE + CELL_SIZE / 2;

        DrawLineEx((Vector2){(float)screen_x1, (float)screen_y1}, 
                   (Vector2){(float)screen_x2, (float)screen_y2}, 3.0f, GREEN);

        // Puntos inicial y final en azul
        FillCell(p1_x, p1_y, BLUE);
        FillCell(p2_x, p2_y, BLUE);

        // Textos informativos
        DrawText("Punto Inicial (WASD): Azul", 80, 20, 20, DARKBLUE);
        DrawText("Punto Final (Flechas): Azul", 380, 20, 20, DARKBLUE);
        DrawText("Linea Bresenham: Rojo | Linea Raylib: Verde", 80, 50, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}