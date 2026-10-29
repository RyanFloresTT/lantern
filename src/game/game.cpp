//
// Created by rryan on 10/28/2026.
//

#include "lantern/game/game.h"

#include "raylib.h"
#include "lantern/scene/scene_manager.h"

Game::Game(const int width, const int height, const std::string& title, const int fps) {
    InitWindow(width, height, title.c_str());
    SetTargetFPS(fps);
    InitAudioDevice();
}

Game::~Game() {
    CloseAudioDevice();
    CloseWindow();
}

void Game::Run() {
    scene_manager.Run();
}
