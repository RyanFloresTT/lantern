#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <string_view>
#include <vector>

class AssetScope {
public:
    explicit AssetScope(AssetStore& asset_store) : asset_store(asset_store) {}

    template <typename T>
    T& Get(const std::string_view asset_path) {
        const auto path = std::string(asset_path);
        std::shared_ptr<T> d = std::static_pointer_cast<T>(assets.at(path));
        return *d;
    }

    template <typename T>
    void Load(const std::string_view asset_path) {
        auto ptr = asset_store.Get<T>(asset_path);
        const auto path = std::string(asset_path);
        assets[path] = ptr;
    }

    template <typename T>
    void LoadAll(const std::vector<std::string_view>& asset_paths) {
        for (const auto& path : asset_paths) Load<T>(path);
    }

private:
    AssetStore& asset_store;
    std::unordered_map<std::string, std::shared_ptr<void>> assets;
};