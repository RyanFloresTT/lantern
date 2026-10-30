#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>

#include "raylib.h"

template <typename T>
struct AssetTraits;

typedef std::tuple<std::unordered_map<std::string, std::weak_ptr<Texture2D>>,
               std::unordered_map<std::string, std::weak_ptr<Sound>>,
               std::unordered_map<std::string, std::weak_ptr<Music>>,
               std::unordered_map<std::string, std::weak_ptr<Font>>> AssetMaps;

template <>
struct AssetTraits<Texture2D> {
    static Texture2D* Load(const std::string_view path) { return new Texture2D(LoadTexture(path.data())); }
    static void      Unload(const Texture2D& asset) { UnloadTexture(asset); }
};


template <>
struct AssetTraits<Sound> {
    static Sound* Load(const std::string_view path) { return new Sound(LoadSound(path.data())); }
    static void  Unload(const Sound& asset) { UnloadSound(asset); }
};

template <>
struct AssetTraits<Music> {
    static Music* Load(const std::string_view path) { return new Music(LoadMusicStream(path.data())); }
    static void  Unload(const Music& asset) { UnloadMusicStream(asset); }
};

template <>
struct AssetTraits<Font> {
    static constexpr int BaseSize = 96;

    static Font* Load(const std::string_view path) {
        const Font font = LoadFontEx(path.data(), BaseSize, nullptr, 0);
        SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
        return new Font(font);
    }

    static void Unload(const Font& asset) { UnloadFont(asset); }
};

class AssetStore {
public:
    AssetStore() = default;

    AssetStore(const AssetStore& other)                = delete;
    AssetStore& operator=(const AssetStore& other)     = delete;
    AssetStore(AssetStore&& other) noexcept            = delete;
    AssetStore& operator=(AssetStore&& other) noexcept = delete;

    template <typename T>
    std::shared_ptr<T> Get(std::string_view file_path);

private:
     AssetMaps maps;
};

template <typename T>
std::shared_ptr<T> AssetStore::Get(const std::string_view file_path) {
    auto&             map  = std::get<std::unordered_map<std::string, std::weak_ptr<T>>>(maps);
    const auto&       normalizedPath = std::string(file_path);

    if (map.contains(normalizedPath)) {
        if (std::shared_ptr<T> ptr = map[normalizedPath].lock()) return ptr;
    }

    std::shared_ptr<T> a(AssetTraits<T>::Load(normalizedPath), [](T* asset) {
        AssetTraits<T>::Unload(*asset);
        delete asset;
    });

    map[normalizedPath] = a;
    return map[normalizedPath].lock();
}
