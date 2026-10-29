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
};
