#pragma once
#include "raylib.h"

class Audio {
public:
    Audio() {
        InitAudioDevice();
    }

    ~Audio() {
        CloseAudioDevice();
    }

    Audio(const Audio& other)                = delete;
    Audio& operator=(const Audio& other)     = delete;
    Audio(Audio&& other) noexcept            = delete;
    Audio& operator=(Audio&& other) noexcept = delete;
};
