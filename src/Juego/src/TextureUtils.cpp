#include "../include/TextureUtils.h"
#include <stdio.h>
#include <string.h>

Texture2D LoadCustomGameTexture(const char* filepath, int targetWidth, int targetHeight) {
    Image img = LoadImage(filepath);

    if (img.data == nullptr) {
        char altPath[256];
        sprintf(altPath, "../%s", filepath);
        img = LoadImage(altPath);
    }

    if (img.data == nullptr) {
        char altPath[256];
        sprintf(altPath, "../../%s", filepath);
        img = LoadImage(altPath);
    }

    if (img.data == nullptr) {
        return { 0, 0, 0, 0, 0 };
    }

    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

    Color* pixels = (Color*)img.data;
    int pixelCount = img.width * img.height;

    if (strstr(filepath, "well") != nullptr) {

        for (int i = 0; i < pixelCount; i++) {
            Color c = pixels[i];
            if (c.r > 245 && c.g > 245 && c.b > 245) {
                pixels[i] = BLANK;
            }
        }
    }
    else if (strstr(filepath, "fire2") != nullptr) {

        for (int i = 0; i < pixelCount; i++) {
            Color c = pixels[i];
            int dr = abs(c.r - 129);
            int dg = abs(c.g - 146);
            int db = abs(c.b - 153);
            if (dr < 15 && dg < 15 && db < 15) {
                pixels[i] = BLANK;
            }
        }
    }
    else if (strstr(filepath, "fire") != nullptr) {

        for (int i = 0; i < pixelCount; i++) {
            Color c = pixels[i];
            if (c.r > 240 && c.g > 240 && c.b > 240) {
                pixels[i] = BLANK;
            }
        }
    }
    else if (strstr(filepath, "ash") != nullptr) {

        for (int i = 0; i < pixelCount; i++) {
            Color c = pixels[i];
            if (c.r > 240 && c.g > 240 && c.b > 240) {
                pixels[i] = BLANK;
            }
        }
    }
    else if (strstr(filepath, "part") != nullptr) {

        for (int i = 0; i < pixelCount; i++) {
            Color c = pixels[i];
            if (c.r < 120 && c.g < 120 && c.b < 120) {
                pixels[i] = BLANK;
            }
        }
    }
    else if (strstr(filepath, "grass") != nullptr) {

        for (int i = 0; i < pixelCount; i++) {
            Color c = pixels[i];
            if (c.r > 200 && c.g > 200 && c.b > 200) {
                pixels[i] = BLANK;
            }
        }
    }
    else if (strstr(filepath, "mov") != nullptr || strstr(filepath, "estatico") != nullptr) {

        for (int i = 0; i < pixelCount; i++) {
            Color c = pixels[i];
            bool isBg = (c.r > 200 && c.g > 200 && c.b > 200) ||
                        (c.r > 120 && c.r < 170 && c.g > 130 && c.g < 170 && c.b > 135 && c.b < 175);
            if (isBg) {
                pixels[i] = BLANK;
            }
        }
    }

    ImageResizeNN(&img, targetWidth, targetHeight);
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

Sound LoadCustomGameSound(const char* filepath) {
    Sound snd = LoadSound(filepath);
    if (snd.frameCount == 0) {
        char altPath[256];
        sprintf(altPath, "../%s", filepath);
        snd = LoadSound(altPath);
    }
    if (snd.frameCount == 0) {
        char altPath[256];
        sprintf(altPath, "../../%s", filepath);
        snd = LoadSound(altPath);
    }
    return snd;
}
