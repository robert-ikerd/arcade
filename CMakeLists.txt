cmake_minimum_required(VERSION 3.20)
project(arcade LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG main
)
set(SDL_TTF_VENDORED ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL3_ttf)

include_directories(packages)

add_subdirectory(packages/graphics)
add_subdirectory(packages/gym)
# add_subdirectory(packages/ml)
add_subdirectory(packages/physics)

add_subdirectory(games/cartpole)