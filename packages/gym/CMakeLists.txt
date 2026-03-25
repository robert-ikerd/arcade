add_library(gym STATIC 
    src/env.cpp
)

target_include_directories(gym PUBLIC include/)

target_link_libraries(gym 
    PUBLIC 
        SDL3::SDL3-shared
        physics 
        graphics
)