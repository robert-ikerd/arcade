add_library(physics STATIC 
    src/2d/geom.cpp
    src/2d/objects.cpp
)

target_compile_features(physics PUBLIC cxx_std_20)

target_include_directories(physics PUBLIC include/)
target_link_libraries(physics PUBLIC SDL3::SDL3-shared)