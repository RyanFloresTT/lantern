#pragma once

class SceneManager;

class Scene {
public:
    virtual void  Enter() {}
    virtual void  Update(float dt);
    virtual void  Draw();
    bool          Done() const { return done; }
    SceneManager* scene_manager;

protected:
    bool done = false;
};
