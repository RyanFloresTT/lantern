#pragma once
#include <string>

#include "lantern/scene/scene_manager.h"

class Game {
public:
    Game(int width, int height, const std::string& title, int fps);
    ~Game();

    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    Game(Game&& other) noexcept = delete;
    Game& operator=(Game&& other) noexcept = delete;

    SceneManager& GetSceneManager() { return scene_manager; }
    void Run();

private:
    SceneManager scene_manager;
};
