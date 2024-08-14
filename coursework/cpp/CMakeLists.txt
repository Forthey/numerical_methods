cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(lab10)


find_package(Threads REQUIRED)

option(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
    find_program(_PROTOBUF_PROTOC protoc)
else()
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()


# Generated sources
set(rg_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/main.pb.cc")
set(rg_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/main.pb.h")
set(rg_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/main.grpc.pb.cc")
set(rg_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/main.grpc.pb.h")

add_custom_command(
        OUTPUT "${rg_proto_srcs}" "${rg_proto_hdrs}" "${rg_grpc_srcs}" "${rg_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I../../protos/
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        ../../protos/main.proto
        DEPENDS ../../protos/main.proto
)

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hw_grpc_proto
add_library(rg_grpc_proto
        ${rg_grpc_srcs}
        ${rg_grpc_hdrs}
        ${rg_proto_srcs}
        ${rg_proto_hdrs})
target_link_libraries(rg_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})


include(FetchContent)
FetchContent_Declare(
        pretty
        GIT_REPOSITORY https://github.com/Forthey/PrettySTL
        GIT_TAG        0.1.0
)
FetchContent_MakeAvailable(pretty)

set(SOURCE_FILES
        source/main.cpp
        source/integral.cpp
)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/pretty-src)

set(EXECUTABLE_NAME ${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${EXECUTABLE_NAME}
        ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME}
        rg_grpc_proto
        ${_REFLECTION}
        ${_PROTOBUF_LIBPROTOBUF}
)

