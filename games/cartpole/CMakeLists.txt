add_executable(CartPole src/main.cpp)

target_link_libraries(CartPole PRIVATE 
    graphics
    SDL3::SDL3-shared
)

if(APPLE)
    set_target_properties(CartPole PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourname.cartpole"
    )
endif()