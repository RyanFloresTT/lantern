#pragma once
#include "raylib.h"

class Window {
public:
    Window(const int width, const int height, const char* title, const int fps) {
        InitWindow(width, height, title);
        SetTargetFPS(fps);
    }

    ~Window() {
        CloseWindow();
    }
};
