#pragma once
#include <string>

#include "lantern/scene/scene_manager.h"

class Game {
public:
    Game(int width, int height, const std::string& title, int fps);
    ~Game();
    SceneManager& GetSceneManager() { return scene_manager; }
    void Run();

private:
    SceneManager scene_manager;
};
