#pragma once
#include <string>

#include "lantern/raii/audio.h"
#include "lantern/raii/window.h"
#include "lantern/scene/scene_manager.h"

class Game {
public:
    Game(const int width, const int height, const std::string& title, const int fps) : window(width, height, title.c_str(), fps), scene_manager(assets) {}

    ~Game()                                = default;
    Game(const Game& other)                = delete;
    Game& operator=(const Game& other)     = delete;
    Game(Game&& other) noexcept            = delete;
    Game& operator=(Game&& other) noexcept = delete;

    SceneManager& GetSceneManager() { return scene_manager; }
    void          Run() { scene_manager.Run(); }

private:
    Window       window;
    Audio        audio;
    AssetStore   assets;
    SceneManager scene_manager;
};
