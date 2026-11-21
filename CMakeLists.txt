cmake_minimum_required(VERSION 3.20)

project(MConfig LANGUAGES CXX)

add_library(MConfig INTERFACE)

target_include_directories(MConfig
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(MConfig INTERFACE cxx_std_17)
