#pragma once
#include <functional>
#include <memory>
#include <optional>

#include "scene.h"

class SceneManager {
public:
    void        Run();
    void        Quit() { running = false; }

    void SetFrameCallback(const std::function<void()>& callback) { frame_callback = callback; }

    template <typename T, typename... Args>
    void GoTo(Args... args) {
        if (current != nullptr) transitioning = true;
        pending = [=] { return std::make_unique<T>(args...); };
    }

private:
    std::unique_ptr<Scene>                  current;
    std::function<std::unique_ptr<Scene>()> pending;
    std::optional<std::function<void()>>    frame_callback;
    bool                                    running             = true;
    bool                                    transitioning       = false;
    float                                   transition_progress = 0.0f;
    float                                   transition_duration = 1.0f;
    float                                   swap_time           = transition_duration / 2;
};
