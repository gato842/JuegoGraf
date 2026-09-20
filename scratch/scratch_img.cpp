#include <raylib.h>
#include <iostream>

void PrintSize(const char* name) {
    Image img = LoadImage(name);
    if (img.data != nullptr) {
        std::cout << name << " size: " << img.width << "x" << img.height << std::endl;
        UnloadImage(img);
    } else {
        std::cout << "Failed to load: " << name << std::endl;
    }
}

int main() {
    InitWindow(100, 100, "Temp");
    PrintSize("../src/Juego/resources/padre.png");
    PrintSize("../src/Juego/resources/hijo.png");
    PrintSize("../src/Juego/resources/bombero.png");
    PrintSize("../src/Juego/resources/camion.png");
    CloseWindow();
    return 0;
}
