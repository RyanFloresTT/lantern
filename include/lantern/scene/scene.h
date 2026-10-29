#pragma once

class SceneManager;

class Scene {
public:
    Scene(SceneManager& scene_manager);
    virtual      ~Scene() = default;
    virtual void Enter() {}
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    bool         Done() const { return done; }

protected:
    bool done = false;
    SceneManager& scene_manager;
};
