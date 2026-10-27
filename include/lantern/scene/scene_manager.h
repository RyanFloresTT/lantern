#pragma once
#include <functional>
#include <memory>
#include "scene.h"

class SceneManager {
public:
    static SceneManager& Get() {
        static SceneManager instance;
        return instance;
    }

    void        Run();
    void        Quit() { running = false; }

    template <typename T, typename... Args>
    void GoTo(Args... args) {
        if (current != nullptr) transitioning = true;
        pending = [=] { return std::make_unique<T>(args...); };
    }

private:
    std::unique_ptr<Scene>                  current;
    std::function<std::unique_ptr<Scene>()> pending;
    bool                                    running             = true;
    bool                                    transitioning       = false;
    float                                   transition_progress = 0.0f;
    float                                   transition_duration = 1.0f;
    float                                   swap_time           = transition_duration / 2;
};
