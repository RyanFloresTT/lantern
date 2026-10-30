#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <string_view>

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

private:
    AssetStore& asset_store;
    std::unordered_map<std::string, std::shared_ptr<void>> assets;
};