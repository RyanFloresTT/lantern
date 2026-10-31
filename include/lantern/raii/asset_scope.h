#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "lantern/assets/asset_store.h"

// Holds shared references to the assets a scene (or other owner) uses, so they stay loaded
// for the scope's lifetime.
class AssetScope {
public:
    explicit AssetScope(AssetStore& asset_store) : asset_store(asset_store) {}

    template <typename T>
    T& Get(const std::string_view asset_path) const {
        const auto it = assets.find(std::string(asset_path));
        if (it == assets.end()) {
            AssetError(std::string("AssetScope::Get: ") + AssetTraits<T>::Name + " '" + std::string(asset_path) +
                       "' was not loaded in this scope. Load it (or call the helper's Preload) first.");
        }
        if (it->second.type != std::type_index(typeid(T))) {
            AssetError(std::string("AssetScope::Get: '") + std::string(asset_path) +
                       "' was loaded as a different type than " + AssetTraits<T>::Name);
        }
        return *std::static_pointer_cast<T>(it->second.ptr);
    }

    template <typename T>
    void Load(const std::string_view asset_path) {
        assets.insert_or_assign(std::string(asset_path), Entry{asset_store.Get<T>(asset_path), std::type_index(typeid(T))});
    }

    template <typename T>
    void LoadAll(const std::vector<std::string_view>& asset_paths) {
        for (const auto& path : asset_paths) Load<T>(path);
    }

private:
    struct Entry {
        std::shared_ptr<void> ptr;
        std::type_index       type;
    };

    AssetStore&                            asset_store;
    std::unordered_map<std::string, Entry> assets;
};
