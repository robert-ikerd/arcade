add_library(graphics STATIC 
    src/colors.cpp
    src/shapes.cpp
)

target_include_directories(graphics PUBLIC include/)

target_link_libraries(graphics PUBLIC SDL3::SDL3-shared)