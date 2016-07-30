cmake_minimum_required(VERSION 3.3)
project(10_view_camera_move)

IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

aux_source_directory(. SOURCE_FILES)

set(GBC_DIR ../../src)
add_subdirectory(${GBC_DIR} gbc)
include_directories(${GBC_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} GBC SDL2)

