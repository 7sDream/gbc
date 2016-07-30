cmake_minimum_required(VERSION 3.3)

aux_source_directory(. GBC_FILES)

add_library(GBC ${GBC_FILES})

target_compile_features(GBC PUBLIC cxx_nullptr)
target_compile_features(GBC PUBLIC cxx_auto_type)
target_compile_features(GBC PUBLIC cxx_range_for)
target_compile_features(GBC PUBLIC cxx_final)

target_link_libraries(
    GBC
    PRIVATE GL
    PRIVATE GLU
    PRIVATE glut
)

