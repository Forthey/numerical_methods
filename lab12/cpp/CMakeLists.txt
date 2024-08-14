cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab12)

set(SOURCE_FILES
        source/main.cpp
        source/runge_kutta.cpp
)

set(EXECUTABLE_NAME ${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${EXECUTABLE_NAME}
        ${SOURCE_FILES})