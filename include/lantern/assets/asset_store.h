#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"

template <typename T> struct Asset;

template <>
struct Asset<Texture2D> {
    static Texture2D Load(const std::string_view path) { return LoadTexture(path.data()); }
    static void      Unload(const Texture2D& asset) { UnloadTexture(asset); }
};


template <>
struct Asset<Sound> {
    static Sound     Load(const std::string_view path) { return LoadSound(path.data()); }
    static void      Unload(const Sound& asset) { UnloadSound(asset); }
};

template <>
struct Asset<Music> {
    static Music     Load(const std::string_view path) { return LoadMusicStream(path.data()); }
    static void      Unload(const Music& asset) { UnloadMusicStream(asset); }
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
    T& Get(std::string_view path);

private:
    std::tuple<std::unordered_map<std::string, Texture2D>,
    std::unordered_map<std::string, Sound>,
    std::unordered_map<std::string, Music>> maps;
};

template <typename T>
T& AssetStore::Get(const std::string_view path) {
    auto& map = std::get<std::unordered_map<std::string, T>>(maps);
    const std::string data = path.data();
    if (map.contains(data)) {
        return map[data];
    }

    map[data] = Asset<T>::Load(data);
    return map[data];
}
