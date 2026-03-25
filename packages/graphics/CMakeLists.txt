add_library(graphics STATIC 
    src/colors.cpp
    src/2d/entities.cpp
    src/2d/screen.cpp
)

target_include_directories(graphics PUBLIC include/)

target_link_libraries(graphics 
    PUBLIC 
        SDL3::SDL3-shared
        physics 
)