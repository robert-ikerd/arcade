add_executable(cartpole MACOSX_BUNDLE src/main.cpp)

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