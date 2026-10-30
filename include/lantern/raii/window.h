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

    Window(const Window& other)                = delete;
    Window& operator=(const Window& other)     = delete;
    Window(Window&& other) noexcept            = delete;
    Window& operator=(Window&& other) noexcept = delete;
};
