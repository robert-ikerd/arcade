cmake_minimum_required(VERSION 3.20)
project(MyGameSuite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)

FetchContent_MakeAvailable(SDL3)

add_subdirectory(packages/graphics)
# add_subdirectory(packages/physics)
# add_subdirectory(packages/gym)
# add_subdirectory(packages/ml)
add_subdirectory(games/cartpole)