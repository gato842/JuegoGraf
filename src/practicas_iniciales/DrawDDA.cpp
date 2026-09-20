#include "raylib.h"
#include <cmath>
#include <string>

const int CELL_SIZE = 40;
const int COLS=15;
const int ROWS=10;
const int OFFSET_X=80;
const int OFFSET_Y=80;

void DrawGridEx(){
    for(int i=0;i<=COLS;i++){
        DrawLine(OFFSET_X+i*CELL_SIZE, OFFSET_Y, OFFSET_X+i*CELL_SIZE, OFFSET_Y+ROWS*CELL_SIZE, LIGHTGRAY);
    }
    for(int j=0;j<=ROWS;j++){
        DrawLine(OFFSET_X, OFFSET_Y+j*CELL_SIZE, OFFSET_X+COLS*CELL_SIZE, OFFSET_Y+j*CELL_SIZE, LIGHTGRAY);
    }
}
void FillCell(int x, int y,Color color){
    if(x>=0&&x<COLS&&y>=0&&y<ROWS){
        DrawRectangle(OFFSET_X+x*CELL_SIZE, OFFSET_Y+y*CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
    }
}
void DrawLineDDA_Grid(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    if (steps == 0) {
        FillCell(x1, y1, RED);
        return;
    }

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = (float)x1;
    float y = (float)y1;

    for (int k = 0; k <= steps; k++) {
        FillCell((int)round(x), (int)round(y), RED);
        x += xInc;
        y += yInc;
    }
}
int main() {
    InitWindow(800, 600, "Ejercicio DDA - Primitivas Graficas");
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
        DrawLineDDA_Grid(p1_x, p1_y, p2_x, p2_y);
        int screen_x1 = OFFSET_X + p1_x * CELL_SIZE + CELL_SIZE / 2;
        int screen_y1 = OFFSET_Y + p1_y * CELL_SIZE + CELL_SIZE / 2;
        int screen_x2 = OFFSET_X + p2_x * CELL_SIZE + CELL_SIZE / 2;
        int screen_y2 = OFFSET_Y + p2_y * CELL_SIZE + CELL_SIZE / 2;

        DrawLineEx((Vector2){(float)screen_x1, (float)screen_y1}, 
                   (Vector2){(float)screen_x2, (float)screen_y2}, 3.0f, GREEN);
        FillCell(p1_x, p1_y, BLUE);
        FillCell(p2_x, p2_y, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}






