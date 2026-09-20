Coloca aquí las imágenes requeridas para las prácticas:

- raylib_logo.png
- raybunny.png

Sugerencia: copia ambas imágenes en esta carpeta para que el programa las cargue con rutas relativas.

Compilar (ejemplo rápido con gcc y raylib en Windows/MSYS):

```bash
# Usando pkg-config si está disponible
gcc ../PracTextura1.cpp -o PracTextura1.exe $(pkg-config --cflags --libs raylib)
gcc ../PracTextura2.cpp -o PracTextura2.exe $(pkg-config --cflags --libs raylib)

# Alternativa (linkear manualmente en Windows):
# gcc ../PracTextura1.cpp -o PracTextura1.exe -lraylib -lopengl32 -lgdi32 -lwinmm -lm
# gcc ../PracTextura2.cpp -o PracTextura2.exe -lraylib -lopengl32 -lgdi32 -lwinmm -lm
```

Nota: Ajusta las rutas según el directorio de trabajo del ejecutable. Si usas CMake, asegúrate de copiar la carpeta `resources` al directorio donde se ejecuta el binario (por ejemplo, `build/`).