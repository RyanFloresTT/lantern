#pragma once
#include "lantern/assets/asset_store.h"
#include "lantern/raii/asset_scope.h"

class SceneManager;

class Scene {
public:
    explicit     Scene(AssetStore& asset_store) : scene_manager(nullptr), asset_store(asset_store), assets(asset_store) {}
    virtual      ~Scene() = default;
    virtual void Enter() {}
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    bool         Done() const { return done; }

protected:
    bool       done = false;
    SceneManager* scene_manager;
    AssetStore& asset_store;
    AssetScope assets;
};
