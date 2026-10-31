cmake_minimum_required(VERSION 4.2)
project(lantern CXX)

include(FetchContent)
FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_library(lantern STATIC
        src/scene/scene_manager.cpp
        include/lantern/game/game.h
        include/lantern/assets/asset_store.h
        include/lantern/raii/window.h
        include/lantern/raii/asset_scope.h
)

target_include_directories(lantern
        PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(lantern PUBLIC raylib)
target_compile_features(lantern PUBLIC cxx_std_20)
