cmake_minimum_required(VERSION 3.25)
project(nm_6_v_2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        source/solution.cpp
        source/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(nm_6_v_2 ${SOURCE_FILES})