//
// Created by rryan on 10/28/2026.
//

#include "lantern/assets/asset_store.h"

template <typename Map>
static void UnloadAssets(Map& map) {
    using AssetType = Map::mapped_type;
    for (auto& [path, asset] : map) {
        Asset<AssetType>::Unload(asset);
    }
}

AssetStore::~AssetStore() {
    std::apply([](auto&... v) {
        (UnloadAssets(v), ...);
    }, maps);
}