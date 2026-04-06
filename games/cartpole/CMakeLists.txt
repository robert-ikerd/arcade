cmake_minimum_required(VERSION 3.20)
project(CartPole LANGUAGES CXX)

add_executable(cartpole MACOSX_BUNDLE src/main.cpp)

target_compile_definitions(cartpole PRIVATE 
    CARTPOLE_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(cartpole PRIVATE
    physics
    graphics
    gym
    SDL3::SDL3-shared
)

install(TARGETS cartpole
    RUNTIME DESTINATION .
    BUNDLE DESTINATION .
    COMPONENT cartpole
)
