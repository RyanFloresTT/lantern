#pragma once
#include "lantern/assets/asset_store.h"

class SceneManager;

class Scene {
public:
    virtual       ~Scene() = default;
    virtual void  Enter() {}
    virtual void  Update(float dt) = 0;
    virtual void  Draw() = 0;
    bool          Done() const { return done; }
    SceneManager* scene_manager;

protected:
    bool       done = false;
    AssetStore assets;
};
