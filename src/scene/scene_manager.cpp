//
// Created by rryan on 10/23/2026.
//

#include "lantern/scene/scene_manager.h"

#include "raylib.h"

void SceneManager::Run() {
    while (!WindowShouldClose() && running) {
        if (transitioning && transition_progress < transition_duration) {
            transition_progress += GetFrameTime();
        }
        else {
            transitioning       = false;
            transition_progress = 0;
        }

        if (pending && (!transitioning || transition_progress >= swap_time)) {
            current = pending();
            pending = nullptr;
            current->Enter();
            current->scene_manager = this;
        }
        if (!current) break;

        current->Update(GetFrameTime());

        BeginDrawing();

        ClearBackground(RAYWHITE);
        current->Draw();

        if (transitioning) {
            const float t     = transition_progress / transition_duration; // 0 -> 1
            const float alpha = 1.0f - std::abs(t * 2.0f - 1.0f);
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, alpha));
        }

        if (frame_callback.has_value()) {
            frame_callback.value();
        }

        EndDrawing();
    }
}
