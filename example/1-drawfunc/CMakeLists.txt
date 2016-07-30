cmake_minimum_required(VERSION 3.3)

project(1_drawfunc)

IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

aux_source_directory(. SOURCE_FILES)

set(GBC_DIR ../../src)

add_subdirectory(${GBC_DIR} gbc)
include_directories(${GBC_DIR})

add_executable(1_drawfunc ${SOURCE_FILES})

target_link_libraries(1_drawfunc GBC)

