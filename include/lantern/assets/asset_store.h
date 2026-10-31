#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>

#include "raylib.h"

[[noreturn]] inline void AssetError(const std::string& message) {
    TraceLog(LOG_ERROR, "%s", message.c_str());
    throw std::runtime_error(message);
}

template <typename T>
struct AssetTraits;

template <>
struct AssetTraits<Texture2D> {
    static constexpr const char* Name = "Texture2D";
    static Texture2D Load(const std::string& path) { return LoadTexture(path.c_str()); }
    static bool      Valid(const Texture2D& asset) { return IsTextureValid(asset); }
    static void      Unload(const Texture2D& asset) { UnloadTexture(asset); }
};

template <>
struct AssetTraits<Sound> {
    static constexpr const char* Name = "Sound";
    static Sound Load(const std::string& path) { return LoadSound(path.c_str()); }
    static bool  Valid(const Sound& asset) { return IsSoundValid(asset); }
    static void  Unload(const Sound& asset) { UnloadSound(asset); }
};

template <>
struct AssetTraits<Music> {
    static constexpr const char* Name = "Music";
    static Music Load(const std::string& path) { return LoadMusicStream(path.c_str()); }
    static bool  Valid(const Music& asset) { return IsMusicValid(asset); }
    static void  Unload(const Music& asset) { UnloadMusicStream(asset); }
};

template <>
struct AssetTraits<Font> {
    static constexpr const char* Name     = "Font";
    static constexpr int         BaseSize = 96;

    static Font Load(const std::string& path) {
        const Font font = LoadFontEx(path.c_str(), BaseSize, nullptr, 0);
        if (Valid(font)) SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
        return font;
    }

    static bool Valid(const Font& asset) { return IsFontValid(asset) && asset.texture.id != 0; }
    static void Unload(const Font& asset) { UnloadFont(asset); }
};

using AssetMaps = std::tuple<std::unordered_map<std::string, std::weak_ptr<Texture2D>>,
                             std::unordered_map<std::string, std::weak_ptr<Sound>>,
                             std::unordered_map<std::string, std::weak_ptr<Music>>,
                             std::unordered_map<std::string, std::weak_ptr<Font>>>;

class AssetStore {
public:
    AssetStore() = default;

    AssetStore(const AssetStore& other)                = delete;
    AssetStore& operator=(const AssetStore& other)     = delete;
    AssetStore(AssetStore&& other) noexcept            = delete;
    AssetStore& operator=(AssetStore&& other) noexcept = delete;

    // Returns the cached asset if anyone still holds it, otherwise loads it.
    // Throws if the load fails.
    template <typename T>
    std::shared_ptr<T> Get(std::string_view file_path);

private:
    AssetMaps maps;
};

template <typename T>
std::shared_ptr<T> AssetStore::Get(const std::string_view file_path) {
    auto&             map = std::get<std::unordered_map<std::string, std::weak_ptr<T>>>(maps);
    const std::string path(file_path);

    if (const auto it = map.find(path); it != map.end()) {
        if (std::shared_ptr<T> ptr = it->second.lock()) return ptr;
    }

    const T loaded = AssetTraits<T>::Load(path);
    if (!AssetTraits<T>::Valid(loaded)) {
        AssetError(std::string("AssetStore: failed to load ") + AssetTraits<T>::Name + " '" + path + "'");
    }

    std::shared_ptr<T> asset(new T(loaded), [](T* a) {
        AssetTraits<T>::Unload(*a);
        delete a;
    });

    map[path] = asset;
    return asset;
}
