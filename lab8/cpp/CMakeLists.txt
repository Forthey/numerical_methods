cmake_minimum_required(VERSION 3.27)
project(lab8)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        poly.cpp
        poly_interpolator.cpp
        main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lab8 ${SOURCE_FILES})