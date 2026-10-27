#pragma once

class Scene {
public:
    virtual      ~Scene() = default;
    virtual void Enter() {}
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    bool         Done() const { return done; }

protected:
    bool done = false;
};
