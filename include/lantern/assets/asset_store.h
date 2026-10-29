#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"

template <typename T> struct Asset;

template <>
struct Asset<Texture2D> {
    static Texture2D Load(const std::string& path) { return LoadTexture(path.c_str()); }
    static void      Unload(const Texture2D& asset) { UnloadTexture(asset); }
};


template <>
struct Asset<Sound> {
    static Sound     Load(const std::string& path) { return LoadSound(path.c_str()); }
    static void      Unload(const Sound& asset) { UnloadSound(asset); }
};

class AssetStore {
public:
    AssetStore() = default;
    ~AssetStore();

    AssetStore(const AssetStore& other) = delete;
    AssetStore& operator=(const AssetStore& other) = delete;
    AssetStore(AssetStore&& other) noexcept = delete;
    AssetStore& operator=(AssetStore&& other) noexcept = delete;

    template <typename T>
    T& Get(std::string path);

private:
    std::tuple<std::unordered_map<std::string, Texture2D>,
    std::unordered_map<std::string, Sound>> maps;
};

template <typename T>
T& AssetStore::Get(std::string path) {
    auto& map = std::get<std::unordered_map<std::string, T>>(maps);
    if (map.contains(path)) {
        return map[path];
    }

    map[path] = Asset<T>::Load(path);
    return map[path];
}
